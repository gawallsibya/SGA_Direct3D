#pragma once

#define g_pTextureManager cTextureManager::GetInstance()

class cTextureManager
{
private:
	std::map<std::string, LPDIRECT3DTEXTURE9>	m_mapTexture;
	std::map<std::string, D3DXIMAGE_INFO>		m_mapImageInfo;
public:
	SINGLETONE(cTextureManager);
	
	LPDIRECT3DTEXTURE9 GetTexture(char* szFullPath);
	LPDIRECT3DTEXTURE9 GetTexture(std::string sFullPath);
	LPDIRECT3DTEXTURE9 GetTexture(std::string sFullPath, D3DXIMAGE_INFO* pImageInfo);
	void Destroy();
};

