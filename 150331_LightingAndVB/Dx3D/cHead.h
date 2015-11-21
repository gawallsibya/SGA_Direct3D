#pragma once

#include "cFrame.h"

class cHead : public cFrame
{
private:
	

public:
	cHead(void);
	~cHead(void);

	virtual void Setup() override;
	virtual void Update(D3DXMATRIXA16* pParent) override;
};

