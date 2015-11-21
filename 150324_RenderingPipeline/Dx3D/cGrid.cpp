#include "StdAfx.h"
#include "cGrid.h"
#include "cPyramid.h"

cGrid::cGrid(void)
{
}


cGrid::~cGrid(void)
{
}

void cGrid::Setup(int nNumHalfLine, float fInterval)
{
	D3DXMATRIXA16 matWorld, matR, matS;
	
	D3DXMatrixScaling(&matS, 0.1f, 2.0f, 0.1f);

	cPyramid* pPyramid = NULL;

	pPyramid = new cPyramid;
	D3DXMatrixRotationZ(&matR, D3DX_PI / 2.0f);
	matWorld = matS * matR;
	pPyramid->Setup(D3DCOLOR_XRGB(255, 0, 0), &matWorld);
	m_vecPyramid.push_back(pPyramid);

	pPyramid = new cPyramid;
	D3DXMatrixRotationZ(&matR, D3DX_PI);
	matWorld = matS * matR;
	pPyramid->Setup(D3DCOLOR_XRGB(0, 255, 0), &matWorld);
	m_vecPyramid.push_back(pPyramid);

	pPyramid = new cPyramid;
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0f);
	matWorld = matS * matR;
	pPyramid->Setup(D3DCOLOR_XRGB(0, 0, 255), &matWorld);
	m_vecPyramid.push_back(pPyramid);

	float fMax = nNumHalfLine * fInterval;
	float fMin = -fMax;
	
	ST_PC_VERTEX v;
	
	v.c = D3DCOLOR_XRGB(255, 255, 255);

	for (int i = 1; i <= nNumHalfLine; ++i)
	{
		if(i % 5 == 0)
		{
			v.c = D3DCOLOR_XRGB(255, 255, 255);
		}
		else
		{
			v.c = D3DCOLOR_XRGB(128, 128, 128);
		}
		v.p = D3DXVECTOR3(fMin, 0,  i * fInterval); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(fMax, 0,  i * fInterval); m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(fMin, 0, -i * fInterval); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(fMax, 0, -i * fInterval); m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3( i * fInterval, 0, fMin); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3( i * fInterval, 0, fMax); m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(-i * fInterval, 0, fMin); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(-i * fInterval, 0, fMax); m_vecVertex.push_back(v);
	}

	v.c = D3DCOLOR_XRGB(255, 0, 0);
	v.p = D3DXVECTOR3(fMin, 0, 0); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(fMax, 0, 0); m_vecVertex.push_back(v);

	v.c = D3DCOLOR_XRGB(0, 255, 0);
	v.p = D3DXVECTOR3(0, fMin, 0); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0, fMax, 0); m_vecVertex.push_back(v);

	v.c = D3DCOLOR_XRGB(0, 0, 255);
	v.p = D3DXVECTOR3(0, 0, fMin); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0, 0, fMax); m_vecVertex.push_back(v);
}

void cGrid::Render()
{
	// Á¶¸íÀ» ²ö´Ù.
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST,
		m_vecVertex.size() / 2, 
		&m_vecVertex[0],
		sizeof(ST_PC_VERTEX));

	for each(cPyramid* p in m_vecPyramid)
	{
		p->Render();
	}
}
