#pragma once
#include "cGameObject.h"

class cCharacter : public cGameObject
{
protected:
	D3DXVECTOR3		m_vDirection;
	float			m_fAngle;
	D3DXMATRIXA16	m_matWorld;

public:
	cCharacter(void);
	virtual ~cCharacter(void);

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual void GetWorldMatrix(D3DXMATRIXA16* pmatWorld);
};

