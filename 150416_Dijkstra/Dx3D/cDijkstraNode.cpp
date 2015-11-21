#include "StdAfx.h"
#include "cDijkstraNode.h"


cDijkstraNode::cDijkstraNode(void)
	: m_nNodeId(-1)
	, m_nVia(-1)
	, m_isVisited(false)
	, m_fCost(COST_INFINITY)
	, m_vPosition(0, 0, 0)
	, m_eState(E_NORMAL)
	, m_fRadius(0.2f)
{
	for (int i = 0; i < E_STATE_CNT; ++i)
	{
		ZeroMemory(&m_stMtl[i], sizeof(D3DMATERIAL9));
	}
	m_stMtl[E_NORMAL].Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtl[E_NORMAL].Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtl[E_NORMAL].Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);

	m_stMtl[E_SELECTED].Ambient = D3DXCOLOR(0.7f, 0.0f, 0.0f, 1.0f);
	m_stMtl[E_SELECTED].Diffuse = D3DXCOLOR(0.7f, 0.0f, 0.0f, 1.0f);
	m_stMtl[E_SELECTED].Specular = D3DXCOLOR(0.7f, 0.0f, 0.0f, 1.0f);

	m_stMtl[E_MOUSE_OVER].Ambient = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
	m_stMtl[E_MOUSE_OVER].Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
	m_stMtl[E_MOUSE_OVER].Specular = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);

	m_stMtl[E_PATH].Ambient = D3DXCOLOR(0.0f, 0.7f, 0.7f, 1.0f);
	m_stMtl[E_PATH].Diffuse = D3DXCOLOR(0.0f, 0.7f, 0.7f, 1.0f);
	m_stMtl[E_PATH].Specular = D3DXCOLOR(0.0f, 0.7f, 0.7f, 1.0f);
}


cDijkstraNode::~cDijkstraNode(void)
{
}

void cDijkstraNode::Render( LPD3DXMESH pSphere )
{
	
	D3DXMATRIXA16 matWorld;
	D3DXMatrixTranslation(&matWorld, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	g_pD3DDevice->SetMaterial(&m_stMtl[m_eState]);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	pSphere->DrawSubset(0);
}
