#pragma once

class cGrid;
class cCamera;
class cFrame;
//class cGroup;

class cMainGame
{
private:
	cCamera*			m_pCamera;
	cGrid*				m_pGrid;
	//cGroup*				m_pGroupHead;
	cFrame*				m_pRoot;
	LPD3DXFONT			m_pFont;

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

