#pragma once
#include "cVector3.h"
#include "cVector4.h"
#include "cMatrix.h"

struct ST_VECTOR2
{
	float x, y;
	ST_VECTOR2() : x(0.0f), y(0.0f) {}
	ST_VECTOR2(float _x, float _y) : x(_x), y(_y) {}
	ST_VECTOR2 operator+(ST_VECTOR2& v)
	{
		ST_VECTOR2 p;
		p.x = x + v.x;
		p.y = y + v.y;
		return p;
	}
};

class cMainGame
{
private:
	HDC			m_MemDC; 
	HBITMAP		m_hOldBitmap, m_hBitmap;

	float		m_fRadius;
	float		m_fTheta;
	float		m_fDeltaRadius;
	float		m_fDeltaTheta;

public:
	cMainGame(void);
	~cMainGame(void);

	void Setup();
	void Update();
	void Render(HDC hdc);
};

