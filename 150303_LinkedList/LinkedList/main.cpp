// LinkedList.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "cLinkedList.h"

int _tmain(int argc, _TCHAR* argv[])
{
	cLinkedList ll;
	ll.Delete(1);

	ll.Insert(1);
	ll.Delete(1);
	ll.Delete(1);

	ll.Insert(3);
	ll.Reverse();
	ll.Print();
	ll.Delete(1);
	ll.Print();
	
	return 0;
}

