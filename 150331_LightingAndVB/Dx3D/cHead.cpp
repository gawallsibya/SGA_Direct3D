#include "StdAfx.h"
#include "cHead.h"


cHead::cHead(void)
{
}


cHead::~cHead(void)
{
}

void cHead::Setup()
{
	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));

	m_stMtl.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtl.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtl.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtl.Power = 5.0f;

	ST_PNT_VERTEX v;
	//¸Ó¸®
	v.n = D3DXVECTOR3(0, 0, -1);
	v.p = D3DXVECTOR3(-1, 0, -1); v.t = D3DXVECTOR2( 0.125f,  0.5f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, 2, -1); v.t = D3DXVECTOR2( 0.125f, 0.25f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1, 0, -1); v.t = D3DXVECTOR2(  0.25f,  0.5f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, 2, -1); v.t = D3DXVECTOR2( 0.125f, 0.25f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1, 2, -1); v.t = D3DXVECTOR2(  0.25f, 0.25f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1, 0, -1); v.t = D3DXVECTOR2(  0.25f,  0.5f); m_vecVertex.push_back(v);

	v.n = D3DXVECTOR3(-1, 0, 0);
	v.p = D3DXVECTOR3(-1, 0,  1); v.t = D3DXVECTOR2(   0.0f,  0.5f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, 2,  1); v.t = D3DXVECTOR2(   0.0f, 0.25f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, 0, -1); v.t = D3DXVECTOR2( 0.125f,  0.5f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, 2,  1); v.t = D3DXVECTOR2(   0.0f, 0.25f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, 2, -1); v.t = D3DXVECTOR2( 0.125f, 0.25f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, 0, -1); v.t = D3DXVECTOR2( 0.125f,  0.5f); m_vecVertex.push_back(v);

	v.n = D3DXVECTOR3(1, 0, 0);
	v.p = D3DXVECTOR3( 1, 0, -1); v.t = D3DXVECTOR2(  0.25f,  0.5f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1, 2, -1); v.t = D3DXVECTOR2(  0.25f, 0.25f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1, 0,  1); v.t = D3DXVECTOR2( 0.375f,  0.5f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1, 2, -1); v.t = D3DXVECTOR2(  0.25f, 0.25f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1, 2,  1); v.t = D3DXVECTOR2( 0.375f, 0.25f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1, 0,  1); v.t = D3DXVECTOR2( 0.375f,  0.5f); m_vecVertex.push_back(v);

	v.n = D3DXVECTOR3(0, 0, 1);
	v.p = D3DXVECTOR3( 1, 0,  1); v.t = D3DXVECTOR2( 0.375f,  0.5f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1, 2,  1); v.t = D3DXVECTOR2( 0.375f, 0.25f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, 0,  1); v.t = D3DXVECTOR2(   0.5f,  0.5f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1, 2,  1); v.t = D3DXVECTOR2( 0.375f, 0.25f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, 2,  1); v.t = D3DXVECTOR2(   0.5f, 0.25f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, 0,  1); v.t = D3DXVECTOR2(   0.5f,  0.5f); m_vecVertex.push_back(v);

	v.n = D3DXVECTOR3(0, 1, 0);
	v.p = D3DXVECTOR3(-1, 2, -1); v.t = D3DXVECTOR2( 0.125f, 0.25f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, 2,  1); v.t = D3DXVECTOR2( 0.125f,  0.0f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1, 2, -1); v.t = D3DXVECTOR2(  0.25f, 0.25f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, 2,  1); v.t = D3DXVECTOR2( 0.125f,  0.0f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1, 2,  1); v.t = D3DXVECTOR2(  0.25f,  0.0f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1, 2, -1); v.t = D3DXVECTOR2(  0.25f, 0.25f); m_vecVertex.push_back(v);

	v.n = D3DXVECTOR3(0, -1, 0);
	v.p = D3DXVECTOR3(-1, 0,  1); v.t = D3DXVECTOR2(  0.25f, 0.25f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, 0, -1); v.t = D3DXVECTOR2(  0.25f,  0.0f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1, 0,  1); v.t = D3DXVECTOR2( 0.375f, 0.25f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, 0, -1); v.t = D3DXVECTOR2(  0.25f,  0.0f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1, 0, -1); v.t = D3DXVECTOR2( 0.375f,  0.0f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1, 0,  1); v.t = D3DXVECTOR2( 0.375f, 0.25f); m_vecVertex.push_back(v);
}

void cHead::Update( D3DXMATRIXA16* pParent )
{
	D3DXMatrixTranslation(&m_matLocal, 0.0f, 1.5f, 0.0f);
	m_matWorld = m_matLocal * (*pParent);
}

