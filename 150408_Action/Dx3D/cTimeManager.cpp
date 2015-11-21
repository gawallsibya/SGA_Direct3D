#include "StdAfx.h"
#include "cTimeManager.h"


cTimeManager::cTimeManager(void)
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
}

float cTimeManager::GetElapsedTime()
{
	return m_dwDeltaTime / 1000.f;
}
