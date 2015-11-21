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

	// 이름을 복사해주세요.

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
	pSkinInfo->AddRef();
	pBoneMesh->pSkinInfo = pSkinInfo;
	// step 1. pSkinInfo 저장
	// step 2. 원본 메쉬 복사
	// step 3. pSkinInfo->GetNumBones()를 통해 영향력을 미치는 모든 본에 대한 매트릭스 들을 세팅
	// ppBoneMatrixPtrs, pBoneOffsetMatrices, pCurrentBoneMatrices를 동적할당
	// step 4. 동적 할당된 pBoneOffsetMatrices 매트릭스에 값 저장.
	// pSkinInfo->GetBoneOffsetMatrix(i)
	
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
