#pragma once
class cMainGame
{
private:
	int  m_nX;
	static void ThFunc1(LPVOID pParam);
	static void ThFunc2(LPVOID pParam);
	
	volatile bool m_isLoaded;

public:
	cMainGame(void);
	~cMainGame(void);

	void Setup();
};

