#include "StdAfx.h"
#include "cTPSCamera.h"
#include "cDeviceMgr.h"

cTPSCamera::cTPSCamera(void)
{
	m_isLButtonDown		= false;
	m_pvTarget			= NULL;
	m_fRotX				= 0.0f;
	m_fRotY				= 0.0f;
	m_fDist				= 20.0f;
}

cTPSCamera::~cTPSCamera(void)
{
}

void cTPSCamera::Setup()
{
	m_vEye = D3DXVECTOR3(0,0,-m_fDist);
	m_vLookAt = D3DXVECTOR3(0,0,0);
	m_vUp = D3DXVECTOR3(0,1,0);

	D3DXMATRIXA16 mProj;
	D3DXMatrixPerspectiveFovLH(&mProj, D3DX_PI / 4.0f, WINSIZE_X / (float)WINSIZE_Y, 1.0f, 1000.0f);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &mProj);
}

void cTPSCamera::Update()
{
	if(m_pvTarget == NULL)
		return;

	m_vEye = D3DXVECTOR3(0,0,-m_fDist);

	D3DXMATRIXA16 mRotX;
	D3DXMatrixRotationX(&mRotX, m_fRotX);
	D3DXVec3TransformCoord(&m_vEye, &m_vEye, &mRotX);

	D3DXMATRIXA16 mRotY;
	D3DXMatrixRotationY(&mRotY, m_fRotY);
	D3DXVec3TransformCoord(&m_vEye, &m_vEye, &mRotY);
	
	m_vEye += *m_pvTarget;

	D3DXMATRIXA16 mView;
	D3DXMatrixLookAtLH(&mView, &m_vEye, m_pvTarget, &m_vUp);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &mView);
}

void cTPSCamera::SetTarget( D3DXVECTOR3* vTarget )
{
	m_pvTarget = vTarget;
}

bool cTPSCamera::MsgProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
		m_ptPrevMouse.x = LOWORD(lParam);
		m_ptPrevMouse.y = HIWORD(lParam);
		m_isLButtonDown = true;
		return true;
	case WM_LBUTTONUP:
		m_isLButtonDown = false;
		return true;
	case WM_MOUSEMOVE:
		{
			if(m_isLButtonDown)
			{
				POINT ptCurMouse;
				ptCurMouse.x = LOWORD(lParam);
				ptCurMouse.y = HIWORD(lParam);
				
				// 이전 마우스 위치로 부터 얼마나 움직였는지 계산.
				float fDeltaRotX = (float)ptCurMouse.y - m_ptPrevMouse.y;
				float fDeltaRotY = (float)ptCurMouse.x - m_ptPrevMouse.x;

				fDeltaRotX /= 100.0f;
				fDeltaRotY /= 100.0f;

				m_fRotX += fDeltaRotX;
				m_fRotY += fDeltaRotY;
				
				// 다음 갱신시 적용할 마지막 마우스 좌표 저장.
				m_ptPrevMouse = ptCurMouse;

				return true;
			}
		}break;
	case WM_MOUSEWHEEL:
		{
			float fDelta = -GET_WHEEL_DELTA_WPARAM(wParam) / 100.f; // 얼마나 회전 했는지..
			m_fDist += fDelta;
			return true;
		}
		break;
	case WM_KEYDOWN:
		{
			switch(wParam)
			{
			case VK_UP:
				// TODO : 어떤 처리	
				return true;
			}
		}
		break;
	}
	return false;
	return false;
}
