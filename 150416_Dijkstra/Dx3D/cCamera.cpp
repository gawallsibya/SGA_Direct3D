#include "StdAfx.h"
#include "cCamera.h"


cCamera::cCamera(void)
	: m_vEye(0, 0, -5)
	, m_vLookAt(0, 0, 0)
	, m_vUp(0, 1, 0)
	, m_fDistance(15.0f)
	, m_fCamRotX(0.0f)
	, m_fCamRotY(0.0f)
	, m_pvTarget(NULL)
{
	m_ptPrevMouse.x = 0;
	m_ptPrevMouse.y = 0;
}


cCamera::~cCamera(void)
{
}

void cCamera::Setup(D3DXVECTOR3* pvTarget)
{
	m_pvTarget = pvTarget;

	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vLookAt, &m_vUp);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);
	
	D3DVIEWPORT9 vp;
	g_pD3DDevice->GetViewport(&vp);

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0f, vp.Width / (float)vp.Height, 1, 10000);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);

}

void cCamera::Update()
{
	if(GetKeyState(VK_LBUTTON) & 0x8000)
	{
		POINT ptMouse;
		GetCursorPos(&ptMouse);
		ScreenToClient(g_hWnd, &ptMouse);

		int nDeltaX = ptMouse.x - m_ptPrevMouse.x;
		int nDeltaY = ptMouse.y - m_ptPrevMouse.y;

		m_fCamRotX += nDeltaY / 100.f;
		m_fCamRotY += nDeltaX / 100.f;

		if(m_fCamRotX > D3DX_PI / 2.0f - 0.001f)
		{
			m_fCamRotX = D3DX_PI / 2.0f - 0.001f;
		}

		if(m_fCamRotX < -D3DX_PI / 2.0f + 0.001f)
		{
			m_fCamRotX = -D3DX_PI / 2.0f + 0.001f;
		}

		m_ptPrevMouse = ptMouse;
	}

	if(m_pvTarget)
		m_vLookAt = *m_pvTarget;

	m_vEye = D3DXVECTOR3(0, 0, -m_fDistance);
	D3DXMATRIXA16 matCamRot, matCamRotX, matCamRotY;
	D3DXMatrixRotationX(&matCamRotX, m_fCamRotX);
	D3DXMatrixRotationY(&matCamRotY, m_fCamRotY);
	
	matCamRot = matCamRotX * matCamRotY;
	D3DXVec3TransformCoord(&m_vEye, &m_vEye, &matCamRot);

	m_vEye = m_vEye + m_vLookAt;
	
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vLookAt, &m_vUp);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);
}

void cCamera::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
		{
			m_ptPrevMouse.x = LOWORD(lParam);
			m_ptPrevMouse.y = HIWORD(lParam);
		}
		break;
	case WM_MOUSEWHEEL:
		{
			m_fDistance -= GET_WHEEL_DELTA_WPARAM(wParam) / 100.f;
			if(m_fDistance < 3.0f) 
				m_fDistance = 3.0f;
		}
		break;
	}
}
