#pragma once

class cGrid
{
	std::vector<ST_PC_VERTEX> m_LineVertex;
	int m_nNumHalf;
public:
	cGrid(void);
	virtual ~cGrid(void);

	void Setup(float fGap, int nNumHalf);
	void Render();
};
