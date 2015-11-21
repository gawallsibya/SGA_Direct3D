#pragma once

class cUIButton;

class iUIButtonDelegate
{
public:
	virtual void OnClick(cUIButton* pSender) = 0;
};

class cUIButton : public cUIObject
{
private:
	enum eButtonState
	{
		E_NORMAL,
		E_MOUSE_OVER,
		E_SELECTED,
	};

	eButtonState m_eButtonState;

private:
	SYNTHESIZE(std::string, m_sNormalImage, NormalImage);
	SYNTHESIZE(std::string, m_sMouseOverImage, MouseOverImage);
	SYNTHESIZE(std::string, m_sSelectedImage, SelectedImage);
	SYNTHESIZE(iUIButtonDelegate*, m_pDelegate, Delegate);

public:
	cUIButton(void);
	~cUIButton(void);
	
	virtual void Update(D3DXVECTOR3* pvParentWorld) override;
	virtual void Render(LPD3DXSPRITE pSprite) override;
};

