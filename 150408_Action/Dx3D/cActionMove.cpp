#include "StdAfx.h"
#include "cActionMove.h"


cActionMove::cActionMove(void)
	: m_vFrom(0, 0, 0)
	, m_vTo(0, 0, 0)
	, m_fActionTime(0.0f)
	, m_fPassedTime(0.0f)
{
}

cActionMove::~cActionMove(void)
{
}

void cActionMove::Start()
{
	m_fPassedTime = 0.0f;
}

void cActionMove::Update()
{
	m_fPassedTime += g_pTimeManager->GetElapsedTime();
	if(m_fPassedTime >= m_fActionTime)
	{
		if(m_pOwner)
			m_pOwner->SetPosition(m_vTo);

		if(m_pDelegate)
			m_pDelegate->OnActionFinish(this);
	}
	else
	{
		float t = m_fPassedTime / m_fActionTime;
		D3DXVECTOR3 v;
		D3DXVec3Lerp(&v, &m_vFrom, &m_vTo, t);

		if(m_pOwner)
			m_pOwner->SetPosition(v);
	}
}
