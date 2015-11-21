#pragma once
class cUITextView : public cUIObject
{
private:
	SYNTHESIZE(std::string, m_sText, Text);
	SYNTHESIZE(cFontManager::eFontType, m_eFontType, FontType);
	SYNTHESIZE(DWORD, m_dwDT, DrawTextType);
	SYNTHESIZE(D3DCOLOR, m_dwColor, TextColor);

public:
	cUITextView(void);
	virtual ~cUITextView(void);

	virtual void Render(LPD3DXSPRITE pSprite) override;
};

