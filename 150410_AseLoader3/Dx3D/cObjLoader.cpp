#include "StdAfx.h"
#include "cObjLoader.h"
#include "cMtlTex.h"
#include "cGroup.h"

cObjLoader::cObjLoader(void)
	: m_pHead(NULL)
{
}


cObjLoader::~cObjLoader(void)
{
}

cGroup* cObjLoader::Load( char* szFullPath )
{
	std::vector<D3DXVECTOR3>	vecV;
	std::vector<D3DXVECTOR2>	vecVT;
	std::vector<D3DXVECTOR3>	vecVN;
	std::vector<ST_PNT_VERTEX>	vecVertex;
	std::string					sMtlName;
	

	FILE* fp = NULL;
	
	fopen_s(&fp, szFullPath, "r");

	while(true)
	{
		char szBuf[1024];
		fgets(szBuf, 1024, fp);
		
		if(szBuf[0] == '#')
		{
			continue;
		}
		else if(szBuf[0] == 'm')
		{
			char szMtlPath[1024] = {0, };
			sscanf_s(szBuf, "%*s %s", szMtlPath, sizeof(szMtlPath));
			LoadMtlLib(szMtlPath);
		}
		else if(szBuf[0] == 'g')
		{
			if(!vecVertex.empty())
			{
				cGroup* pGroup = new cGroup;
				pGroup->BuildVertexBuffer(vecVertex);
				vecVertex.clear();
				if(m_pHead)
				{
					pGroup->m_pNext = m_pHead;
				}
				pGroup->SetMtlTex(m_mapMtlTex[sMtlName]);
				m_pHead = pGroup;
			}
		}
		else if(szBuf[0] == 'v')
		{
			if(szBuf[1] == ' ')
			{
				float x, y, z;
				sscanf_s(szBuf, "%*s %f %f %f", &x, &y, &z);
				vecV.push_back(D3DXVECTOR3(x, y, z));
			}
			else if(szBuf[1] == 't')
			{
				float u, v;
				sscanf_s(szBuf, "%*s %f %f %*f", &u, &v);
				vecVT.push_back(D3DXVECTOR2(u, v));
			}
			else if(szBuf[1] == 'n')
			{
				float x, y, z;
				sscanf_s(szBuf, "%*s %f %f %f", &x, &y, &z);
				vecVN.push_back(D3DXVECTOR3(x, y, z));
			}
		}
		else if(szBuf[0] == 'f')
		{
			int idx[3][3];
			sscanf_s(szBuf, "%*s %d/%d/%d %d/%d/%d %d/%d/%d",
				&idx[0][0], &idx[0][1], &idx[0][2],
				&idx[1][0], &idx[1][1], &idx[1][2],
				&idx[2][0], &idx[2][1], &idx[2][2]);
			for (int i = 0; i < 3; ++i)
			{
				ST_PNT_VERTEX v;
				v.p = vecV[idx[i][0] - 1];
				v.t = vecVT[idx[i][1] - 1];
				v.n = vecVN[idx[i][2] - 1];
				vecVertex.push_back(v);
			}
		}
		else if(szBuf[0] == 'u')
		{
			char szMtlName[1024] = {0, };
			sscanf_s(szBuf, "%*s %s", szMtlName, sizeof(szMtlName));
			sMtlName = std::string(szMtlName);
		}
		if(feof(fp))
			break;
	}
	
	fclose(fp);

	for each(auto it in m_mapMtlTex)
	{
		SAFE_RELEASE(it.second);
	}

	return m_pHead;
}

void cObjLoader::LoadMtlLib( char* szFullPath )
{
	std::string sMtlName;

	FILE* fp = NULL;

	fopen_s(&fp, szFullPath, "r");

	while(true)
	{
		char szBuf[1024];
		fgets(szBuf, 1024, fp);

		if(feof(fp))
			break;

		if(szBuf[0] == '#')
		{
			continue;
		}
		else if(szBuf[0] == 'n')
		{
			char szMtlName[1024] = {0, };
			sscanf_s(szBuf, "%*s %s", szMtlName, sizeof(szMtlName));
			
			sMtlName = std::string(szMtlName);

			m_mapMtlTex[sMtlName] = new cMtlTex;
		}
		else if(szBuf[0] == 'K')
		{
			if(szBuf[1] == 'a')
			{
				float r, g, b;
				sscanf_s(szBuf, "%*s %f %f %f", &r, &g, &b);
				m_mapMtlTex[sMtlName]->m_stMtl.Ambient.r = r;
				m_mapMtlTex[sMtlName]->m_stMtl.Ambient.g = g;
				m_mapMtlTex[sMtlName]->m_stMtl.Ambient.b = b;
				m_mapMtlTex[sMtlName]->m_stMtl.Ambient.a = 1.0f;
			}
			else if(szBuf[1] == 'd')
			{
				float r, g, b;
				sscanf_s(szBuf, "%*s %f %f %f", &r, &g, &b);
				m_mapMtlTex[sMtlName]->m_stMtl.Diffuse.r = r;
				m_mapMtlTex[sMtlName]->m_stMtl.Diffuse.g = g;
				m_mapMtlTex[sMtlName]->m_stMtl.Diffuse.b = b;
				m_mapMtlTex[sMtlName]->m_stMtl.Diffuse.a = 1.0f;
			}
			else if(szBuf[1] == 's')
			{
				float r, g, b;
				sscanf_s(szBuf, "%*s %f %f %f", &r, &g, &b);
				m_mapMtlTex[sMtlName]->m_stMtl.Specular.r = r;
				m_mapMtlTex[sMtlName]->m_stMtl.Specular.g = g;
				m_mapMtlTex[sMtlName]->m_stMtl.Specular.b = b;
				m_mapMtlTex[sMtlName]->m_stMtl.Specular.a = 1.0f;
			}
		}
		else if(szBuf[0] == 'm')
		{
			char szTextureName[1024] = {0, };
			sscanf_s(szBuf, "%*s %s", szTextureName, sizeof(szTextureName));
			m_mapMtlTex[sMtlName]->SetTexture(szTextureName);
		}
	}

	fclose(fp);
}
