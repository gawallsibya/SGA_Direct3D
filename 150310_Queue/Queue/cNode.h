#pragma once

class cNode
{
public:
	cNode(void);
	~cNode(void);

	int		m_aDummy[1023];
	int		m_nValue;
	cNode*	m_pNext;

	void Insert(int n);
	void Print();
	void Delete(int n, cNode** ppThis);
	void Reverse(cNode* pPrev);
	cNode* GetTail();
	void Destroy();
};

