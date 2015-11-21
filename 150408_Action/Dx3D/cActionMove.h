#pragma once

#include "cAction.h"

class cActionMove : public cAction
{
private:
	SYNTHESIZE(D3DXVECTOR3, m_vFrom, From);
	SYNTHESIZE(D3DXVECTOR3, m_vTo, To);
	SYNTHESIZE(float, m_fActionTime, ActionTime);
	SYNTHESIZE(float, m_fPassedTime, PassedTime);

public:
	cActionMove(void);
	~cActionMove(void);

	virtual void Start() override;
	virtual void Update() override;
};

