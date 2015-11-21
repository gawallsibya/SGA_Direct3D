#include "StdAfx.h"
#include "cFrustum.h"


cFrustum::cFrustum(void)
{
}


cFrustum::~cFrustum(void)
{
	
}

void cFrustum::Setup()
{
	m_vecProjPosition.push_back(D3DXVECTOR3(-1, -1, 0));
	m_vecProjPosition.push_back(D3DXVECTOR3(-1,  1, 0));
	m_vecProjPosition.push_back(D3DXVECTOR3( 1,  1, 0));
	m_vecProjPosition.push_back(D3DXVECTOR3( 1, -1, 0));
	m_vecProjPosition.push_back(D3DXVECTOR3(-1, -1, 1));
	m_vecProjPosition.push_back(D3DXVECTOR3(-1,  1, 1));
	m_vecProjPosition.push_back(D3DXVECTOR3( 1,  1, 1));
	m_vecProjPosition.push_back(D3DXVECTOR3( 1, -1, 1));

	m_vecPlane.resize(6);
}

void cFrustum::Update()
{
	std::vector<D3DXVECTOR3>	vecWorldPosition;

	vecWorldPosition.resize(m_vecProjPosition.size());

	D3DXMATRIXA16 matProj, matView;
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	for (size_t i = 0; i < m_vecProjPosition.size(); ++i)
	{
		D3DXVec3Unproject(
			&vecWorldPosition[i],
			&m_vecProjPosition[i],
			NULL,
			&matProj,
			&matView,
			NULL);
	}

	// 앞
	D3DXPlaneFromPoints(&m_vecPlane[0],
		&vecWorldPosition[0],
		&vecWorldPosition[1],
		&vecWorldPosition[2]);

	// 뒤
	D3DXPlaneFromPoints(&m_vecPlane[1],
		&vecWorldPosition[6],
		&vecWorldPosition[5],
		&vecWorldPosition[7]);
	
	// 위
	D3DXPlaneFromPoints(&m_vecPlane[2],
		&vecWorldPosition[1],
		&vecWorldPosition[5],
		&vecWorldPosition[6]);

	// 아래
	D3DXPlaneFromPoints(&m_vecPlane[3],
		&vecWorldPosition[0],
		&vecWorldPosition[3],
		&vecWorldPosition[7]);

	// 좌
	D3DXPlaneFromPoints(&m_vecPlane[4],
		&vecWorldPosition[1],
		&vecWorldPosition[0],
		&vecWorldPosition[5]);

	// 우
	D3DXPlaneFromPoints(&m_vecPlane[5],
		&vecWorldPosition[2],
		&vecWorldPosition[6],
		&vecWorldPosition[7]);
}

bool cFrustum::IsIn( D3DXVECTOR3& vCenter, float fRadius )
{
	for each(D3DXPLANE p in m_vecPlane)
	{
		if(D3DXPlaneDotCoord(&p, &vCenter) > fRadius)
			return false;
	}
	return true;
}
