#pragma once

#include "cAction.h"

class cActionRepeat 
	: public cAction
	, public iActionDelegate
{
private:
	SYNTHESIZE_ADD_REF(cAction*, m_pAction, Action);

public:
	cActionRepeat(void);
	~cActionRepeat(void);

	virtual void Start() override;
	virtual void Update() override;

	// iActionDelegate
	virtual void OnActionFinish(cAction* pSender) override;
};

