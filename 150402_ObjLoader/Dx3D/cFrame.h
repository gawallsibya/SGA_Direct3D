#pragma once
class cFrame
{
protected:
	D3DXMATRIXA16				m_matWorld;
	D3DXMATRIXA16				m_matLocal;
	std::vector<ST_PNT_VERTEX>	m_vecVertex;
	LPDIRECT3DTEXTURE9			m_pTexture;
	std::vector<cFrame*>		m_vecChild;
	float						m_fRotX;
	float						m_fRotXSpeed;
	D3DMATERIAL9				m_stMtl;

public:
	cFrame(void);
	virtual ~cFrame(void);

	virtual void Setup();
	virtual void Update(D3DXMATRIXA16* pParent);
	virtual void Render();
	virtual void SetTexture(LPDIRECT3DTEXTURE9 pTexture);
	virtual void AddChild(cFrame* pFrame);
	virtual void Destroy();
};

