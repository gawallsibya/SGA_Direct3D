#pragma once

#include "cFrame.h"

class cRightArm : public cFrame
{
public:
	cRightArm(void);
	~cRightArm(void);

	virtual void Setup() override;
	virtual void Update( D3DXMATRIXA16* pParent ) override;
};

