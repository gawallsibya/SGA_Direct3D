#pragma once
class cRay
{
private:
	enum eRaySpace
	{
		E_NONE,
		E_VIEW,
		E_WORLD,
	};

	eRaySpace	m_eRaySpace;
	D3DXVECTOR3 m_vOrg;
	D3DXVECTOR3 m_vDir;

public:
	cRay(void);
	~cRay(void);

	static cRay RayAtViewSpace(int x, int y);
	static cRay RayAtWorldSpace(int x, int y);
	cRay Transform(D3DXMATRIXA16& mat);
	bool IsPicked(D3DXVECTOR3& vSphereCenter, float fSphereRadius);
};

