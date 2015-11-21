#pragma once
class cPyramid
{
private:
	D3DXMATRIXA16				m_matWorld;
	LPDIRECT3DVERTEXBUFFER9		m_pVB;
	D3DMATERIAL9				m_stMtl;
public:
	cPyramid(void);
	~cPyramid(void);
	void Setup(D3DXCOLOR c, D3DXMATRIXA16* pmat);
	void Render();
private:
	void CalcNormal(ST_PN_VERTEX& v0, ST_PN_VERTEX& v1, ST_PN_VERTEX& v2);
};

