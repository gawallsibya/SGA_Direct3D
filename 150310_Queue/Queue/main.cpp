// Queue.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "cCircularQueue.h"
#include "cListQueue.h"
#include "cNiceQueue.h"
#include <Windows.h>


int _tmain(int argc, _TCHAR* argv[])
{
// 	cCircularQueue cq;
// 	cq.Run();

	DWORD dwStart, dwFinish;
	DWORD dwList, dwNice;

	dwStart = GetTickCount();
	cListQueue lq;
	for (int nLoop = 0; nLoop < 500; ++nLoop)
	{
		for (int i = 0; i < 500; ++i)
		{
			lq.Enqueue(i);
		}
		for (int i = 0; i < 500; ++i)
		{
			cNode* pNode = lq.Dequeue();
			if(pNode)
				delete pNode;
		}
	}
	
	dwFinish = GetTickCount();
	dwList = dwFinish - dwStart;
	dwStart = dwFinish;

	cNiceQueue nq;
	for (int nLoop = 0; nLoop < 500; ++nLoop)
	{
		for (int i = 0; i < 500; ++i)
		{
			nq.Enqueue(i);
		}
		for (int i = 0; i < 500; ++i)
		{
			cNode* pNode = nq.Dequeue();
			if(pNode)
				delete pNode;
		}
	}

	dwFinish = GetTickCount();
	dwNice = dwFinish - dwStart;

	std::cout << "List : " << dwList << std::endl;
	std::cout << "Nice : " << dwNice << std::endl;
	std::cout << "Ratio : " << dwList / (float)dwNice << std::endl;
	return 0;
}

