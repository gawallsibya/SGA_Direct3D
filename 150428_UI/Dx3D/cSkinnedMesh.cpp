#include "StdAfx.h"
#include "cSkinnedMesh.h"
#include "cAllocateHierarchy.h"

cSkinnedMesh::cSkinnedMesh(void)
	: m_pAnimController(NULL)
	, m_fBlendTime(0.2f)
	, m_fPassedBlendTime(0.0f)
	, m_isAnimBlending(false)
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

	SetupBoneMatrixPtrs((ST_BONE*)m_pRoot);
}

void cSkinnedMesh::Update()
{
	if(m_isAnimBlending)
	{
		m_fPassedBlendTime += g_pTimeManager->GetElapsedTime();

		if(m_fPassedBlendTime > m_fBlendTime)
		{
			m_isAnimBlending = false;
			m_pAnimController->SetTrackWeight(0, 1.0f);
			m_pAnimController->SetTrackEnable(1, false);
		}
		else
		{
			float fWeight = m_fPassedBlendTime / m_fBlendTime;
			m_pAnimController->SetTrackWeight(0, fWeight);
			m_pAnimController->SetTrackWeight(1, 1.0f - fWeight);
		}
	}

	m_pAnimController->AdvanceTime(g_pTimeManager->GetElapsedTime(), NULL);

	if (m_pRoot)
	{
		((ST_BONE*)m_pRoot)->Update(NULL);
	}

	UpdateSkinnedMesh((ST_BONE*)m_pRoot);
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

	if(pBone->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;
		if(pBoneMesh->pSkinInfo)
		{
			LPD3DXSKININFO pSkinInfo = pBoneMesh->pSkinInfo;
			
			DWORD dwNumBones = pSkinInfo->GetNumBones();
			for (DWORD i = 0; i < dwNumBones; ++i)
			{
				LPCSTR szBoneName = pSkinInfo->GetBoneName(i);
				ST_BONE* pBone = (ST_BONE*)D3DXFrameFind(m_pRoot, szBoneName);
				pBoneMesh->ppBoneMatrixPtrs[i] = &(pBone->matWorld);
			}
		}
	}

	//재귀적으로 모든 프레임에 대해서 실행.
	if(pBone->pFrameFirstChild)
	{
		SetupBoneMatrixPtrs((ST_BONE*)pBone->pFrameFirstChild);
	}

	if(pBone->pFrameSibling)
	{
		SetupBoneMatrixPtrs((ST_BONE*)pBone->pFrameSibling);
	}
}

void cSkinnedMesh::UpdateSkinnedMesh( ST_BONE* pBone )
{
	// pCurrentBoneMatrices 를 계산하시오
	// pCurrentBoneMatrices = pBoneOffsetMatrices * ppBoneMatrixPtrs 
	if(pBone->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;
		if(pBoneMesh->pSkinInfo)
		{
			LPD3DXSKININFO pSkinInfo = pBoneMesh->pSkinInfo;

			DWORD dwNumBones = pSkinInfo->GetNumBones();
			for (DWORD i = 0; i < dwNumBones; ++i)
			{
				pBoneMesh->pCurrentBoneMatrices[i] =
					pBoneMesh->pBoneOffsetMatrices[i] * *(pBoneMesh->ppBoneMatrixPtrs[i]);
			}
		}

		BYTE* src = NULL;
		BYTE* dest = NULL;

		pBoneMesh->pOrigMesh->LockVertexBuffer( D3DLOCK_READONLY, (void**)&src );
		pBoneMesh->MeshData.pMesh->LockVertexBuffer( 0, (void**)&dest );

		//MeshData.pMesh을 업데이트 시켜준다.
		pBoneMesh->pSkinInfo->UpdateSkinnedMesh(
			pBoneMesh->pCurrentBoneMatrices, NULL, src, dest );

		pBoneMesh->MeshData.pMesh->UnlockVertexBuffer();
		pBoneMesh->pOrigMesh->UnlockVertexBuffer();
	}

	//재귀적으로 모든 프레임에 대해서 실행.

	if(pBone->pFrameFirstChild)
	{
		UpdateSkinnedMesh((ST_BONE*)pBone->pFrameFirstChild);
	}

	if(pBone->pFrameSibling)
	{
		UpdateSkinnedMesh((ST_BONE*)pBone->pFrameSibling);
	}
}

void cSkinnedMesh::SetAnimationIndex( int n )
{
	if(m_pAnimController == NULL)
		return;
	LPD3DXANIMATIONSET pAnimSet = NULL;
	m_pAnimController->GetAnimationSet(n, &pAnimSet);
	m_pAnimController->SetTrackAnimationSet(0, pAnimSet);
	SAFE_RELEASE(pAnimSet);
}

void cSkinnedMesh::SetAnimationIndexBlend( int n )
{
	if(m_pAnimController == NULL)
		return;
	
	LPD3DXANIMATIONSET pNewAnimSet = NULL;
	LPD3DXANIMATIONSET pOldAnimSet = NULL;

	D3DXTRACK_DESC desc;
	m_pAnimController->GetTrackDesc(0, &desc);

	m_pAnimController->GetTrackAnimationSet(0, &pOldAnimSet);
	m_pAnimController->SetTrackAnimationSet(1, pOldAnimSet);
	
	m_pAnimController->GetAnimationSet(n, &pNewAnimSet);
	m_pAnimController->SetTrackAnimationSet(0, pNewAnimSet);
	m_pAnimController->SetTrackPosition(0, 0.0);
	m_pAnimController->SetTrackDesc(1, &desc);

	SAFE_RELEASE(pNewAnimSet);
	SAFE_RELEASE(pOldAnimSet);

	m_isAnimBlending = true;
	m_fPassedBlendTime = 0.f;
}
