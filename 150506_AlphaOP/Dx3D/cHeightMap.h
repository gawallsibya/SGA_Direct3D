#pragma once
class cHeightMap
{
private:
	LPD3DXMESH					m_pMesh;
	std::string					m_sTexture;
	D3DMATERIAL9				m_stMtl;
	std::vector<D3DXVECTOR3>	m_vecVertex;
	int							m_nTile;
public:
	cHeightMap(void);
	~cHeightMap(void);

	void Setup(char* szFolder, char* szRawFile, char* szTextureFile, int nBytesPerColor = 1);
	void Render();
	bool GetHeight(IN float x, OUT float& y, IN float z);
};

