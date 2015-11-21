#include "StdAfx.h"
#include "cObjParser.h"
#include <iostream>
#include "cDeviceMgr.h"

using namespace std;

cObjParser::cObjParser(void)
{
}

cObjParser::~cObjParser(void)
{
}

void cObjParser::Load( IN char* szFileName,
					  OUT std::vector<ST_GROUP*>& Groups,
					  OUT std::map<std::string, ST_MTL_TEX> &MtlTex )
{
	Clear();

	std::vector<ST_PNT_VERTEX>	Vertexes;
	char szBuf[1024];

	FILE* fp;
	fopen_s(&fp, szFileName, "r");

	while(!feof(fp))
	{
		fgets(szBuf, 1024, fp);
		if(szBuf[0] == '#')
		{
			continue;
		}
		else if(IsStartWith(szBuf, "mtllib"))
		{
			char szMtlFileName[1024];
			sscanf_s(szBuf, "%*s %s", szMtlFileName, 1024);
			ProcessMtl(szMtlFileName, MtlTex);
		}
		else if(szBuf[0] == 'g')
		{
			if(!Vertexes.empty())
			{
				// 버텍스 버퍼 생성
				g_pD3DDevice->CreateVertexBuffer(
					Vertexes.size() * sizeof(ST_PNT_VERTEX),
					0,
					ST_PNT_VERTEX::FVF,
					D3DPOOL_MANAGED,
					&Groups.back()->pVB,
					0);
				// 삼각형 개수 기록
				Groups.back()->nNumTri = Vertexes.size() / 3;

				// 디바이스 메모리에 데이터 기록
				void* pVertex;
				Groups.back()->pVB->Lock(0, 0, &pVertex, 0);
				memcpy(pVertex, &Vertexes[0], Vertexes.size() * sizeof(ST_PNT_VERTEX));
				Groups.back()->pVB->Unlock();

				Vertexes.clear();
			}
		}
		else if(IsStartWith(szBuf, "vt"))
		{
			float fU, fV;
			sscanf_s(szBuf, "%*s %f %f %*f", &fU, &fV);
			m_VT.push_back(D3DXVECTOR2(fU, fV));
		}
		else if(IsStartWith(szBuf, "vn"))
		{
			float fX, fY, fZ;
			sscanf_s(szBuf, "%*s %f %f %f", &fX, &fY, &fZ);
			m_VN.push_back(D3DXVECTOR3(fX, fY, fZ));
		}
		else if(IsStartWith(szBuf, "v "))
		{
			float fX, fY, fZ;
			sscanf_s(szBuf, "%*s %f %f %f", &fX, &fY, &fZ);
			m_V.push_back(D3DXVECTOR3(fX, fY, fZ));
		}
		else if(IsStartWith(szBuf, "usemtl"))
		{
			char szMtlName[1024];
			sscanf_s(szBuf, "%*s %s", szMtlName, 1024);

			ST_GROUP* pGroup = new ST_GROUP;
			pGroup->sMtlName = szMtlName;
			Groups.push_back(pGroup);
		}
		else if(IsStartWith(szBuf, "f "))
		{
			int nIdx[3][3];
			sscanf_s(szBuf, "%*s %d/%d/%d %d/%d/%d %d/%d/%d",
				&nIdx[0][0], &nIdx[0][1], &nIdx[0][2],
				&nIdx[1][0], &nIdx[1][1], &nIdx[1][2],
				&nIdx[2][0], &nIdx[2][1], &nIdx[2][2]);
			
			for (int i = 0; i < 3; ++i)
			{
				ST_PNT_VERTEX v;
				v.p = m_V[nIdx[i][0] - 1];
				v.t = m_VT[nIdx[i][1] - 1];
				v.n = m_VN[nIdx[i][2] - 1];
				Vertexes.push_back(v);
			}
		}
	}
	fclose(fp);

	if(!Vertexes.empty())
	{
		// 버텍스 버퍼 생성
		g_pD3DDevice->CreateVertexBuffer(
			Vertexes.size() * sizeof(ST_PNT_VERTEX),
			0,
			ST_PNT_VERTEX::FVF,
			D3DPOOL_MANAGED,
			&Groups.back()->pVB,
			0);
		// 삼각형 개수 기록
		Groups.back()->nNumTri = Vertexes.size() / 3;

		// 디바이스 메모리에 데이터 기록
		void* pVertex;
		Groups.back()->pVB->Lock(0, 0, &pVertex, 0);
		memcpy(pVertex, &Vertexes[0], Vertexes.size() * sizeof(ST_PNT_VERTEX));
		Groups.back()->pVB->Unlock();

		Vertexes.clear();
	}
}

void cObjParser::ProcessMtl( IN char* szFileName,
							OUT std::map<std::string, ST_MTL_TEX> &MtlTex )
{
	char szBuf[1024];
	
	FILE* fp;
	fopen_s(&fp, szFileName, "r");

	char szMtlName[1024];

	while(!feof(fp))
	{
		fgets(szBuf, 1024, fp);
		if(szBuf[0] == '#')
		{
			continue;
		}
		else if(IsStartWith(szBuf, "newmtl"))
		{
			sscanf_s(szBuf, "%*s %s", szMtlName, 1024);
		}
		else if(IsStartWith(szBuf, "map_Kd"))
		{
			char szTextureFileName[1024];
			sscanf_s(szBuf, "%*s %s", szTextureFileName, 1024);
			D3DXCreateTextureFromFile(g_pD3DDevice, szTextureFileName, &MtlTex[szMtlName].pTex);
		}
		else if(IsStartWith(szBuf, "Ka"))
		{
			float fR, fG, fB;
			sscanf_s(szBuf, "%*s %f %f %f", &fR, &fG, &fB);
			MtlTex[szMtlName].Mtl.Ambient.r = fR;
			MtlTex[szMtlName].Mtl.Ambient.g = fG;
			MtlTex[szMtlName].Mtl.Ambient.b = fB;
			MtlTex[szMtlName].Mtl.Ambient.a = 1.0f;
		}
		else if(IsStartWith(szBuf, "Kd"))
		{
			float fR, fG, fB;
			sscanf_s(szBuf, "%*s %f %f %f", &fR, &fG, &fB);
			MtlTex[szMtlName].Mtl.Diffuse.r = fR;
			MtlTex[szMtlName].Mtl.Diffuse.g = fG;
			MtlTex[szMtlName].Mtl.Diffuse.b = fB;
			MtlTex[szMtlName].Mtl.Diffuse.a = 1.0f;
		}
		else if(IsStartWith(szBuf, "Ks"))
		{
			float fR, fG, fB;
			sscanf_s(szBuf, "%*s %f %f %f", &fR, &fG, &fB);
			MtlTex[szMtlName].Mtl.Specular.r = fR;
			MtlTex[szMtlName].Mtl.Specular.g = fG;
			MtlTex[szMtlName].Mtl.Specular.b = fB;
			MtlTex[szMtlName].Mtl.Specular.a = 1.0f;
		}
	}
	fclose(fp);
}

bool cObjParser::IsStartWith( char* szStr, char* szBeginStr )
{
	char* szTemp = strstr(szStr, szBeginStr);
	if (szTemp)
		return true;
	return false;
}

void cObjParser::LoadSurface( IN char* szFileName,
							 OUT std::vector<D3DXVECTOR3>& vSurface,
							 IN D3DXMATRIXA16* mMat /*= NULL*/ )
{
	Clear();

	char szBuf[1024];

	FILE* fp;
	fopen_s(&fp, szFileName, "r");

	while(!feof(fp))
	{
		fgets(szBuf, 1024, fp);
		if(szBuf[0] == '#')
		{
			continue;
		}
		else if(IsStartWith(szBuf, "v "))
		{
			float fX, fY, fZ;
			sscanf_s(szBuf, "%*s %f %f %f", &fX, &fY, &fZ);
			
			D3DXVECTOR3 v = D3DXVECTOR3(fX, fY, fZ);
			if(mMat)
			{
				D3DXVec3TransformCoord(&v, &v, mMat);
			}

			m_V.push_back(v);
		}
		else if(IsStartWith(szBuf, "f "))
		{
			int nIdx[3];
			sscanf_s(szBuf, "%*s %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d",
				&nIdx[0], &nIdx[1], &nIdx[2]);

			for (int i = 0; i < 3; ++i)
			{
				vSurface.push_back(m_V[nIdx[i] - 1]);
			}
		}
	}
	fclose(fp);
}

void cObjParser::Clear()
{
	m_V.clear();
	m_VT.clear();
	m_VN.clear();
}

