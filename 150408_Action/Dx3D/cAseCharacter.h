#pragma once
#include "cCharacter.h"

class cFrame;

class cAseCharacter : public cCharacter
{
private:
	cFrame* m_pRoot;

public:
	cAseCharacter(void);
	virtual ~cAseCharacter(void);

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
};

