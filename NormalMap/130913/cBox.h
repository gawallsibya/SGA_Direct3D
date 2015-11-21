#pragma once

class iCamera;

class cBox
{
	LPD3DXEFFECT			m_pShader;
	LPDIRECT3DTEXTURE9		m_pStoneDM;
	LPDIRECT3DTEXTURE9		m_pStoneSM;
	LPDIRECT3DTEXTURE9		m_pStoneNM;
	D3DXVECTOR4				m_vWorldLightPosition;
	D3DXVECTOR4				m_vLightColor;

	LPD3DXMESH				m_pBox;

public:
	cBox(void);
	~cBox(void);

	
	void Setup();
	void Render(iCamera* pCamera);
};
