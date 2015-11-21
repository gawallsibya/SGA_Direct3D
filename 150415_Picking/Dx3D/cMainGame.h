#pragma once

class cGrid;
class cCamera;
//class cFrame;
//class cMtlTex;
//class cGroup;

class cMainGame
{
private:
	cCamera*				m_pCamera;
	cGrid*					m_pGrid;
	//cGroup*					m_pGroupHead;
	//cFrame*					m_pRoot;
	LPD3DXFONT				m_pFont;
	//LPD3DXMESH				m_pMesh;
	//std::vector<cMtlTex*>	m_vecMtlTex;
	LPD3DXMESH				m_pTeapot;
	LPD3DXMESH				m_pSphere;
	D3DMATERIAL9			m_stWhiteMtl;
	D3DMATERIAL9			m_stRedMtl;
	D3DXVECTOR3				m_vTeapotPos;
	float					m_fTeapotRadius;
	bool					m_isPicked;

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

