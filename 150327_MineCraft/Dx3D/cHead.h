#pragma once

#include "cFrame.h"

class cHead : public cFrame
{
public:
	cHead(void);
	~cHead(void);

	virtual void Setup() override;
	virtual void Update(D3DXMATRIXA16* pParent) override;
};

