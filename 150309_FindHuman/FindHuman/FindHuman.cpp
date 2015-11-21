// FindHuman.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
#include <vector>

struct ST_PEOPLE
{
	int					nNo;
	bool				isHuman;
	std::vector<int>	vecInterview;
};

char* GetToken(FILE* fp)
{
	static char szToken[8];

	int nCnt = 0;

	while(true)
	{
		char c = fgetc(fp);
		
		if(feof(fp))
			break;

		if(c < 33)
		{
			if(nCnt == 0)
				continue;
			else
				break;
		}

		szToken[nCnt++] = c;

	}

	if(nCnt == 0)
		return NULL;

	szToken[nCnt] = '\0';

	return szToken;
}

void CheckHuman(std::vector<ST_PEOPLE>& vecPeople)
{
	if(vecPeople.empty())
		return;

	vecPeople[0].isHuman = true;

	std::vector<ST_PEOPLE*> vecStack;

	vecStack.push_back(&vecPeople[0]);

	while(!vecStack.empty())
	{
		ST_PEOPLE* pPeople = vecStack.back();
		vecStack.pop_back();
		for (size_t i = 0; i < pPeople->vecInterview.size(); ++i)
		{
			int nNo = pPeople->vecInterview[i];
			if(vecPeople[nNo - 1].isHuman)
				continue;
			vecPeople[nNo - 1].isHuman = true;
			vecStack.push_back(&vecPeople[nNo - 1]);
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	FILE* fp = NULL;

	fopen_s(&fp, "p2-2.txt", "r");

	char* szToken = GetToken(fp);
	
	int nPeople = atoi(szToken);

	std::vector<ST_PEOPLE> vecPeople(nPeople);

	for (int i = 0; i < nPeople; ++i)
	{
		szToken = GetToken(fp);
		int nNo = atoi(szToken);

		szToken = GetToken(fp);
		int nAnswer = atoi(szToken);

		vecPeople[nNo - 1].nNo = nNo;
		vecPeople[nNo - 1].isHuman = false;
		vecPeople[nNo - 1].vecInterview.resize(nAnswer);

		for (int j = 0; j < nAnswer; ++j)
		{
			szToken = GetToken(fp);
			vecPeople[nNo - 1].vecInterview[j] = atoi(szToken);
		}
	}

	CheckHuman(vecPeople);
// 
// 	while(char* szToken = GetToken(fp))
// 	{
// 		std::cout << szToken << std::endl;
// 	}

	int nNumHuman = 0;

	for(size_t i = 0; i < vecPeople.size(); ++i)
	{
		if(vecPeople[i].isHuman)
			nNumHuman++;
	}

	std::cout << nNumHuman << std::endl;


	fclose(fp);

	return 0;
}

