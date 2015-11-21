#include "StdAfx.h"
#include "cNode.h"


cNode::cNode(void)
	: m_nValue(0)
	, m_pLChild(NULL)
	, m_pRChild(NULL)
{
}


cNode::~cNode(void)
{
}

void cNode::Insert( int n )
{
	if(m_nValue < n)
	{
		if(m_pRChild)
			m_pRChild->Insert(n);
		else
		{
			m_pRChild = new cNode;
			m_pRChild->m_nValue = n;
		}
	}
	else if(m_nValue > n)
	{
		if(m_pLChild)
			m_pLChild->Insert(n);
		else
		{
			m_pLChild = new cNode;
			m_pLChild->m_nValue = n;
		}
	} 
}

cNode* cNode::Delete( int n, cNode** ppThis )
{
	if(n < m_nValue)
	{
		if(!m_pLChild)
			return NULL;
		else
			return m_pLChild->Delete(n, &m_pLChild);
	}
	else if(n > m_nValue)
	{
		if(!m_pRChild)
			return NULL;
		else
			return m_pRChild->Delete(n, &m_pRChild);
	}
	else
	{
		if (m_pLChild == NULL && m_pRChild == NULL)
		{
			(*ppThis) = NULL;
			return this;
		}
		else if (m_pLChild != NULL && m_pRChild == NULL)
		{
			(*ppThis) = m_pLChild;
			return this;
		}
		else if (m_pLChild == NULL && m_pRChild != NULL)
		{
			(*ppThis) = m_pRChild;
			return this;
		}
		else
		{
			cNode* pMinNode = m_pRChild->GetMinNode();
			m_nValue = pMinNode->m_nValue;
			return m_pRChild->Delete(m_nValue, &m_pRChild);
		}
	}
}

void cNode::Print()
{
	if(m_pLChild)
		m_pLChild->Print();

	std::cout << m_nValue << std::endl;

	if(m_pRChild)
		m_pRChild->Print();
}

cNode* cNode::GetMinNode()
{
	if(m_pLChild)
		return m_pLChild->GetMinNode();
	return this;
}
