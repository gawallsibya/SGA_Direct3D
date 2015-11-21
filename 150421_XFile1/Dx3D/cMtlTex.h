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
	DWORD				m_dwAttrId;

public:
	cMtlTex(void);
	~cMtlTex(void);

	void SetTexture(char* szFullPath);
	LPDIRECT3DTEXTURE9 GetTexture()
	{
		return m_pTexture;
	}
	D3DMATERIAL9& GetMaterial()
	{
		return m_stMtl;
	}
};

