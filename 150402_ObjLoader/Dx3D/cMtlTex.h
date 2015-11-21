#pragma once

class cMtlTex : public cObject
{
	friend class cObjLoader;
	friend class cGroup;

private:
	LPDIRECT3DTEXTURE9	m_pTexture;
	D3DMATERIAL9		m_stMtl;

public:
	cMtlTex(void);
	~cMtlTex(void);

	void SetTexture(char* szFullPath);
};

