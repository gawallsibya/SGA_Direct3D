#pragma once
#include "cListQueue.h"

class cNiceQueue : public cListQueue
{
protected:
	cListQueue* m_pDummyQueue;

public:
	cNiceQueue(void);
	virtual ~cNiceQueue(void);

	virtual void Enqueue(int n) override;
	virtual cNode* Dequeue() override;
};

