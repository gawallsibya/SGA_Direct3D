#pragma once

class cGrid;
class cCamera;
class cSkinnedMesh;

class cMainGame
{
private:
	cGrid*						m_pGrid;
	cCamera*					m_pCamera;
	
	std::vector<cSkinnedMesh*>	m_vecSkinnedMesh;

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

