#include "StdAfx.h"
#include "cUIButton.h"


cUIButton::cUIButton(void)
	: m_eButtonState(E_NORMAL)
	, m_pDelegate(NULL)
{
}


cUIButton::~cUIButton(void)
{
}

void cUIButton::Update( D3DXVECTOR3* pvParentWorld )
{
	cUIObject::Update(pvParentWorld);

	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	RECT rc;
	SetRect(&rc, 
		m_vWorldPos.x,
		m_vWorldPos.y,
		m_vWorldPos.x + m_stSize.fWidth,
		m_vWorldPos.y + m_stSize.fHeight);

	if(PtInRect(&rc, pt))
	{
		if(GetKeyState(VK_LBUTTON) & 0x8000)
		{
			if(m_eButtonState == E_NORMAL || m_eButtonState == E_MOUSE_OVER)
			{
				m_eButtonState = E_SELECTED;
			}
		}
		else
		{
			if(m_eButtonState == E_SELECTED)
			{
				if(m_pDelegate)
					m_pDelegate->OnClick(this);
			}

			m_eButtonState = E_MOUSE_OVER;
		}
	}
	else
	{
		if(GetKeyState(VK_LBUTTON) & 0x8000)
		{
			if(m_eButtonState != E_SELECTED)
				m_eButtonState = E_NORMAL;
		}
		else
		{
			m_eButtonState = E_NORMAL;
		}
	}
}

void cUIButton::Render( LPD3DXSPRITE pSprite )
{
	D3DXIMAGE_INFO ii;
	LPDIRECT3DTEXTURE9 pTexture = NULL;

	if (m_eButtonState == E_NORMAL)
	{
		pTexture = g_pTextureManager->GetTexture(m_sNormalImage, &ii);
	}
	else if (m_eButtonState == E_MOUSE_OVER)
	{
		pTexture = g_pTextureManager->GetTexture(m_sMouseOverImage, &ii);
	}
	else if (m_eButtonState == E_SELECTED)
	{
		pTexture = g_pTextureManager->GetTexture(m_sSelectedImage, &ii);
	}

	if(pTexture)
	{
		m_stSize.fWidth = ii.Width;
		m_stSize.fHeight = ii.Height;

		pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

		D3DXMATRIXA16 matWorld;

		D3DXMatrixTranslation(&matWorld, m_vWorldPos.x, m_vWorldPos.y, m_vWorldPos.z);
		pSprite->SetTransform(&matWorld);

		RECT rc;
		SetRect(&rc, 0, 0, ii.Width, ii.Height);
		pSprite->Draw(pTexture,
			&rc, 
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(0, 0, 0),
			D3DCOLOR_XRGB(255, 255, 255));
		pSprite->End();
	}
}
