#pragma once

#define g_pTimeManager cTimeManager::GetInstance()

class cTimeManager
{
private:
	DWORD m_dwLastUpdateTime;
	DWORD m_dwDeltaTime;
	DWORD m_dwPassedTime;
	DWORD m_dwFrameCount;
	DWORD m_dwFPS;

public:
	SINGLETONE(cTimeManager);

public:
	void Update();
	float GetElapsedTime();
	DWORD GetFPS();
};

