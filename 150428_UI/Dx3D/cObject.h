#pragma once

class cObject
{
protected:
	int m_nRefCount;
	
	SYNTHESIZE(int, m_nTag, Tag);

public:
	cObject(void);
	virtual ~cObject(void);

	virtual void AddRef()
	{
		++m_nRefCount;
	}

	virtual void Release()
	{
		--m_nRefCount;
		if(m_nRefCount == 0)
			delete this;
	}
};

