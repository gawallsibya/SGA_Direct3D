#include "StdAfx.h"
#include "cNode.h"


cNode::cNode(void)
	: m_nValue(0)
	, m_pNext(NULL)
{
}


cNode::~cNode(void)
{
}

void cNode::Insert( int n )
{
	if(m_pNext)
	{
		m_pNext->Insert(n);
	}
	else
	{
		cNode* pNode = new cNode;
		pNode->m_nValue = n;

		m_pNext = pNode;
	}
}

void cNode::Print()
{
	std::cout << m_nValue << std::endl;

	if (m_pNext)
	{
		m_pNext->Print();
	}
}

void cNode::Delete( int n, cNode** ppThis )
{
	if(m_nValue == n)
	{
		(*ppThis) = m_pNext;
		delete this;
	}
	else
	{
		if(m_pNext)
			m_pNext->Delete(n, &m_pNext);
	}
}

void cNode::Reverse( cNode* pPrev )
{
	if(m_pNext)
		m_pNext->Reverse(this);

	m_pNext = pPrev;
}

cNode* cNode::GetTail()
{
	if (m_pNext)
	{
		return m_pNext->GetTail();
	}
	return this;
}

void cNode::Destroy()
{
	if(m_pNext)
		m_pNext->Destroy();
	delete this;
}
