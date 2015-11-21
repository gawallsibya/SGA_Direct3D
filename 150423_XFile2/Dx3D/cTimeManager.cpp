#include "StdAfx.h"
#include "cTimeManager.h"


cTimeManager::cTimeManager(void)
	: m_dwFPS(0)
	, m_dwPassedTime(0)
	, m_dwFrameCount(0)
{
	m_dwLastUpdateTime = GetTickCount();
}


cTimeManager::~cTimeManager(void)
{
}

void cTimeManager::Update()
{
	DWORD dwCurrTime = GetTickCount();
	m_dwDeltaTime = dwCurrTime - m_dwLastUpdateTime;
	m_dwLastUpdateTime = dwCurrTime;

	m_dwFrameCount++;
	m_dwPassedTime += m_dwDeltaTime;

	if(m_dwPassedTime >= 1000)
	{
		m_dwPassedTime -= 1000;
		m_dwFPS = m_dwFrameCount;
		m_dwFrameCount = 0;
	}
}

float cTimeManager::GetElapsedTime()
{
	return m_dwDeltaTime / 1000.f;
}

DWORD cTimeManager::GetFPS()
{
	return m_dwFPS;
}
