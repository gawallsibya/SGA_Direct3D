#pragma once

class cNode;

class cListQueue
{
	friend class cNiceQueue;

protected:
	cNode* m_pFront;
	cNode* m_pRear;

public:
	cListQueue(void);
	virtual ~cListQueue(void);

	virtual void Enqueue(int n);
	virtual cNode* Dequeue();
	virtual void PrintQueue();

protected:
	virtual void Enqueue(cNode* pNode);
};

