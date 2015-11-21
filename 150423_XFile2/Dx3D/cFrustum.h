#pragma once
class cFrustum
{
private:
	std::vector<D3DXVECTOR3>	m_vecProjPosition;
	
	std::vector<D3DXPLANE>		m_vecPlane;

public:
	cFrustum(void);
	~cFrustum(void);

	void Setup();
	void Update();
	bool IsIn(D3DXVECTOR3& vCenter, float fRadius);
};

