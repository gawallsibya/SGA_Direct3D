#pragma once

#include "cFrame.h"
#include "cCharacter.h"

class cBody : public cFrame
{
private:
	cCharacter* m_pCharacter;

public:
	cBody(void);
	~cBody(void);

public:
	virtual void Setup() override;
	virtual void Update(D3DXMATRIXA16* pParent) override;
};

