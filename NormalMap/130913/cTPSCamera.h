#pragma once
#include "icamera.h"

class cTPSCamera : public iCamera
{
	bool			m_isLButtonDown;
	POINT			m_ptPrevMouse;
	
	float			m_fDist;

	float			m_fRotX;
	float			m_fRotY;

	D3DXVECTOR3		m_vEye;
	D3DXVECTOR3		m_vLookAt;
	D3DXVECTOR3		m_vUp;
	D3DXVECTOR3*	m_pvTarget;

public:
	cTPSCamera(void);
	virtual ~cTPSCamera(void);

	virtual void Setup() override;
	virtual void Update() override;
	virtual void SetTarget(D3DXVECTOR3* vTarget) override;
	virtual D3DXVECTOR3& GetEye() override {return m_vEye;}
	virtual bool MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};
