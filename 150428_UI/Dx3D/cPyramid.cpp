#include "StdAfx.h"
#include "cPyramid.h"


cPyramid::cPyramid(void)
	: m_pVB(NULL)
{
}


cPyramid::~cPyramid(void)
{
	SAFE_RELEASE(m_pVB);
}

void cPyramid::Setup(D3DXCOLOR c, D3DXMATRIXA16* pmat)
{
	m_matWorld = (*pmat);

	ZeroMemory(&m_stMtl, sizeof(m_stMtl));
	m_stMtl.Ambient = c;
	m_stMtl.Diffuse = c;
	m_stMtl.Specular = c;
	m_stMtl.Power = 15.0f;

	std::vector<ST_PN_VERTEX>	vecVertex;

	ST_PN_VERTEX v;
	D3DXVECTOR3 v0, v1, v2, v01, v02, n;

	v.p = D3DXVECTOR3( 0,  0,  0); vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1, -1, -1); vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1, -1); vecVertex.push_back(v);

	v.p = D3DXVECTOR3( 0,  0,  0); vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1, -1,  1); vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1, -1, -1); vecVertex.push_back(v);
	
	v.p = D3DXVECTOR3( 0,  0,  0); vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1,  1); vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1, -1,  1); vecVertex.push_back(v);

	v.p = D3DXVECTOR3( 0,  0,  0); vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1, -1); vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1,  1); vecVertex.push_back(v);


	v.p = D3DXVECTOR3(-1, -1, -1); vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1, -1, -1); vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1, -1,  1); vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1, -1, -1); vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1, -1,  1); vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1,  1); vecVertex.push_back(v);

	for (size_t i = 0; i < vecVertex.size(); i += 3)
	{
		CalcNormal(vecVertex[i], vecVertex[i + 1], vecVertex[i + 2]);
	}

	g_pD3DDevice->CreateVertexBuffer(
		vecVertex.size() * sizeof(ST_PN_VERTEX),
		0,
		ST_PN_VERTEX::FVF,
		D3DPOOL_MANAGED,
		&m_pVB,
		0);

	ST_PN_VERTEX* pV = NULL;
	m_pVB->Lock(0, 0, (LPVOID*)&pV, 0);
	memcpy(pV, &vecVertex[0], vecVertex.size() * sizeof(ST_PN_VERTEX));
	m_pVB->Unlock();
}

void cPyramid::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetFVF(ST_PN_VERTEX::FVF);
	g_pD3DDevice->SetMaterial(&m_stMtl);
	g_pD3DDevice->SetStreamSource(0, m_pVB, 0, sizeof(ST_PN_VERTEX));
	g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 6);
}

void cPyramid::CalcNormal( ST_PN_VERTEX& v0, ST_PN_VERTEX& v1, ST_PN_VERTEX& v2 )
{
	D3DXVECTOR3 n;
	D3DXVECTOR3 v01 = v1.p - v0.p;
	D3DXVECTOR3 v02 = v2.p - v0.p;
	D3DXVec3Cross(&n, &v01, &v02);
	D3DXVec3Normalize(&n, &n);
	v0.n = n;
	v1.n = n;
	v2.n = n;
}
