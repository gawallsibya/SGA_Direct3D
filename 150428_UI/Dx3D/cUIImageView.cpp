#include "StdAfx.h"
#include "cUIImageView.h"


cUIImageView::cUIImageView(void)
{
}


cUIImageView::~cUIImageView(void)
{
}

void cUIImageView::Update( D3DXVECTOR3* pvParentWorld )
{
	cUIObject::Update(pvParentWorld);
}

void cUIImageView::Render(LPD3DXSPRITE pSprite)
{
	D3DXIMAGE_INFO ii;
	LPDIRECT3DTEXTURE9 pTexture = g_pTextureManager->GetTexture(m_sImageName, &ii);

	m_stSize.fWidth = ii.Width;
	m_stSize.fHeight = ii.Height;

	if(pTexture)
	{
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

	cUIObject::Render(pSprite);
}
