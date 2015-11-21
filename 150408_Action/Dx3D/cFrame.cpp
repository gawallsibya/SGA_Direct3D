#include "StdAfx.h"
#include "cFrame.h"
#include "cMtlTex.h"

cFrame::cFrame(void)
	: m_pMtlTex(NULL)
	, m_pVB(NULL)
	, m_nNumTri(0)
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matLocal);
}


cFrame::~cFrame(void)
{	
	SAFE_RELEASE(m_pMtlTex);
	SAFE_RELEASE(m_pVB);
}

void cFrame::Setup()
{

}

void cFrame::Update(D3DXMATRIXA16* pParent)
{
	if(pParent)
	{
		m_matWorld = m_matLocal * (*pParent);
	}
	else
	{
		m_matWorld = m_matLocal;
	}

	for each(auto f in m_vecChild)
	{
		f->Update(&m_matWorld);
	}
}

void cFrame::Render()
{
	if (m_pMtlTex)
	{
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
		g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
		g_pD3DDevice->SetMaterial(&m_pMtlTex->m_stMtl);
		g_pD3DDevice->SetTexture(0, m_pMtlTex->m_pTexture);
		g_pD3DDevice->SetStreamSource(0, m_pVB, 0, sizeof(ST_PNT_VERTEX));
		g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_nNumTri);
	}

	for each(auto f in m_vecChild)
	{
		f->Render();
	}
}

void cFrame::AddChild( cFrame* pFrame )
{
	m_vecChild.push_back(pFrame);
}

void cFrame::Destroy()
{
	for each(auto f in m_vecChild)
	{
		f->Destroy();
	}
	delete this;
}

void cFrame::BuildVB( std::vector<ST_PNT_VERTEX>& vecVertex )
{
	D3DXMATRIXA16 matInvWorld;
	D3DXMatrixInverse(&matInvWorld, NULL, &m_matWorld);

	for (size_t i = 0; i < vecVertex.size(); ++i)
	{
		D3DXVec3TransformCoord(&vecVertex[i].p, &vecVertex[i].p, &matInvWorld);
		D3DXVec3TransformNormal(&vecVertex[i].n, &vecVertex[i].n, &matInvWorld);
	}

	g_pD3DDevice->CreateVertexBuffer(
		vecVertex.size() * sizeof(ST_PNT_VERTEX),
		0,
		ST_PNT_VERTEX::FVF,
		D3DPOOL_MANAGED,
		&m_pVB,
		0);

	ST_PNT_VERTEX* pV = NULL;
	m_pVB->Lock(0, 0, (LPVOID*)&pV, 0);
	memcpy(pV, &vecVertex[0], vecVertex.size() * sizeof(ST_PNT_VERTEX));
	m_pVB->Unlock();

	m_nNumTri = vecVertex.size() / 3;
}

void cFrame::SetOriginLocalTM( D3DXMATRIXA16* pParent )
{
	if(pParent)
	{
		D3DXMATRIXA16 matInvPW;
		D3DXMatrixInverse(&matInvPW, NULL, pParent);
		m_matLocal = m_matWorld * matInvPW;
	}
	else
	{
		m_matLocal = m_matWorld;
	}

	for each(auto f in m_vecChild)
	{
		f->SetOriginLocalTM(&m_matWorld);
	}
}
