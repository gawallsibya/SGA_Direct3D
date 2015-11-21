#pragma once

#include "cCharacter.h"

class cCube : public cCharacter
{
private:
	std::vector<ST_PC_VERTEX> m_vecVertex;

public:
	cCube(void);
	virtual ~cCube(void);

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
};

