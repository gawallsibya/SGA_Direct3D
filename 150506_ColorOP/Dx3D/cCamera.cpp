#include "StdAfx.h"
#include "cCamera.h"


cCamera::cCamera(void)
	: m_vEye(0, 0, -15)
	, m_vLookAt(0, 0, 0)
	, m_vUp(0, 1, 0)
	, m_fDistance(15.0f)
	, m_fAngleX(0.0f)
	, m_fAngleY(0.0f)
	, m_isLButtonDown(false)
	, m_pvTarget(NULL)
{
	m_ptPrev.x = 0;
	m_ptPrev.y = 0;
}


cCamera::~cCamera(void)
{
}

void cCamera::Setup()
{
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vLookAt, &m_vUp);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0f, rc.right / (float)rc.bottom, 1, 10000);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}

void cCamera::Update()
{
	m_vEye		= D3DXVECTOR3(0, 0, -m_fDistance);
	m_vLookAt	= D3DXVECTOR3(0, 0, 0);
	m_vUp		= D3DXVECTOR3(0, 1, 0);

	D3DXMATRIXA16 matRotX, matRotY;
	D3DXMatrixRotationX(&matRotX, m_fAngleX);
	D3DXMatrixRotationY(&matRotY, m_fAngleY);
	D3DXVec3TransformCoord(&m_vEye, &m_vEye, &matRotX);
	D3DXVec3TransformCoord(&m_vEye, &m_vEye, &matRotY);

	if(m_pvTarget)
	{
		m_vEye += (*m_pvTarget);
		m_vLookAt = (*m_pvTarget);
	}

	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vLookAt, &m_vUp);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);
}

void cCamera::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch (message)
	{
	case WM_MOUSEWHEEL:
		m_fDistance -= (GET_WHEEL_DELTA_WPARAM(wParam) / 100.0f);
		break;
	case WM_LBUTTONDOWN:
		{
			int nX = LOWORD(lParam);
			int nY = HIWORD(lParam);
			m_ptPrev.x = nX;
			m_ptPrev.y = nY;
			m_isLButtonDown = true;
		}
		break;
	case WM_LBUTTONUP:
		m_isLButtonDown = false;
		break;
	case WM_MOUSEMOVE:
		{
			if(m_isLButtonDown)
			{
				int nX = LOWORD(lParam);
				int nY = HIWORD(lParam);

				int nDeltaX = nX - m_ptPrev.x;
				int nDeltaY = nY - m_ptPrev.y;

				m_fAngleX += (nDeltaY / 100.0f);
				m_fAngleY += (nDeltaX / 100.0f);

				if(m_fAngleX > D3DX_PI / 2.0f - 0.0001f)
					m_fAngleX = D3DX_PI / 2.0f - 0.0001f;

				if(m_fAngleX < -D3DX_PI / 2.0f + 0.0001f)
					m_fAngleX = -D3DX_PI / 2.0f + 0.0001f;


				m_ptPrev.x = nX;
				m_ptPrev.y = nY;
			}
		}
		break;
	}
}

void cCamera::SetTarget( D3DXVECTOR3* pvTarget )
{
	m_pvTarget = pvTarget;
}
