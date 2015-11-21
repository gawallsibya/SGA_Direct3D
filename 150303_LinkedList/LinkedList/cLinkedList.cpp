#include "StdAfx.h"
#include "cLinkedList.h"
#include "cNode.h"
#include <iostream>
using namespace std;


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
		cNode* newNode = new cNode;
		newNode->m_nValue = n;
		newNode->m_pNext = NULL;

		cNode* temp = m_pHead;
		while (temp->m_pNext != NULL)
		{
			temp = temp->m_pNext;
		}
		temp->m_pNext = newNode;
	}
	else
	{
		m_pHead = new cNode;
		m_pHead->m_nValue = n;
	}
}
void cLinkedList::Print()
{
	if (m_pHead)
	{
		if (m_pHead->m_pNext == NULL)
		{
			cout << m_pHead->m_nValue << endl;
		}
		else
		{
			cNode* temp = m_pHead;
			while (temp->m_pNext != NULL)
			{
				cout << temp->m_nValue << endl;
				temp = temp->m_pNext;
			}
			cout << temp->m_nValue << endl;
		}

	}
	else
	{
		cout << "리스트가 없음" << endl;
	}
}
void cLinkedList::Delete(int n)
{
	cNode* prev = NULL;
	cNode* temp = m_pHead;

	if (temp == NULL)
	{
		return;
	}
	else
	{
		if (m_pHead->m_nValue == n)
		{
			m_pHead = m_pHead->m_pNext;
			delete temp;
		}
		else
		{
			while (temp->m_nValue != n)
			{
				if (temp->m_pNext == NULL) return;
				prev = temp;
				temp = temp->m_pNext;
			}
			prev->m_pNext = temp->m_pNext;
			delete temp;
		}
	}

}
void cLinkedList::Reverse()
{
	cNode* prev = NULL;
	cNode* temp = m_pHead;
	

	if (temp == NULL || temp->m_pNext == NULL)
	{
		return;
	}
	else
	{
		cNode* next;
		while(temp->m_pNext != NULL)
		{
			next = temp->m_pNext;
			temp->m_pNext = prev;
			prev = temp;
			temp = next;
		}
		m_pHead = temp;
		m_pHead->m_pNext = prev;
	}
}