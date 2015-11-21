#include "StdAfx.h"
#include "cPyramid.h"


cPyramid::cPyramid(void)
{
}


cPyramid::~cPyramid(void)
{
}

void cPyramid::Setup(D3DCOLOR c, D3DXMATRIXA16& matWorld)
{
	m_matWorld = matWorld;

	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
	m_stMtl.Ambient = D3DXCOLOR(c);
	m_stMtl.Diffuse = D3DXCOLOR(c);
	m_stMtl.Specular = D3DXCOLOR(c);

	ST_PN_VERTEX v;

	v.p = D3DXVECTOR3( 0,  0,  0);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3( 1, -1, -1);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1, -1, -1);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3( 0,  0,  0);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3( 1, -1,  1);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3( 1, -1, -1);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3( 0,  0,  0);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1, -1,  1);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3( 1, -1,  1);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3( 0,  0,  0);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1, -1, -1);
	m_vecVertex.push_back(v);
	
	v.p = D3DXVECTOR3(-1, -1,  1);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1, -1, -1);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3( 1, -1, -1);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3( 1, -1,  1);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1, -1, -1);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3( 1, -1,  1);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1, -1,  1);
	m_vecVertex.push_back(v);

	for (size_t i = 0; i < m_vecVertex.size(); i += 3)
	{
		D3DXVECTOR3 v0 = m_vecVertex[i].p;
		D3DXVECTOR3 v1 = m_vecVertex[i + 1].p;
		D3DXVECTOR3 v2 = m_vecVertex[i + 2].p;
		
		D3DXVECTOR3 v01 = v1 - v0;
		D3DXVECTOR3 v02 = v2 - v0;

		D3DXVECTOR3 n;
		D3DXVec3Cross(&n, &v01, &v02);
		D3DXVec3Normalize(&n, &n);

		m_vecVertex[i].n = n;
		m_vecVertex[i + 1].n = n;
		m_vecVertex[i + 2].n = n;
	}
}

void cPyramid::Render()
{
	g_pD3DDevice->SetMaterial(&m_stMtl);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetFVF(ST_PN_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex.size() / 3,
		&m_vecVertex[0],
		sizeof(ST_PN_VERTEX));
}
