// LinkedList.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
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

