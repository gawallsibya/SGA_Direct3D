#pragma once

#include "cFrame.h"

class cLeftLeg : public cFrame
{
public:
	cLeftLeg(void);
	~cLeftLeg(void);

	virtual void Setup() override;
	virtual void Update( D3DXMATRIXA16* pParent ) override;
};

