#pragma once
class cNode
{
public:
	int		m_nValue;
	cNode*	m_pLChild;
	cNode*	m_pRChild;

public:
	cNode(void);
	~cNode(void);

	void Insert(int n);
	cNode* Delete(int n, cNode** ppThis);
	void Print();
	cNode* GetMinNode();
};

