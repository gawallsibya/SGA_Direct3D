#pragma once

class cMtlTex : public cObject
{
	friend class cObjLoader;
	friend class cGroup;
	friend class cAseLoader;
	friend class cFrame;

private:
	LPDIRECT3DTEXTURE9	m_pTexture;
	D3DMATERIAL9		m_stMtl;

public:
	cMtlTex(void);
	virtual ~cMtlTex(void);

	void SetTexture(char* szFullPath);
};

