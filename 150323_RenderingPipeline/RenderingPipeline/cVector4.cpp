#include "StdAfx.h"
#include "cVector4.h"
#include "cMatrix.h"

cVector4::cVector4(void)
	: x(0.0f)
	, y(0.0f)
	, z(0.0f)
	, w(0.0f)
{
}

cVector4::cVector4( float _x, float _y, float _z, float _w )
	: x(_x)
	, y(_y)
	, z(_z)
	, w(_w)
{

}


cVector4::~cVector4(void)
{
}

cVector4 cVector4::operator+( cVector4& v )
{
	cVector4 ret;
	ret.x = x + v.x;
	ret.y = y + v.y;
	ret.z = z + v.z;
	ret.w = w + v.w;
	return ret;
}

cVector4 cVector4::operator-( cVector4& v )
{
	cVector4 ret;
	ret.x = x - v.x;
	ret.y = y - v.y;
	ret.z = z - v.z;
	ret.w = w - v.w;
	return ret;
}

cVector4 cVector4::operator*( float f )
{
	cVector4 ret;
	ret.x = x * f;
	ret.y = y * f;
	ret.z = z * f;
	ret.w = w * f;
	return ret;
}

cVector4 cVector4::operator*( cMatrix& mat )
{
	cVector4 ret;
	ret.x = x * mat[0][0] + y * mat[1][0] + z * mat[2][0] + w * mat[3][0];
	ret.y = x * mat[0][1] + y * mat[1][1] + z * mat[2][1] + w * mat[3][1];
	ret.z = x * mat[0][2] + y * mat[1][2] + z * mat[2][2] + w * mat[3][2];
	ret.w = x * mat[0][3] + y * mat[1][3] + z * mat[2][3] + w * mat[3][3];

	if(fabs(ret.w) > 0.00001f)
	{
		ret.x /= ret.w;
		ret.y /= ret.w;
		ret.z /= ret.w;
		ret.w /= ret.w;
	}

	return ret;
}

bool cVector4::operator==( cVector4& v )
{
	float fEpsilon = 0.0001f;
	if(fabs(x - v.x) > fEpsilon)
		return false;
	if(fabs(y - v.y) > fEpsilon)
		return false;
	if(fabs(z - v.z) > fEpsilon)
		return false;
	if(fabs(w - v.w) > fEpsilon)
		return false;
	return true;
}

bool cVector4::operator!=( cVector4& v )
{
	return !((*this) == v);
}

cVector3 cVector4::ToVector3()
{
	cVector3 v;
	v.x = x; v.y = y; v.z = z;
	return v;
}
