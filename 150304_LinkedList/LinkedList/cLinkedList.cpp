#include "StdAfx.h"
#include "cLinkedList.h"
#include "cNode.h"

cLinkedList::cLinkedList(void)
	: m_pHead(NULL)
{
}


cLinkedList::~cLinkedList(void)
{
}

void cLinkedList::Insert(int n)
{
	if(m_pHead)
	{
		m_pHead->Insert(n);
	}
	else
	{
		m_pHead = new cNode;
		m_pHead->m_nValue = n;
	}
}

void cLinkedList::Print()
{
	if(m_pHead)
		m_pHead->Print();
}

void cLinkedList::Delete( int n )
{
	if(m_pHead)
		m_pHead->Delete(n, &m_pHead);
}

void cLinkedList::Reverse()
{
	if(!m_pHead)
		return;

	cNode* pTail = m_pHead->GetTail();
	m_pHead->Reverse(NULL);
	m_pHead = pTail;
}
