#pragma once

class cCube;
class cGrid;
class cCamera;

class cMainGame
{
private:
	cCamera*			m_pCamera;
	cCube*				m_pCube;
	cGrid*				m_pGrid;
	ST_PT_VERTEX		m_aVertex[3];
	LPDIRECT3DTEXTURE9	m_pTexture;

public:
	cMainGame(void);
	~cMainGame(void);

	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

