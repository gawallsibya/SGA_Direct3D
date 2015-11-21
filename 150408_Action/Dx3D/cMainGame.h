#pragma once
#include "cAction.h"

class cGrid;
class cCamera;
class cCharacter;
//class cGroup;

class cMainGame : public iActionDelegate
{
private:
	cCamera*			m_pCamera;
	cGrid*				m_pGrid;
	//cGroup*				m_pGroupHead;
	cCharacter*			m_pCharacter;
	LPD3DXFONT			m_pFont;

public:
	cMainGame(void);
	~cMainGame(void);

	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	 
	// iActionDelegate override
	virtual void OnActionFinish(cAction* pSender) override;

private:
	void SetLight();
};

