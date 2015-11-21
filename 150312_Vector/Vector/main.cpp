// Vector.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "cVector3.h"
#include <iostream>

void PrintVector(cVector3& v)
{
	std::cout << "x : " << v.x << std::endl;
	std::cout << "y : " << v.y << std::endl;
	std::cout << "z : " << v.z << std::endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	cVector3 v1(1, 2, 3);
	cVector3 v2(0, 1, -3);
	cVector3 v3(1, 2, 3);

	PrintVector(v1 * 3.0f);

	std::cout << v1.Normalize().Length() << std::endl;
	
	cVector3 v = cVector3::Cross(v1, v2);
	std::cout << cVector3::Dot(v, v1) << std::endl;

	return 0;
}

