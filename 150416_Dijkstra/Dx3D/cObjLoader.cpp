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
	
	DWORD dwAttrId = 0;

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
			m_mapMtlTex[sMtlName]->m_dwAttrId = dwAttrId;
			++dwAttrId;
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

LPD3DXMESH cObjLoader::LoadMesh( char* szFullPath, std::vector<cMtlTex*>& vecMtlTex )
{
	std::vector<D3DXVECTOR3>	vecV;
	std::vector<D3DXVECTOR2>	vecVT;
	std::vector<D3DXVECTOR3>	vecVN;
	std::vector<DWORD>			vecAttrBuffer;
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
			vecAttrBuffer.push_back(m_mapMtlTex[sMtlName]->m_dwAttrId);
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
	
	vecMtlTex.resize(m_mapMtlTex.size());

	for each(auto it in m_mapMtlTex)
	{
		vecMtlTex[it.second->m_dwAttrId] = it.second;
	}

	LPD3DXMESH pMesh = NULL;

	D3DXCreateMeshFVF(vecVertex.size() / 3,
		vecVertex.size(),
		D3DXMESH_MANAGED,
		ST_PNT_VERTEX::FVF,
		g_pD3DDevice,
		&pMesh);

	ST_PNT_VERTEX* pV = NULL;
	pMesh->LockVertexBuffer(0, (LPVOID*)&pV);
	memcpy(pV, &vecVertex[0], vecVertex.size() * sizeof(ST_PNT_VERTEX));
	pMesh->UnlockVertexBuffer();

	WORD* pI = NULL;
	pMesh->LockIndexBuffer(0, (LPVOID*)&pI);
	for (size_t i = 0; i < vecVertex.size(); ++i)
	{
		pI[i] = i;
	}
	pMesh->UnlockIndexBuffer();

	DWORD* pA = NULL;
	pMesh->LockAttributeBuffer(0, &pA);
	memcpy(pA, &vecAttrBuffer[0], vecAttrBuffer.size() * sizeof(DWORD));
	pMesh->UnlockAttributeBuffer();

	std::vector<DWORD> vecAdjBuffer(vecVertex.size());
	pMesh->GenerateAdjacency(0.0f, &vecAdjBuffer[0]);

	pMesh->OptimizeInplace(
		D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_COMPACT |
		D3DXMESHOPT_VERTEXCACHE,
		&vecAdjBuffer[0]
	,0, 0, 0);

	return pMesh;
}
