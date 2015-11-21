#include "StdAfx.h"
#include "cCircularQueue.h"


cCircularQueue::cCircularQueue(void)
	: m_nFront(0)
	, m_nRear(0)
{
}


cCircularQueue::~cCircularQueue(void)
{
}

char* cCircularQueue::GetToken( FILE* fp )
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

void cCircularQueue::Run()
{
	FILE* fp = NULL;
	fopen_s(&fp, "queue_data.txt", "r");
	
	while(char* szToken = GetToken(fp))
	{
		if(strcmp(szToken, "e") == 0)
		{
			szToken = GetToken(fp);
			int n = atoi(szToken);

			Enqueue(n);
		}
		else if(strcmp(szToken, "d") == 0)
		{
			Dequeue();
		}
		else if(strcmp(szToken, "p") == 0)
		{
			PrintQueue();
		}
	}

	fclose(fp);
}

void cCircularQueue::Enqueue( int n )
{
	if(IsFull())
		return;
	
	m_aData[m_nRear] = n;

	m_nRear = (m_nRear + 1) % QUEUE_SIZE;
}

void cCircularQueue::Dequeue()
{
	if(IsEmpty())
		return;

	m_nFront = (m_nFront + 1) % QUEUE_SIZE;
}

void cCircularQueue::PrintQueue()
{
	for (int i = m_nFront; i != m_nRear; i = (i + 1) % QUEUE_SIZE)
	{
		std::cout << m_aData[i] << std::endl;
	}
}

bool cCircularQueue::IsFull()
{
	return (m_nRear + 1) % QUEUE_SIZE == m_nFront;
}

bool cCircularQueue::IsEmpty()
{
	return m_nRear == m_nFront;
}
