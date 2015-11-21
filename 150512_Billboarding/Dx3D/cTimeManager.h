#pragma once

#define g_pTimeManager cTimeManager::GetInstance()

class cTimeManager
{
private:
	SINGLETONE(cTimeManager);

private:
	DWORD m_dwLastUpdateTime;
	DWORD m_dwDeltaTime;
	DWORD m_dwFPS;
	DWORD m_dwFrameCount;
	DWORD m_dwAccTime;

public:
	
	void Update();
	float GetDeltaTime();
	DWORD GetFPS()
	{
		return m_dwFPS;
	}
};

