#include "StdAfx.h"
#include "cFontManager.h"


cFontManager::cFontManager(void)
{
}


cFontManager::~cFontManager(void)
{
}

LPD3DXFONT cFontManager::GetFont( eFontType eType )
{
	if(m_mapFont.find(eType) == m_mapFont.end())
	{	
		if(eType == E_DEFAULT_FONT)
		{
			//폰트 생성
			D3DXFONT_DESC fd;
			ZeroMemory(&fd,sizeof(D3DXFONT_DESC));
			fd.Height			= 24;
			fd.Width			= 12;
			fd.Weight			= FW_MEDIUM;
			fd.Italic			= false;
			fd.CharSet			= DEFAULT_CHARSET;
			fd.OutputPrecision  = OUT_DEFAULT_PRECIS;
			fd.PitchAndFamily   = FF_DONTCARE;
			strcpy_s(fd.FaceName, "굴림체");	//글꼴 스타일
			//AddFontResource("umberto.ttf");
			//strcpy(fd.FaceName, "umberto");

			D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_mapFont[eType]);
		}
	}

	return m_mapFont[eType];
}

void cFontManager::Destroy()
{
	for each(auto it in m_mapFont)
	{
		SAFE_RELEASE(it.second);
	}
	m_mapFont.clear();
}
