#pragma once
#include "cVector3.h"
#include "cVector4.h"
#include "cMatrix.h"

class cMainGame
{
private:
	HDC			m_MemDC; 
	HBITMAP		m_hOldBitmap, m_hBitmap;

	cVector3	m_vEye;
	cVector3	m_vLookAt;
	cVector3	m_vUp;
	cVector3	m_vCubePosition;
	cMatrix		m_matWorld;
	cMatrix		m_matView;
	cMatrix		m_matProjection;
	cMatrix		m_matViewport;

	std::vector<cVector4>	m_vecVertex;
	std::vector<DWORD>		m_vecIndex;
	
public:
	cMainGame(void);
	~cMainGame(void);

	void Setup();
	void Update();
	void Render(HDC hdc);
};

