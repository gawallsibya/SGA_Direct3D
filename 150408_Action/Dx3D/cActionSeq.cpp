#include "StdAfx.h"
#include "cActionSeq.h"


cActionSeq::cActionSeq(void)
{
}


cActionSeq::~cActionSeq(void)
{
	for each(auto p in m_vecAction)
	{
		SAFE_RELEASE(p);
	}
}

void cActionSeq::Start()
{
	m_itCurrAction = m_vecAction.begin();
	(*m_itCurrAction)->Start();
}

void cActionSeq::Update()
{
	if(*m_itCurrAction)
		(*m_itCurrAction)->Update();
}

void cActionSeq::OnActionFinish( cAction* pSender )
{
	++m_itCurrAction;
	
	if(m_itCurrAction == m_vecAction.end())
	{
		if(m_pDelegate)
			m_pDelegate->OnActionFinish(this);
	}
	else
	{
		(*m_itCurrAction)->Start();
	}
}

void cActionSeq::AddAction( cAction* pAction )
{
	SAFE_ADD_REF(pAction);
	m_vecAction.push_back(pAction);
}
