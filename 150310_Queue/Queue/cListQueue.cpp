#include "StdAfx.h"
#include "cListQueue.h"
#include "cNode.h"

cListQueue::cListQueue(void)
	: m_pFront(NULL)
	, m_pRear(NULL)
{
}


cListQueue::~cListQueue(void)
{
	if(m_pFront)
		m_pFront->Destroy();
}

void cListQueue::Enqueue( int n )
{
	cNode* pNode = new cNode;
	
	pNode->m_nValue = n;

	Enqueue(pNode);
}

void cListQueue::Enqueue( cNode* pNode )
{
	pNode->m_pNext = NULL;

	if (m_pFront)
	{
		m_pRear->m_pNext = pNode;
		m_pRear = pNode;
	}
	else
	{	
		m_pFront = pNode;
		m_pRear = pNode;
	}
}

cNode* cListQueue::Dequeue()
{
	if(m_pFront == NULL)
		return NULL;

	cNode* pTemp = m_pFront;
	m_pFront = m_pFront->m_pNext;
	
	if(m_pFront == NULL)
		m_pRear = NULL;

	return pTemp;
}

void cListQueue::PrintQueue()
{
	if(m_pFront)
		m_pFront->Print();
}
