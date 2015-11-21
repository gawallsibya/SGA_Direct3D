#pragma once

#define g_pTimeManager cTimeManager::GetInstance()

class cTimeManager
{
private:
	DWORD m_dwLastUpdateTime;
	DWORD m_dwDeltaTime;

public:
	SINGLETONE(cTimeManager);

public:
	void Update();
	float GetElapsedTime();
};

