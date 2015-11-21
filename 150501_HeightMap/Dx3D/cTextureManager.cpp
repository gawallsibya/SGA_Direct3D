#include "StdAfx.h"
#include "cTextureManager.h"


cTextureManager::cTextureManager(void)
{
}


cTextureManager::~cTextureManager(void)
{
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture( char* szFilename, D3DXIMAGE_INFO* pImageInfo /*= NULL*/ )
{
	return GetTexture(std::string(szFilename), pImageInfo);
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture( std::string& sFilename, D3DXIMAGE_INFO* pImageInfo /*= NULL*/ )
{
	if(pImageInfo)
	{
		if( m_mapImageInfo.find(sFilename) == m_mapImageInfo.end() ||
			m_mapTexture.find(sFilename) == m_mapTexture.end())
		{
			SAFE_RELEASE(m_mapTexture[sFilename]);

			D3DXCreateTextureFromFileEx(
				g_pD3DDevice,
				sFilename.c_str(), 
				D3DX_DEFAULT_NONPOW2,
				D3DX_DEFAULT_NONPOW2,
				D3DX_DEFAULT,
				0,
				D3DFMT_UNKNOWN, 
				D3DPOOL_MANAGED, 
				D3DX_FILTER_NONE, 
				D3DX_DEFAULT, 
				0,
				&m_mapImageInfo[sFilename],
				NULL,
				&m_mapTexture[sFilename] );
		}
	}
	else if(m_mapTexture.find(sFilename) == m_mapTexture.end())
	{
		D3DXCreateTextureFromFile(g_pD3DDevice, sFilename.c_str(), &m_mapTexture[sFilename]);
	}

	if(pImageInfo)
		*pImageInfo = m_mapImageInfo[sFilename];
	
	return m_mapTexture[sFilename];
}

void cTextureManager::Destroy()
{
	for each(auto p in m_mapTexture)
	{
		SAFE_RELEASE(p.second);
	}
}
