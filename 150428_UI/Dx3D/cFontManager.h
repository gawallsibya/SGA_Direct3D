#pragma once

#define g_pFontManager cFontManager::GetInstance()

class cFontManager
{
public:
	enum eFontType
	{
		E_DEFAULT_FONT,
		E_QUEST_FONT,
		E_BUTTON_FONT,
	};

private:
	std::map<eFontType, LPD3DXFONT> m_mapFont;

public:
	SINGLETONE(cFontManager);

public:
	LPD3DXFONT GetFont(eFontType eType);

	void Destroy();
};

