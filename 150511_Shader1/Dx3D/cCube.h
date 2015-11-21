#pragma once
class cCube
{
private:
	std::vector<ST_P_VERTEX>	m_vecVertex;
	LPD3DXEFFECT				m_pEffect;

public:
	cCube(void);
	~cCube(void);
	void Setup();
	void Update();
	void Render();
	LPD3DXEFFECT LoadEffect( const char* szFileName );
};

