#pragma once

#include "cAction.h"

class cActionSeq 
	: public cAction
	, public iActionDelegate
{
protected:
	std::vector<cAction*>			m_vecAction;
	std::vector<cAction*>::iterator	m_itCurrAction;

public:
	cActionSeq(void);
	~cActionSeq(void);

	virtual void Start() override;
	virtual void Update() override;
	virtual void AddAction(cAction* pAction);

	// iActionDelegate override
	virtual void OnActionFinish(cAction* pSender) override;
};

