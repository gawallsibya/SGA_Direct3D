// StackCalc.cpp : ÄÜ¼Ö ÀÀ¿ë ÇÁ·Î±×·¥¿¡ ´ëÇÑ ÁøÀÔÁ¡À» Á¤ÀÇÇÕ´Ï´Ù.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>

std::map<std::string, int> g_mapPriority;


void Re()
{
	int a[50];
	Re();
}

bool IsOperand(int& nIndex, const char* szInfix)
{
	char c = szInfix[nIndex];

	if(c == '+' || c == '*' || c == '/' || c == '(' || c == ')')
		return false;
	
	if(c == '.')
		return true;

	if(c == '-')
	{
		if(nIndex != 0 && szInfix[nIndex - 1] == '(')
			return true;
		else 
			return false;
	}

	return true;
}

bool IsOperator(char* szToken)
{
	if(strcmp(szToken, "+") == 0)
		return true;
	if(strcmp(szToken, "-") == 0)
		return true;
	if(strcmp(szToken, "*") == 0)
		return true;
	if(strcmp(szToken, "/") == 0)
		return true;
	if(strcmp(szToken, "(") == 0)
		return true;
	if(strcmp(szToken, ")") == 0)
		return true;
	return false;
}

char* GetToken(int& nIndex, const char* szInfix)
{
	if(strlen(szInfix) <= (size_t)nIndex)
		return NULL;

	static char szToken[1024];
	
	int nCurr = 0;
	
	while(true)
	{
		if(IsOperand(nIndex, szInfix))
		{
			szToken[nCurr] = szInfix[nIndex];
			nCurr++;
			nIndex++;
		}
		else
		{
			if(nCurr > 0)
			{
				//--nIndex;
				break;
			}
			szToken[nCurr] = szInfix[nIndex];
			nIndex++;
			nCurr++;
			break;
		}
	}
	
	szToken[nCurr] = '\0';

	return szToken;
}

int _tmain(int argc, _TCHAR* argv[])
{
	/*
	- °ýÈ£ ( )
	- ºÎÈ£ + -
	- N Á¦°ö ¿¬»ê ^
	- °ö¼À ³ª´°¼À * /
	- µ¡¼À »¬¼À + -
	- XOR¿¬»ê #
	*/

	/*
	g_mapPriority["*"] = 10;
	g_mapPriority["/"] = 10;
	g_mapPriority["+"] = 9;
	g_mapPriority["-"] = 9;
	g_mapPriority["("] = 8;

	std::vector<std::string> vecPostfix;
	std::vector<std::string> vecOperatorStack;

	std::string sToken;
	char szTemp[1024] = {0, };
	int nCnt = 1;

	FILE* fp;
	fopen_s(&fp, "calc_data.txt", "r");
	fgets(szTemp, 1024, fp);
	fclose(fp);

	std::string sInfix(szTemp);
	sInfix = std::string("(") + sInfix + std::string(")");

	int nIndex = 0;
	while(char* szToken = GetToken(nIndex, sInfix.c_str()))
	{
		if(IsOperator(szToken))
		{
			if(strcmp(szToken, "(") == 0)
			{
				vecOperatorStack.push_back(std::string(szToken));
			}
			else if(strcmp(szToken, ")") == 0)
			{
				while(true)
				{
					std::string sOperator = vecOperatorStack.back();
					vecOperatorStack.pop_back();
					if(sOperator == std::string("("))
					{
						break;
					}
					else
					{
						vecPostfix.push_back(sOperator);
					}
				}
			}
			else
			{
				while(true)
				{
					std::string sCurrOperator = std::string(szToken);
					std::string sTopOperator = vecOperatorStack.back();

					if(g_mapPriority[sTopOperator] < g_mapPriority[sCurrOperator])
					{
						vecOperatorStack.push_back(sCurrOperator);
						break;
					}
					else
					{
						vecPostfix.push_back(sTopOperator);
						vecOperatorStack.pop_back();
					}
				}
			}
		}
		else
		{
			vecPostfix.push_back(std::string(szToken));
		}
	}

	std::vector<double> vecCalcStack;

	for (size_t i = 0; i < vecPostfix.size(); ++i)
	{
		if(IsOperator((char*)vecPostfix[i].c_str()))
		{
			double v1 = vecCalcStack.back();
			vecCalcStack.pop_back();
			double v2 = vecCalcStack.back();
			vecCalcStack.pop_back();
			double v = 0.0f;
			if(vecPostfix[i] == std::string("+"))
			{
				v = v2 + v1;
			}
			else if(vecPostfix[i] == std::string("-"))
			{
				v = v2 - v1;
			}
			else if(vecPostfix[i] == std::string("*"))
			{
				v = v2 * v1;
			}
			else if(vecPostfix[i] == std::string("/"))
			{
				v = v2 / v1;
			}
			vecCalcStack.push_back(v);
		}
		else
		{
			vecCalcStack.push_back(atof(vecPostfix[i].c_str()));
		}
	}

	std::cout << vecCalcStack.back() << std::endl;
	*/

	return 0;
}

