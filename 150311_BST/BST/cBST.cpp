#include "StdAfx.h"
#include "cBST.h"
#include "cNode.h"

cBST::cBST(void)
	: m_pRoot(NULL)
{
}


cBST::~cBST(void)
{
}

void cBST::Insert( int n )
{
	if(m_pRoot)
	{
		m_pRoot->Insert(n);
	}
	else
	{
		m_pRoot = new cNode;
		m_pRoot->m_nValue = n;
	}
}

void cBST::Delete( int n )
{
	if(m_pRoot)
	{
		cNode* pDeleteNode = m_pRoot->Delete(n, &m_pRoot);
		if(pDeleteNode)
			delete pDeleteNode;
	}
}

void cBST::Print()
{
	if(m_pRoot)
	{
		m_pRoot->Print();
	}
}
