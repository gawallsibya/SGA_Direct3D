#pragma once

class cMatrix;

class cVector3
{
public:
	cVector3(void);
	cVector3(float _x, float _y, float _z);
	~cVector3(void);

	float x, y, z;

	cVector3		operator+(cVector3& v);
	cVector3		operator-(cVector3& v);
	cVector3		operator*(float f);
	bool			operator==(cVector3& v);
	bool			operator!=(cVector3& v);
	float			Length();
	cVector3		Normalize();
	cVector3		TransformCoord(cMatrix* pmat);
	static float	Dot(cVector3& v1, cVector3& v2);
	static cVector3 Cross(cVector3& v1, cVector3& v2);
};

