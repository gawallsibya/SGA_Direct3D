#pragma once

#include "cFrame.h"

class cLeftArm : public cFrame
{
public:
	cLeftArm(void);
	~cLeftArm(void);

	virtual void Setup() override;
	virtual void Update( D3DXMATRIXA16* pParent ) override;
};

