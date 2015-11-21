#pragma once

class cUIImageView : public cUIObject
{
private:
	SYNTHESIZE(std::string, m_sImageName, ImageName);

public:
	cUIImageView(void);
	virtual ~cUIImageView(void);

	virtual void Update(D3DXVECTOR3* pvParentWorld) override;
	virtual void Render(LPD3DXSPRITE pSprite) override;
	
};

