#pragma once

class iCamera
{
public:
	virtual void Setup() = 0;
	virtual void Update() = 0;
	virtual void SetTarget(D3DXVECTOR3* vTarget) = 0;
	virtual D3DXVECTOR3& GetEye() = 0;
	virtual bool MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) = 0;
};
