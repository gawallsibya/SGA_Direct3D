#pragma once

#include "cFrame.h"

class cRightLeg : public cFrame
{
public:
	cRightLeg(void);
	~cRightLeg(void);

	virtual void Setup() override;
	virtual void Update( D3DXMATRIXA16* pParent ) override;
};




