#include "StdAfx.h"
#include "cMainGame.h"
#include "cVector4.h"

cMainGame::cMainGame(void)
	: m_MemDC(NULL)
	, m_hOldBitmap(NULL)
	, m_hBitmap(NULL)
	, m_vEye(0, 5, -5)
	, m_vLookAt(0, 0, 0)
	, m_vUp(0, 1, 0)
	, m_vCubePosition(0, 0 ,0)
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

	m_matWorld = cMatrix::Translation(m_vCubePosition);
	m_matView = cMatrix::View(m_vEye, m_vLookAt, m_vUp);
	m_matProjection = cMatrix::Projection(PI / 4.0f, rc.right / (float)rc.bottom, 1.0f, 100.0f);
	m_matViewport = cMatrix::Viewport(0.0f, 0.0f, (float)rc.right, (float)rc.bottom, 0.0f, 1.0f);
}

void cMainGame::Update()
{
	if (GetKeyState('A') & 0x8000)
	{
		m_vEye.x -= 0.1f;
	}

	if (GetKeyState('D') & 0x8000)
	{
		m_vEye.x += 0.1f;
	}

	if (GetKeyState(VK_UP) & 0x8000)
	{
		m_vCubePosition.z += 0.1f;
	}

	if (GetKeyState(VK_DOWN) & 0x8000)
	{
		m_vCubePosition.z -= 0.1f;
	}

	m_matWorld = cMatrix::Translation(m_vCubePosition);
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

	// 도화지에 그려진 내용을 화면에 표시
	BitBlt(hdc, 0, 0, rc.right, rc.bottom, m_MemDC, 0, 0, SRCCOPY);
}
