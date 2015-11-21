#include "StdAfx.h"
#include "cMainGame.h"
#include "cVector4.h"

cMainGame::cMainGame(void)
	: m_MemDC(NULL)
	, m_hOldBitmap(NULL)
	, m_hBitmap(NULL)
	, m_stStart(0.0f, 0.0f)
	, m_stDest(0.0f, 0.0f)
	, m_stVel(0.0f, 0.0f)
	, m_fGravity(0.0f)
	, m_fPassedTime(0.0f)
	, m_fMoveTime(0.0)
	, m_dwPrev(0)
	, m_stPosition(0.0f, 0.0f)
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


	
	//v = at;
	//s = vt;
	//s = a * t * t / 2
}

void cMainGame::Update()
{
	if (GetKeyState(VK_LBUTTON) & 0x8000)
	{
		POINT ptMouse;
		GetCursorPos(&ptMouse);
		ScreenToClient(g_hWnd, &ptMouse);

		m_dwPrev = GetTickCount();
		m_fMoveTime = 1.0f;
		m_fPassedTime = 0.0f;
		m_fGravity = 30.0f;

		m_stStart.x = 100.f;
		m_stStart.y = 500.f;
		
		m_stDest.x = ptMouse.x;
		m_stDest.y = 500.f;

		m_stPosition.x = 100.f;
		m_stPosition.y = 500.f;

		m_stVel.x = (m_stDest.x - m_stStart.x) / m_fMoveTime;
		m_stVel.y = -(m_fGravity * m_fMoveTime * m_fMoveTime) / 2.0f;
	}
	else
	{
		DWORD dwCurr = GetTickCount();
		
		float fElapsedTime = (dwCurr - m_dwPrev) / 1000.0f;
		
		m_fPassedTime += fElapsedTime;

		m_stVel.y += m_fGravity * fElapsedTime;
		
		m_stPosition.x = m_stPosition.x + m_stVel.x * fElapsedTime;
		m_stPosition.y = m_stPosition.y + m_stVel.y;

		m_dwPrev = dwCurr;
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

	Ellipse(m_MemDC, 
		m_stPosition.x - 10,
		m_stPosition.y - 10,
		m_stPosition.x + 10,
		m_stPosition.y + 10);

	// 도화지에 그려진 내용을 화면에 표시
	BitBlt(hdc, 0, 0, rc.right, rc.bottom, m_MemDC, 0, 0, SRCCOPY);
}
