#pragma once

#define QUEUE_SIZE 5

class cCircularQueue
{
private:
	int m_aData[QUEUE_SIZE];
	int	m_nFront;
	int	m_nRear;

public:
	cCircularQueue(void);
	~cCircularQueue(void);

	void Run();

private:
	char* GetToken(FILE* fp);
	void Enqueue(int n);
	void Dequeue();
	void PrintQueue();
	bool IsFull();
	bool IsEmpty();
};

