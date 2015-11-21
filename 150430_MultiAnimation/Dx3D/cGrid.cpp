#include "StdAfx.h"
#include "cGrid.h"
#include "cPyramid.h"

cGrid::cGrid(void)
{
}


cGrid::~cGrid(void)
{
	for each(auto p in m_vecPyramid)
	{
		SAFE_DELETE(p);
	}
}

void cGrid::Setup( int nHalfTile /*= 30*/, float fWidth /*= 1.0f*/ )
{
	float fMax = nHalfTile * fWidth;
	float fMin = -fMax;

	ST_PC_VERTEX v;

	for (int i = 1; i <= nHalfTile; ++i)
	{
		v.c = (i % 5 == 0) ? D3DCOLOR_XRGB(255, 255, 255) : D3DCOLOR_XRGB(128, 128, 128);
		
		v.p = D3DXVECTOR3(fMin, 0, i * fWidth); 
		m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(fMax, 0, i * fWidth); 
		m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(fMin, 0, -i * fWidth); 
		m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(fMax, 0, -i * fWidth); 
		m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(i * fWidth, 0, fMin); 
		m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(i * fWidth, 0, fMax); 
		m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(-i * fWidth, 0, fMin); 
		m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(-i * fWidth, 0, fMax); 
		m_vecVertex.push_back(v);
	}

	v.c = D3DCOLOR_XRGB(255, 0, 0);
	v.p = D3DXVECTOR3(fMin, 0, 0); 
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(fMax, 0, 0); 
	m_vecVertex.push_back(v);


	v.c = D3DCOLOR_XRGB(0, 255, 0);
	v.p = D3DXVECTOR3(0, fMin, 0); 
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(0, fMax, 0); 
	m_vecVertex.push_back(v);

	v.c = D3DCOLOR_XRGB(0, 0, 255);
	v.p = D3DXVECTOR3(0, 0, fMin); 
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(0, 0, fMax); 
	m_vecVertex.push_back(v);

	D3DXMATRIXA16 matWorld, matRot, matScale;
	D3DXMatrixScaling(&matScale, 0.1f, 2.0f, 0.1f);

	cPyramid* pPyramid = new cPyramid;
	D3DXMatrixRotationZ(&matRot, D3DX_PI / 2.0f);
	matWorld = matScale * matRot;
	pPyramid->Setup(D3DCOLOR_XRGB(255, 0, 0), matWorld);
	m_vecPyramid.push_back(pPyramid);

	pPyramid = new cPyramid;
	D3DXMatrixRotationZ(&matRot, D3DX_PI);
	matWorld = matScale * matRot;
	pPyramid->Setup(D3DCOLOR_XRGB(0, 255, 0), matWorld);
	m_vecPyramid.push_back(pPyramid);

	pPyramid = new cPyramid;
	D3DXMatrixRotationX(&matRot, -D3DX_PI / 2.0f);
	matWorld = matScale * matRot;
	pPyramid->Setup(D3DCOLOR_XRGB(0, 0, 255), matWorld);
	m_vecPyramid.push_back(pPyramid);
}

void cGrid::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST,
		m_vecVertex.size() / 2,
		&m_vecVertex[0],
		sizeof(ST_PC_VERTEX));

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	for each(auto p in m_vecPyramid)
	{
		p->Render();
	}
}
