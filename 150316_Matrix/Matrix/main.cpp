// Matrix.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "cMatrix.h"

int _tmain(int argc, _TCHAR* argv[])
{
	cMatrix mat1(4), mat2(4);
	
	int nCnt = 0;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			//mat1[i][j] = (i == j) ? 2 : 0;
			mat1[i][j] = rand() % 10 - 5;
		}
	}

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			mat2[i][j] = nCnt++;
			mat2[i][j] = (i == j) ? 2 : 0;
		}
	}

	(mat1 * mat2).Print();
	std::cout << ((mat1 != mat2) ? "true" : "false") << std::endl;

	float fDet = 0;
	cMatrix matInv = mat1.Inverse(fDet);
	if(fabs(fDet) > 0.00001f)
	{
		matInv.Print();

		(matInv * mat1).Print();
	}
	return 0;
}

