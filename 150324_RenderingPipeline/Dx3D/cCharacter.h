#pragma once
class cCharacter
{
protected:
	D3DXVECTOR3		m_vDirection;
	D3DXVECTOR3		m_vPosition;
	float			m_fAngle;
	D3DXMATRIXA16	m_matWorld;
public:
	cCharacter(void);
	virtual ~cCharacter(void);

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual D3DXVECTOR3& GetPosition()
	{
		return m_vPosition;
	}
};

