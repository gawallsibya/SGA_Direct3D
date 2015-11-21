#include "StdAfx.h"
#include "cVector3.h"


cVector3::cVector3(void)
	: x(0.0f)
	, y(0.0f)
	, z(0.0f)
{
}

cVector3::cVector3( float _x, float _y, float _z )
	: x(_x)
	, y(_y)
	, z(_z)
{

}


cVector3::~cVector3(void)
{
}

cVector3 cVector3::operator+( cVector3& v )
{
	cVector3 ret;

	ret.x = x + v.x;
	ret.y = y + v.y;
	ret.z = z + v.z;

	return ret;
}

cVector3 cVector3::operator-( cVector3& v )
{
	cVector3 ret;

	ret.x = x - v.x;
	ret.y = y - v.y;
	ret.z = z - v.z;

	return ret;
}

cVector3 cVector3::operator*( float f )
{
	cVector3 ret;

	ret.x = x * f;
	ret.y = y * f;
	ret.z = z * f;

	return ret;
}

bool cVector3::operator==( cVector3& v )
{
	float fEpsilon = 0.0001f;
	if(fabs(x - v.x) > fEpsilon)
		return false;
	if(fabs(y - v.y) > fEpsilon)
		return false;
	if(fabs(z - v.z) > fEpsilon)
		return false;
	return true;
}

bool cVector3::operator!=( cVector3& v )
{
	return !((*this) == v);
}

float cVector3::Length()
{
	return (float)sqrt(x * x + y * y + z * z);
}

cVector3 cVector3::Normalize()
{
	cVector3 ret = (*this);
	float l = ret.Length();
	ret.x /= l;
	ret.y /= l;
	ret.z /= l;
	return ret;
}

float cVector3::Dot( cVector3& v1, cVector3& v2 )
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

cVector3 cVector3::Cross( cVector3& v1, cVector3& v2 )
{
	cVector3 ret;
	ret.x = v1.y * v2.z - v1.z * v2.y;
	ret.y = v1.z * v2.x - v1.x * v2.z;
	ret.z = v1.x * v2.y - v1.y * v2.x;
	return ret;
}
