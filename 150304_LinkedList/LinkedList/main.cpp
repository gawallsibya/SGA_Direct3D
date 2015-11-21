// LinkedList.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "cLinkedList.h"

int _tmain(int argc, _TCHAR* argv[])
{
	FILE* fp;
	fopen_s(&fp, "calc_data.txt", "r");
	while(true)
	{
		char c = fgetc(fp);
		if(feof(fp))
			break;
		std::cout << c << std::endl;
	}
	
	fclose(fp);

	/*
	cLinkedList ll;
	ll.Insert(1);
	ll.Insert(2);
	ll.Insert(3);
	ll.Insert(4);
	ll.Reverse();
	ll.Print();
	*/
// 	ll.Delete(1);
// 
// 	ll.Insert(1);
// 	ll.Delete(1);
// 	ll.Delete(1);
// 
// 	ll.Insert(3);
// 	ll.Reverse();
// 	ll.Print();
// 	ll.Delete(1);
// 	ll.Print();
	
	return 0;
}

