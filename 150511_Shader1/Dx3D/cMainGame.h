#pragma once

class cGrid;
class cCamera;
class cSkinnedMesh;
class cCube;

class cMainGame
{
private:
	cGrid*						m_pGrid;
	cCamera*					m_pCamera;
	cSkinnedMesh*				m_pSkinnedMesh;
	LPD3DXMESH					m_pStringMesh;
	cCube*						m_pCube;
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

