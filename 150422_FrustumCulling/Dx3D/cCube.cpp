#include "StdAfx.h"
#include "cCube.h"


cCube::cCube(void)
{
}

cCube::~cCube(void)
{
}

void cCube::Setup()
{
	ST_PC_VERTEX v;
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-1, -1, -1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1,  1, -1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1,  1, -1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1, -1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1,  1, -1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1, -1, -1); m_vecVertex.push_back(v);
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-1, -1,  1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1,  1,  1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1,  1,  1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1,  1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1, -1,  1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1,  1,  1); m_vecVertex.push_back(v);
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-1, -1,  1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1,  1,  1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1,  1, -1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1,  1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1,  1, -1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1, -1); m_vecVertex.push_back(v);
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3( 1, -1, -1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1,  1, -1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1,  1,  1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1, -1, -1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1,  1,  1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1, -1,  1); m_vecVertex.push_back(v);
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-1,  1, -1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1,  1,  1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1,  1,  1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1,  1, -1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1,  1,  1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1,  1, -1); m_vecVertex.push_back(v);
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-1, -1,  1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1, -1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1, -1, -1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1,  1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1, -1, -1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1, -1,  1); m_vecVertex.push_back(v);
}

void cCube::Update()
{
	cCharacter::Update();
}

void cCube::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex.size() / 3, 
		&m_vecVertex[0],
		sizeof(ST_PC_VERTEX));
}
