#pragma once

#define g_pD3DDevice cDeviceMgr::GetInstance().GetDevice()

class cDeviceMgr
{
	cDeviceMgr(void);

	LPDIRECT3D9				m_pD3D;
	LPDIRECT3DDEVICE9		m_pD3DDevice;

public:
	~cDeviceMgr(void);

	static cDeviceMgr& GetInstance();
	void CreateDevice(HWND hWnd);
	LPDIRECT3DDEVICE9 GetDevice();
};
