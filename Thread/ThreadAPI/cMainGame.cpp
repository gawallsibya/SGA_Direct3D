#include "StdAfx.h"
#include "cMainGame.h"


cMainGame::cMainGame(void)
	: m_nX(100)
{
}


cMainGame::~cMainGame(void)
{
}

void cMainGame::Setup()
{
// 	m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
// 		m_hWnd, dwVertexFlag|D3DCREATE_MULTITHREADED,
// 		&m_d3dpp, &m_pDevice );
	DWORD dwThID;
	CloseHandle(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThFunc1, this, NULL/*CREATE_SUSPENDED*/, &dwThID));
	CloseHandle(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThFunc2, this, NULL/*CREATE_SUSPENDED*/, &dwThID));
}

void cMainGame::ThFunc1( LPVOID pParam )
{
	cMainGame* pThis = (cMainGame*)pParam;

	while(1)
	{
		HDC hDC = GetDC(g_hWnd);
		pThis->m_nX = 100;
		Sleep(rand() % 100);
		TextOut(hDC, pThis->m_nX, 100, "강아지", strlen("강아지"));
		ReleaseDC(g_hWnd, hDC);
		InvalidateRect(g_hWnd, NULL, false);
	}
}

void cMainGame::ThFunc2( LPVOID pParam )
{
	cMainGame* pThis = (cMainGame*)pParam;
	while(1)
	{
		HDC hDC = GetDC(g_hWnd);
		pThis->m_nX = 200;
		Sleep(rand() % 100);
		TextOut(hDC, pThis->m_nX, 200, "고양이", strlen("고양이"));
		ReleaseDC(g_hWnd, hDC);
		InvalidateRect(g_hWnd, NULL, false);
	}
}
