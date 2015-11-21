#include "StdAfx.h"
#include "cNiceQueue.h"
#include "cNode.h"

cNiceQueue::cNiceQueue(void)
{
	m_pDummyQueue = new cListQueue;
}


cNiceQueue::~cNiceQueue(void)
{
	delete m_pDummyQueue;
}

void cNiceQueue::Enqueue( int n )
{
	cNode* pNode = m_pDummyQueue->Dequeue();
	
	if(pNode == NULL)
	{
		pNode = new cNode;
	}

	pNode->m_nValue = n;
	pNode->m_pNext = NULL;

	cListQueue::Enqueue(pNode);
}

cNode* cNiceQueue::Dequeue()
{
	cNode* pNode = cListQueue::Dequeue();
	if(pNode)
		m_pDummyQueue->Enqueue(pNode);

	return NULL;
}
