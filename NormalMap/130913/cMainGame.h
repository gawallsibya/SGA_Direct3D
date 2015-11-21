#pragma once

class cGrid;
class cBox;
class iCamera;

class cMainGame
{
	cGrid*			m_pGrid;
	cBox*			m_pBox;
	iCamera*		m_pCamera;
	D3DXVECTOR3		m_vLookAt;

public:
	cMainGame(void);
	~cMainGame(void);

	void Setup(HWND hWnd);
	void Update();
	void Render();

	bool MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};
