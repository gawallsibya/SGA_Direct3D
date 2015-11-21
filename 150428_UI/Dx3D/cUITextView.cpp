#include "StdAfx.h"
#include "cUITextView.h"


cUITextView::cUITextView(void)
	: m_eFontType(cFontManager::E_DEFAULT_FONT)
	, m_dwDT(DT_LEFT | DT_TOP)
	, m_dwColor(D3DCOLOR_XRGB(255, 255, 255))
{
}


cUITextView::~cUITextView(void)
{
}

void cUITextView::Render( LPD3DXSPRITE pSprite )
{
	RECT rc;
	SetRect(&rc, 
		m_vWorldPos.x,
		m_vWorldPos.y,
		m_vWorldPos.x + m_stSize.fWidth,
		m_vWorldPos.y + m_stSize.fHeight);
	
	LPD3DXFONT pFont = g_pFontManager->GetFont(m_eFontType);
	
	pFont->DrawTextA(NULL,
		m_sText.c_str(),
		m_sText.length(),
		&rc,
		m_dwDT,//DT_LEFT | DT_TOP | DT_WORDBREAK,
		m_dwColor);
}
