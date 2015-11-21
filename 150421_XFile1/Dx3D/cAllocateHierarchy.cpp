#include "StdAfx.h"
#include "cAllocateHierarchy.h"


cAllocateHierarchy::cAllocateHierarchy(void)
{
}


cAllocateHierarchy::~cAllocateHierarchy(void)
{
}

STDMETHODIMP cAllocateHierarchy::CreateFrame( THIS_ LPCSTR Name, LPD3DXFRAME *ppNewFrame )
{
	ST_BONE* pBone = new ST_BONE;
	ZeroMemory(pBone, sizeof(ST_BONE));

	D3DXMatrixIdentity(&pBone->matWorld);

	(*ppNewFrame) = pBone;

	return S_OK;
}

STDMETHODIMP cAllocateHierarchy::CreateMeshContainer( THIS_ LPCSTR Name,
	CONST D3DXMESHDATA *pMeshData,
	CONST D3DXMATERIAL *pMaterials, 
	CONST D3DXEFFECTINSTANCE *pEffectInstances,
	DWORD NumMaterials,
	CONST DWORD *pAdjacency,
	LPD3DXSKININFO pSkinInfo,
	LPD3DXMESHCONTAINER *ppNewMeshContainer )
{
	ST_BONE_MESH* pBoneMesh = new ST_BONE_MESH;
	ZeroMemory(pBoneMesh, sizeof(ST_BONE_MESH));

	pBoneMesh->MeshData.Type = pMeshData->Type;
	assert(pMeshData->Type == D3DXMESHTYPE_MESH);
	pMeshData->pMesh->AddRef();
	pBoneMesh->MeshData.pMesh = pMeshData->pMesh;

	for (DWORD i = 0; i < NumMaterials; ++i)
	{
		pBoneMesh->vecMaterial.push_back(pMaterials[i].MatD3D);
		std::string sTextureFile("/");
		sTextureFile += std::string(pMaterials[i].pTextureFilename);
		LPDIRECT3DTEXTURE9 pTexture = g_pTextureManager->GetTexture(m_sFolder + sTextureFile);
		pBoneMesh->vecTexture.push_back(pTexture);
	}

	if(pAdjacency)
	{
		pBoneMesh->pAdjacency = new DWORD[pMeshData->pMesh->GetNumVertices()];
		memcpy(pBoneMesh->pAdjacency, pAdjacency, pMeshData->pMesh->GetNumVertices() * sizeof(DWORD));
	}

	*ppNewMeshContainer = pBoneMesh;

	return S_OK;
}

STDMETHODIMP cAllocateHierarchy::DestroyFrame( THIS_ LPD3DXFRAME pFrameToFree )
{
	return S_OK;
}

STDMETHODIMP cAllocateHierarchy::DestroyMeshContainer( THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree )
{
	SAFE_RELEASE(pMeshContainerToFree->MeshData.pMesh);
	SAFE_DELETE_ARRAY(pMeshContainerToFree->pAdjacency);

	return S_OK;
}
