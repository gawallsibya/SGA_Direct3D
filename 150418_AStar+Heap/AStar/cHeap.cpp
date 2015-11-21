#include "StdAfx.h"
#include "cHeap.h"
#include "cNode.h"

cHeap::cHeap(void)
{
}


cHeap::~cHeap(void)
{
}

void cHeap::Insert( cNode* pNode )
{
	pNode->m_nIndexAtHeap = m_vecNode.size();
	m_vecNode.push_back(pNode);
	Update(pNode);
}

cNode* cHeap::GetMinFNode()
{
	if(m_vecNode.empty())
		return NULL;

	cNode* pMinFNode = m_vecNode[0];

	if(m_vecNode.size() == 1)
	{
		m_vecNode.clear();
		return pMinFNode;
	}

	m_vecNode[0] = m_vecNode.back();
	m_vecNode[0]->m_nIndexAtHeap = 0;
	m_vecNode.pop_back();

	UpdateLower(m_vecNode[0]);
	
	return pMinFNode;
}

void cHeap::Update( cNode* pNode )
{
	UpdateUpper(pNode);
	UpdateLower(pNode);
}

void cHeap::Swap( int nIndex1, int nIndex2 )
{
	int nTemp = m_vecNode[nIndex2]->m_nIndexAtHeap;
	m_vecNode[nIndex2]->m_nIndexAtHeap = m_vecNode[nIndex1]->m_nIndexAtHeap;
	m_vecNode[nIndex1]->m_nIndexAtHeap = nTemp;

	cNode* pTemp = m_vecNode[nIndex2];
	m_vecNode[nIndex2] = m_vecNode[nIndex1];
	m_vecNode[nIndex1] = pTemp;
}

void cHeap::UpdateUpper( cNode* pNode )
{
	if(pNode->m_nIndexAtHeap == 0)
		return;

	int nParentIndex = (pNode->m_nIndexAtHeap - 1) / 2;

	if(pNode->m_fF < m_vecNode[nParentIndex]->m_fF)
	{
		Swap(nParentIndex, pNode->m_nIndexAtHeap);
		
		UpdateUpper(m_vecNode[nParentIndex]);
	}
}

void cHeap::UpdateLower( cNode* pNode )
{
	cNode* pMinFNode = NULL;
	int nLeftChild = pNode->m_nIndexAtHeap * 2 + 1;
	if(nLeftChild >= m_vecNode.size())	//왼쪽 자식이 없음.
	{
		return;
	}
	pMinFNode = m_vecNode[nLeftChild];

	int nRightChild = pNode->m_nIndexAtHeap * 2 + 2;
	if(nRightChild < m_vecNode.size())	//오른쪽 자식이 있음.
	{
		if(m_vecNode[nRightChild]->m_fF < m_vecNode[nLeftChild]->m_fF)
		{
			pMinFNode = m_vecNode[nRightChild];
		}
	}

	//최소값을 갖는 노드 찾음.

	if(pMinFNode->m_fF < pNode->m_fF)
	{
		Swap(pMinFNode->m_nIndexAtHeap, pNode->m_nIndexAtHeap);
		UpdateLower(pNode);
	}
}
