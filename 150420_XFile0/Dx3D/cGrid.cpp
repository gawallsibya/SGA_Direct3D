#include "StdAfx.h"
#include "cGrid.h"
#include "cPyramid.h"

cGrid::cGrid(void)
	: m_pVB(NULL)
	, m_nNumLine(0)
{
}


cGrid::~cGrid(void)
{
	for each(cPyramid* p in m_vecPyramid)
	{
		SAFE_DELETE(p);
	}

	SAFE_RELEASE(m_pVB);
}

void cGrid::Setup(int nNumHalfLine, float fInterval)
{
	D3DXMATRIXA16 matWorld, matR, matS;
	
	D3DXMatrixScaling(&matS, 0.1f, 2.0f, 0.1f);

	cPyramid* pPyramid = NULL;

	pPyramid = new cPyramid;
	D3DXMatrixRotationZ(&matR, D3DX_PI / 2.0f);
	matWorld = matS * matR;
	pPyramid->Setup(D3DXCOLOR(1, 0, 0, 1), &matWorld);
	m_vecPyramid.push_back(pPyramid);

	pPyramid = new cPyramid;
	D3DXMatrixRotationZ(&matR, D3DX_PI);
	matWorld = matS * matR;
	pPyramid->Setup(D3DXCOLOR(0, 1, 0, 1), &matWorld);
	m_vecPyramid.push_back(pPyramid);

	pPyramid = new cPyramid;
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0f);
	matWorld = matS * matR;
	pPyramid->Setup(D3DXCOLOR(0, 0, 1, 1), &matWorld);
	m_vecPyramid.push_back(pPyramid);

	std::vector<ST_PC_VERTEX>	vecVertex;

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
		v.p = D3DXVECTOR3(fMin, 0,  i * fInterval); vecVertex.push_back(v);
		v.p = D3DXVECTOR3(fMax, 0,  i * fInterval); vecVertex.push_back(v);

		v.p = D3DXVECTOR3(fMin, 0, -i * fInterval); vecVertex.push_back(v);
		v.p = D3DXVECTOR3(fMax, 0, -i * fInterval); vecVertex.push_back(v);

		v.p = D3DXVECTOR3( i * fInterval, 0, fMin); vecVertex.push_back(v);
		v.p = D3DXVECTOR3( i * fInterval, 0, fMax); vecVertex.push_back(v);

		v.p = D3DXVECTOR3(-i * fInterval, 0, fMin); vecVertex.push_back(v);
		v.p = D3DXVECTOR3(-i * fInterval, 0, fMax); vecVertex.push_back(v);
	}

	v.c = D3DCOLOR_XRGB(255, 0, 0);
	v.p = D3DXVECTOR3(fMin, 0, 0); vecVertex.push_back(v);
	v.p = D3DXVECTOR3(fMax, 0, 0); vecVertex.push_back(v);

	v.c = D3DCOLOR_XRGB(0, 255, 0);
	v.p = D3DXVECTOR3(0, fMin, 0); vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0, fMax, 0); vecVertex.push_back(v);

	v.c = D3DCOLOR_XRGB(0, 0, 255);
	v.p = D3DXVECTOR3(0, 0, fMin); vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0, 0, fMax); vecVertex.push_back(v);

	m_nNumLine = vecVertex.size() / 2;

	g_pD3DDevice->CreateVertexBuffer(vecVertex.size() * sizeof(ST_PC_VERTEX),
		0,
		ST_PC_VERTEX::FVF,
		D3DPOOL_MANAGED,
		&m_pVB,
		0);

	ST_PC_VERTEX* pV = NULL;
	m_pVB->Lock(0, 0, (LPVOID*)&pV, 0);
	memcpy(pV, &vecVertex[0], vecVertex.size() * sizeof(ST_PC_VERTEX));
	m_pVB->Unlock();
}

void cGrid::Render()
{
	// Á¶¸íÀ» ²ö´Ù.
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetTexture(0, NULL);
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->SetStreamSource(0, m_pVB, 0, sizeof(ST_PC_VERTEX));
	g_pD3DDevice->DrawPrimitive(D3DPT_LINELIST, 0, m_nNumLine);

	// Á¶¸íÀ» ÄÒ´Ù.
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	for each(cPyramid* p in m_vecPyramid)
	{
		p->Render();
	}
}
