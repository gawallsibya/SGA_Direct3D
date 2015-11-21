#include "StdAfx.h"
#include "cFrame.h"


cFrame::cFrame(void)
	: m_pTexture(NULL)
	, m_fRotX(0.0f)
	, m_fRotXSpeed(0.01f)
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matLocal);
}


cFrame::~cFrame(void)
{	
	SAFE_RELEASE(m_pTexture);
}

void cFrame::Setup()
{

}

void cFrame::Update(D3DXMATRIXA16* pParent)
{

}

void cFrame::Render()
{
	if(m_vecVertex.empty())
		return;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	g_pD3DDevice->SetTexture(0, m_pTexture);
	g_pD3DDevice->SetMaterial(&m_stMtl);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex.size() / 3, 
		&m_vecVertex[0],
		sizeof(ST_PNT_VERTEX));

	for each(auto f in m_vecChild)
	{
		f->Render();
	}
}

void cFrame::SetTexture( LPDIRECT3DTEXTURE9 pTexture )
{
	if(m_pTexture)
		return; 

	if(pTexture)
		pTexture->AddRef();

	m_pTexture = pTexture;
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
