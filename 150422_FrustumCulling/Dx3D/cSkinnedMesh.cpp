#include "StdAfx.h"
#include "cSkinnedMesh.h"
#include "cAllocateHierarchy.h"

cSkinnedMesh::cSkinnedMesh(void)
	: m_pAnimController(NULL)
{
}


cSkinnedMesh::~cSkinnedMesh(void)
{
	SAFE_RELEASE(m_pAnimController);

	cAllocateHierarchy ah;
	D3DXFrameDestroy(m_pRoot, &ah);
}

void cSkinnedMesh::Setup( char* szFolder, char* szFile )
{
	std::string sFullPath(szFolder);
	sFullPath += (std::string("/") + std::string(szFile));

	cAllocateHierarchy ah;
	
	ah.SetFolder(szFolder);

	D3DXLoadMeshHierarchyFromX(sFullPath.c_str(),
		D3DXMESH_MANAGED,
		g_pD3DDevice,
		&ah,
		NULL,
		&m_pRoot,
		&m_pAnimController);

	//SetupBoneMatrixPtrs
}

void cSkinnedMesh::Update()
{
	m_pAnimController->AdvanceTime(0.1f, NULL);

	if (m_pRoot)
	{
		((ST_BONE*)m_pRoot)->Update(NULL);
	}

	//UpdateSkinnedMesh
}

void cSkinnedMesh::Render()
{
	if (m_pRoot)
	{
		((ST_BONE*)m_pRoot)->Render();
	}
}

void cSkinnedMesh::SetupBoneMatrixPtrs( ST_BONE* pBone )
{
	// 각 프레임의 메시 컨테이너에 있는 pSkinInfo를 이용하여 영향받는 모든 
	// 프레임의 매트릭스를 ppBoneMatrixPtrs에 연결한다.

	// pSkinInfo->GetNumBones() 으로 영향받는 본의 개수를 찾음.
	// pSkinInfo->GetBoneName(i) 로 i번 프레임의 이름을 찾음
	// D3DXFrameFind(루트 프레임, 프레임 이름) 로 프레임을 찾음.
	// 찾아서 월드매트릭스를 걸어줘라.

	//재귀적으로 모든 프레임에 대해서 실행.
}

void cSkinnedMesh::UpdateSkinnedMesh( ST_BONE* pBone )
{
	// pCurrentBoneMatrices 를 계산하시오
	// pCurrentBoneMatrices = pBoneOffsetMatrices * ppBoneMatrixPtrs 

	/*
	BYTE* src = NULL;
	BYTE* dest = NULL;

	pBoneMesh->pOrigMesh->LockVertexBuffer( D3DLOCK_READONLY, (void**)&src );
	pBoneMesh->MeshData.pMesh->LockVertexBuffer( 0, (void**)&dest );

	//MeshData.pMesh을 업데이트 시켜준다.
	pBoneMesh->pSkinInfo->UpdateSkinnedMesh(
		pBoneMesh->pCurrentBoneMatrices, NULL, src, dest );

	pBoneMesh->MeshData.pMesh->UnlockVertexBuffer();
	pBoneMesh->pOrigMesh->UnlockVertexBuffer();
	*/

	//재귀적으로 모든 프레임에 대해서 실행.
}
