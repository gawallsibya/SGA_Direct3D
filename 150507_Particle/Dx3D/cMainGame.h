#pragma once

class cGrid;
class cCamera;
class cCharacter;
class cHeightMap;

class cMainGame
{
private:
	cGrid*		m_pGrid;
	cCamera*	m_pCamera;
	cCharacter*	m_pCharacter;
	cHeightMap* m_pMap;

	std::vector<ST_PC_VERTEX>	m_vecVertex;

public:
	cMainGame(void);
	~cMainGame(void);

	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	void SetLight();
};

