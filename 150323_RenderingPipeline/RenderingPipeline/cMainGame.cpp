#include "StdAfx.h"
#include "cMainGame.h"
#include "cVector4.h"

cMainGame::cMainGame(void)
	: m_MemDC(NULL)
	, m_hOldBitmap(NULL)
	, m_hBitmap(NULL)
	, m_vEye(0, 0, -5)
	, m_vDirection(0, 0, 1)
	, m_vLookAt(0, 0, 0)
	, m_vUp(0, 1, 0)
	, m_vCubePosition(0, 0 ,0)
	, m_fAngle(0.0f)
	, m_fDistance(5.0f)
	, m_fCamRotX(0.0f)
	, m_fCamRotY(0.0f)
	, m_isLButtonDown(false)
{
}


cMainGame::~cMainGame(void)
{
	SelectObject(m_MemDC, m_hOldBitmap);
	DeleteObject(m_hBitmap);
	DeleteDC(m_MemDC);
}

void cMainGame::Setup()
{
	HDC hdc = GetDC(g_hWnd);

	m_MemDC = CreateCompatibleDC(hdc);

	RECT rc;
	GetClientRect(g_hWnd, &rc);

	m_hBitmap = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);

	// SelectObject : 리턴값으로 이전의 객체를 반환
	m_hOldBitmap = (HBITMAP)SelectObject(m_MemDC, m_hBitmap);

	ReleaseDC(g_hWnd, hdc);


	m_vecVertex.push_back(cVector4(-1, -1, -1, 1));
	m_vecVertex.push_back(cVector4(-1,  1, -1, 1));
	m_vecVertex.push_back(cVector4( 1,  1, -1, 1));
	m_vecVertex.push_back(cVector4( 1, -1, -1, 1));
	m_vecVertex.push_back(cVector4(-1, -1,  1, 1));
	m_vecVertex.push_back(cVector4(-1,  1,  1, 1));
	m_vecVertex.push_back(cVector4( 1,  1,  1, 1));
	m_vecVertex.push_back(cVector4( 1, -1,  1, 1));

	m_vecIndex.push_back(0); m_vecIndex.push_back(1); m_vecIndex.push_back(2); 
	m_vecIndex.push_back(0); m_vecIndex.push_back(2); m_vecIndex.push_back(3);
	m_vecIndex.push_back(4); m_vecIndex.push_back(6); m_vecIndex.push_back(5);
	m_vecIndex.push_back(4); m_vecIndex.push_back(7); m_vecIndex.push_back(6);
	m_vecIndex.push_back(4); m_vecIndex.push_back(5); m_vecIndex.push_back(1);
	m_vecIndex.push_back(4); m_vecIndex.push_back(1); m_vecIndex.push_back(0);
	m_vecIndex.push_back(3); m_vecIndex.push_back(2); m_vecIndex.push_back(6);
	m_vecIndex.push_back(3); m_vecIndex.push_back(6); m_vecIndex.push_back(7);
	m_vecIndex.push_back(1); m_vecIndex.push_back(5); m_vecIndex.push_back(6);
	m_vecIndex.push_back(1); m_vecIndex.push_back(6); m_vecIndex.push_back(2);
	m_vecIndex.push_back(4); m_vecIndex.push_back(0); m_vecIndex.push_back(3);
	m_vecIndex.push_back(4); m_vecIndex.push_back(3); m_vecIndex.push_back(7);


	int nNumHalfLine = 5;
	float fInterval = 1.0f;
	float fMax = nNumHalfLine * fInterval;
	float fMin = -fMax;
	for (int i = 1; i <= nNumHalfLine; ++i)
	{
		m_vecLineVertex.push_back(cVector4(fMin, 0, i * fInterval, 1));
		m_vecLineVertex.push_back(cVector4(fMax, 0, i * fInterval, 1));

		m_vecLineVertex.push_back(cVector4(fMin, 0, -i * fInterval, 1));
		m_vecLineVertex.push_back(cVector4(fMax, 0, -i * fInterval, 1));

		m_vecLineVertex.push_back(cVector4(i * fInterval, 0, fMin, 1));
		m_vecLineVertex.push_back(cVector4(i * fInterval, 0, fMax, 1));

		m_vecLineVertex.push_back(cVector4(-i * fInterval, 0, fMin, 1));
		m_vecLineVertex.push_back(cVector4(-i * fInterval, 0, fMax, 1));
	}

	m_vecLineVertex.push_back(cVector4(fMin, 0, 0, 1));
	m_vecLineVertex.push_back(cVector4(fMax, 0, 0, 1));

	m_vecLineVertex.push_back(cVector4(0, 0, fMin, 1));
	m_vecLineVertex.push_back(cVector4(0, 0, fMax, 1));

	m_matWorld = cMatrix::Translation(m_vCubePosition);
	m_matView = cMatrix::View(m_vEye, m_vLookAt, m_vUp);
	m_matProjection = cMatrix::Projection(PI / 4.0f, rc.right / (float)rc.bottom, 1.0f, 100.0f);
	m_matViewport = cMatrix::Viewport(0.0f, 0.0f, (float)rc.right, (float)rc.bottom, 0.0f, 1.0f);
}

void cMainGame::Update()
{
	cVector4 vDir = cVector4(0, 0, 1, 0);

	cMatrix matRot = cMatrix::RotationY(m_fAngle);
	vDir = vDir * matRot;
	m_vDirection = vDir.ToVector3();

	if (GetKeyState('W') & 0x8000)
	{
		m_vCubePosition = m_vCubePosition + (m_vDirection * 0.05f);
	}

	if (GetKeyState('S') & 0x8000)
	{
		m_vCubePosition = m_vCubePosition - (m_vDirection * 0.05f);
	}

	if (GetKeyState('A') & 0x8000)
	{
		m_fAngle -= 0.05f;
	}

	if (GetKeyState('D') & 0x8000)
	{
		m_fAngle += 0.05f;
	}

	m_vLookAt = m_vCubePosition;
	
	cVector4 vEye = cVector4(0, 0, -m_fDistance, 1);

	cMatrix matRotX = cMatrix::RotationX(m_fCamRotX);
	cMatrix matRotY = cMatrix::RotationY(m_fCamRotY);
	cMatrix matCamRot = matRotX * matRotY;
	vEye = vEye * matCamRot;
	m_vEye = vEye.ToVector3();
	m_vEye = m_vEye + m_vCubePosition;
	//m_vEye.x = m_vLookAt.x;
	//m_vEye.y = m_vLookAt.y + 5;
	//m_vEye.z = m_vLookAt.z - 5;

	m_matWorld = matRot * cMatrix::Translation(m_vCubePosition);
	m_matView = cMatrix::View(m_vEye, m_vLookAt, m_vUp);
}

void cMainGame::Render( HDC hdc )
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	// 도화지를 흰색으로
	PatBlt(m_MemDC, rc.left, rc.top, rc.right, rc.bottom, WHITENESS);

	cMatrix matWorldViewProj = m_matWorld * m_matView * m_matProjection;

	// 그리기..
	for (size_t i = 0; i < m_vecIndex.size(); i += 3)
	{
		cVector4 v0 = m_vecVertex[m_vecIndex[i]];
		cVector4 v1 = m_vecVertex[m_vecIndex[i + 1]];
		cVector4 v2 = m_vecVertex[m_vecIndex[i + 2]];

		v0 = v0 * matWorldViewProj;
		v1 = v1 * matWorldViewProj;
		v2 = v2 * matWorldViewProj;

		cVector3 v01 = (v1 - v0).ToVector3();
		cVector3 v02 = (v2 - v0).ToVector3();
		cVector3 vNormal = cVector3::Cross(v01, v02);
		cVector3 vZ(0, 0, 1);
		
		if(cVector3::Dot(vZ, vNormal) > 0)
			continue;

		v0 = v0 * m_matViewport;
		v1 = v1 * m_matViewport;
		v2 = v2 * m_matViewport;

		MoveToEx(m_MemDC, (int)v0.x, (int)v0.y, NULL);
		LineTo(m_MemDC, (int)v1.x, (int)v1.y);
		LineTo(m_MemDC, (int)v2.x, (int)v2.y);
		LineTo(m_MemDC, (int)v0.x, (int)v0.y);
	}

	cMatrix mat = m_matView * m_matProjection * m_matViewport;
	for (size_t i = 0; i < m_vecLineVertex.size(); i += 2)
	{
		cVector4 v0 = m_vecLineVertex[i];
		cVector4 v1 = m_vecLineVertex[i + 1];

		v0 = v0 * mat;
		v1 = v1 * mat;

		MoveToEx(m_MemDC, (int)v0.x, (int)v0.y, NULL);
		LineTo(m_MemDC, (int)v1.x, (int)v1.y);
	}

	// 도화지에 그려진 내용을 화면에 표시
	BitBlt(hdc, 0, 0, rc.right, rc.bottom, m_MemDC, 0, 0, SRCCOPY);
}

void cMainGame::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
		{
			m_ptPrevMouse.x = LOWORD(lParam);
			m_ptPrevMouse.y = HIWORD(lParam);
			m_isLButtonDown = true;
		}
		break;
	case WM_LBUTTONUP:
		{
			m_isLButtonDown = false;
		}
		break;
	case WM_MOUSEMOVE:
		{
			if(!m_isLButtonDown)
				break;

			int nDeltaX = LOWORD(lParam) - m_ptPrevMouse.x;
			int d = HIWORD(lParam);
			int nDeltaY = HIWORD(lParam) - m_ptPrevMouse.y;
			
			m_fCamRotX += nDeltaY / 100.f;
			m_fCamRotY += nDeltaX / 100.f;

			if(m_fCamRotX > PI / 2.0f - 0.001f)
			{
				m_fCamRotX = PI / 2.0f - 0.001f;
			}

			if(m_fCamRotX < -PI / 2.0f + 0.001f)
			{
				m_fCamRotX = -PI / 2.0f + 0.001f;
			}

			m_ptPrevMouse.x = LOWORD(lParam);
			m_ptPrevMouse.y = HIWORD(lParam);
		}
		break;
	case WM_MOUSEWHEEL:
		{
			m_fDistance -= GET_WHEEL_DELTA_WPARAM(wParam) / 10.f;
			if(m_fDistance < 3.0f) 
				m_fDistance = 3.0f;

		}
		break;
	}
}
