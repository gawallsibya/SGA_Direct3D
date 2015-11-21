#pragma once

class cNode;

class cLinkedList
{
private:
	cNode* m_pHead;

public:
	cLinkedList(void);
	~cLinkedList(void);

	void Insert(int n);
	void Delete(int n);
	void Print();
	void Reverse();
};

