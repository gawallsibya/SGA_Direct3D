#include "StdAfx.h"
#include "cSkinnedMesh.h"
#include "cAllocateHierarchy.h"

cSkinnedMesh::cSkinnedMesh(void)
{
}


cSkinnedMesh::~cSkinnedMesh(void)
{
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
		NULL);
}

void cSkinnedMesh::Update()
{
	if (m_pRoot)
	{
		((ST_BONE*)m_pRoot)->Update(NULL);
	}
}

void cSkinnedMesh::Render()
{
	if (m_pRoot)
	{
		((ST_BONE*)m_pRoot)->Render();
	}
}
