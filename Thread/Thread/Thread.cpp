// Thread.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <Windows.h>
#include <process.h>
#include <iostream>

using namespace std;

int Value;
int ValuePlusOne;
int Cnt = 0;
bool isChecked = false;

CRITICAL_SECTION cs;

DWORD WINAPI ThFunc1(LPVOID lpParam)
{
	while(1)
	{
		EnterCriticalSection(&cs);
		//isChecked = false;
		Value = rand() % 1000;
		ValuePlusOne = Value + 1;
		//isChecked = true;
		LeaveCriticalSection(&cs);
	}
	return 0;
}

DWORD WINAPI ThFunc2(LPVOID lpParam)
{
	while(1)
	{
		EnterCriticalSection(&cs);
		//if(isChecked)
		{
			if(Value > ValuePlusOne)
				printf("%d\n",Cnt++);
		}
		LeaveCriticalSection(&cs);
	}

	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	InitializeCriticalSection(&cs);

	DWORD dwThID1, dwThID2;
	HANDLE hThreads[2];

	unsigned long ulStackSize = 0;


	dwThID1 = 0;
	dwThID2 = 0;

	hThreads[0] = NULL;
	hThreads[1] = NULL;

	hThreads[0] = CreateThread(NULL, ulStackSize, ThFunc1, NULL, CREATE_SUSPENDED, &dwThID1);
	hThreads[1] = CreateThread(NULL, ulStackSize, ThFunc2, NULL, CREATE_SUSPENDED, &dwThID2);

	ResumeThread(hThreads[0]);
	ResumeThread(hThreads[1]);

	WaitForMultipleObjects(2, hThreads, TRUE, INFINITE);

	CloseHandle(hThreads[0]);
	CloseHandle(hThreads[1]);

	DeleteCriticalSection(&cs);

	return 0;
}

