#pragma once
class cCamera
{
private:
	D3DXVECTOR3		m_vEye;
	D3DXVECTOR3		m_vLookAt;
	D3DXVECTOR3		m_vUp;
	bool			m_isLButtonDown;
	float			m_fCamRotX;
	float			m_fCamRotY;
	float			m_fDistance;
	POINT			m_ptPrevMouse;
	D3DXVECTOR3*	m_pvTarget;

public:
	cCamera(void);
	~cCamera(void);

	void Setup(D3DXVECTOR3*	pvTarget = NULL);
	void Update();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};

