#include "StdAfx.h"
#include "cGroup.h"
#include "cMtlTex.h"


cGroup::cGroup(void)
	: m_pVB(NULL)
	, m_pNext(NULL)
	, m_nNumTri(NULL)
	, m_pMtlTex(NULL)
{
}


cGroup::~cGroup(void)
{
	SAFE_RELEASE(m_pMtlTex);
	SAFE_RELEASE(m_pVB);
}

void cGroup::BuildVertexBuffer( std::vector<ST_PNT_VERTEX>& vecVertex )
{
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

void cGroup::Render()
{
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	if (m_pMtlTex)
	{
		g_pD3DDevice->SetMaterial(&m_pMtlTex->m_stMtl);
		g_pD3DDevice->SetTexture(0, m_pMtlTex->m_pTexture);
	}
	
	g_pD3DDevice->SetStreamSource(0, m_pVB, 0, sizeof(ST_PNT_VERTEX));
	g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_nNumTri);
	if(m_pNext)
		m_pNext->Render();
}

void cGroup::Destroy()
{
	if (m_pNext)
	{
		m_pNext->Destroy();
	}
	delete this;
}
