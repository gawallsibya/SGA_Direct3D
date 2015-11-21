#pragma once
#include "cAction.h"

class cGameObject : public cObject
{
private:
	SYNTHESIZE_PASS_BY_REF(D3DXVECTOR3, m_vPosition, Position);
	SYNTHESIZE_ADD_REF(cAction*, m_pAction, Action);

public:
	cGameObject(void);
	virtual ~cGameObject(void);

	virtual void Update();
};

