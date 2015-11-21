#pragma once

class cUIObject : public cObject
{
protected:
	std::set<cUIObject*>	m_setChild;
	D3DXVECTOR3				m_vLocalPos;
	D3DXVECTOR3				m_vWorldPos;
	bool					m_isVisible;

	SYNTHESIZE(ST_SIZEF, m_stSize, Size);

public:
	cUIObject(void);
	virtual ~cUIObject(void);

	virtual void Update(D3DXVECTOR3* pvParentWorld);
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual void AddChild(cUIObject* pChild);
	virtual void Destroy();
	virtual void SetVisible(bool isVisible);
	virtual void SetPosition(D3DXVECTOR3& vPosition);
	virtual cUIObject* FindByTag(int nTag);
};

