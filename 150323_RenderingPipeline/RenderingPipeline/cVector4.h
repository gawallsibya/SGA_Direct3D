#pragma once

#include "cVector3.h"

class cMatrix;

class cVector4
{
public:
	cVector4(void);
	cVector4(float _x, float _y, float _z, float _w);
	~cVector4(void);

	float x, y, z, w;

	cVector4		operator+(cVector4& v);
	cVector4		operator-(cVector4& v);
	cVector4		operator*(float f);
	cVector4		operator*(cMatrix& mat);
	bool			operator==(cVector4& v);
	bool			operator!=(cVector4& v);
	cVector3		ToVector3();
};

