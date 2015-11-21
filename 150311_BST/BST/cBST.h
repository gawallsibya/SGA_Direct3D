#pragma once

class cNode;

class cBST
{
private:
	cNode* m_pRoot;
public:
	cBST(void);
	~cBST(void);

	void Insert(int n);
	void Delete(int n);
	void Print();
};

