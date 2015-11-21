#pragma once

struct ST_MTL_TEX;
struct ST_GROUP;

class cObjParser
{
private:
	std::vector<D3DXVECTOR3>			m_V;
	std::vector<D3DXVECTOR2>			m_VT;
	std::vector<D3DXVECTOR3>			m_VN;

public:
	cObjParser(void);
	~cObjParser(void);

	void Load(IN char* szFileName,
		OUT std::vector<ST_GROUP*>& Groups,
		OUT std::map<std::string, ST_MTL_TEX> &MtlTex);

	void LoadSurface(IN char* szFileName,
		OUT std::vector<D3DXVECTOR3>& vSurface,
		IN D3DXMATRIXA16* mMat = NULL);

	void ProcessMtl(IN char* szFileName,
		OUT std::map<std::string, ST_MTL_TEX> &MtlTex);

	bool IsStartWith( char* szStr, char* szBeginStr );

	void Clear();
};

