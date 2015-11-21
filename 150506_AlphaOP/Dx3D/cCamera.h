#pragma once
class cCamera
{
private:
	D3DXVECTOR3		m_vEye;
	D3DXVECTOR3		m_vLookAt;
	D3DXVECTOR3		m_vUp;
	D3DXVECTOR3*	m_pvTarget;
	float			m_fDistance;
	float			m_fAngleX;
	float			m_fAngleY;
	POINT			m_ptPrev;
	bool			m_isLButtonDown;
public:
	cCamera(void);
	~cCamera(void);

	void Setup();
	void Update();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void SetTarget(D3DXVECTOR3* pvTarget);
};

