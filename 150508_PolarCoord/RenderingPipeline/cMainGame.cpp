#include "StdAfx.h"
#include "cMainGame.h"
#include "cVector4.h"

cMainGame::cMainGame(void)
	: m_MemDC(NULL)
	, m_hOldBitmap(NULL)
	, m_hBitmap(NULL)
	, m_fRadius(0.0f)
	, m_fTheta(0.0f)
	, m_fDeltaRadius(1.0f)
	, m_fDeltaTheta(0.1f)
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
}

void cMainGame::Update()
{
	m_fRadius += m_fDeltaRadius;
	m_fTheta += m_fDeltaTheta;

	if(m_fRadius > 300.f)
	{
		m_fDeltaRadius *= -1;
	}

	if(m_fRadius < 0.f)
	{
		m_fDeltaRadius *= -1;
	}
}

void cMainGame::Render( HDC hdc )
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	// 도화지를 흰색으로
	PatBlt(m_MemDC, rc.left, rc.top, rc.right, rc.bottom, WHITENESS);

	MoveToEx(m_MemDC, 0, 500, NULL);
	LineTo(m_MemDC, rc.right, 500);

	static ST_VECTOR2 vPosition;

	vPosition.x = m_fRadius * cosf(m_fTheta) + 300;
	vPosition.y = m_fRadius * sinf(m_fTheta) + 300;

	Ellipse(m_MemDC, 
		vPosition.x - 10,
		vPosition.y - 10,
		vPosition.x + 10,
		vPosition.y + 10);

	// 도화지에 그려진 내용을 화면에 표시
	BitBlt(hdc, 0, 0, rc.right, rc.bottom, m_MemDC, 0, 0, SRCCOPY);
}
