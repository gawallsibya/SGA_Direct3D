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
	// �� �������� �޽� �����̳ʿ� �ִ� pSkinInfo�� �̿��Ͽ� ����޴� ��� 
	// �������� ��Ʈ������ ppBoneMatrixPtrs�� �����Ѵ�.

	// pSkinInfo->GetNumBones() ���� ����޴� ���� ������ ã��.
	// pSkinInfo->GetBoneName(i) �� i�� �������� �̸��� ã��
	// D3DXFrameFind(��Ʈ ������, ������ �̸�) �� �������� ã��.
	// ã�Ƽ� �����Ʈ������ �ɾ����.

	//��������� ��� �����ӿ� ���ؼ� ����.
}

void cSkinnedMesh::UpdateSkinnedMesh( ST_BONE* pBone )
{
	// pCurrentBoneMatrices �� ����Ͻÿ�
	// pCurrentBoneMatrices = pBoneOffsetMatrices * ppBoneMatrixPtrs 

	/*
	BYTE* src = NULL;
	BYTE* dest = NULL;

	pBoneMesh->pOrigMesh->LockVertexBuffer( D3DLOCK_READONLY, (void**)&src );
	pBoneMesh->MeshData.pMesh->LockVertexBuffer( 0, (void**)&dest );

	//MeshData.pMesh�� ������Ʈ �����ش�.
	pBoneMesh->pSkinInfo->UpdateSkinnedMesh(
		pBoneMesh->pCurrentBoneMatrices, NULL, src, dest );

	pBoneMesh->MeshData.pMesh->UnlockVertexBuffer();
	pBoneMesh->pOrigMesh->UnlockVertexBuffer();
	*/

	//��������� ��� �����ӿ� ���ؼ� ����.
}
