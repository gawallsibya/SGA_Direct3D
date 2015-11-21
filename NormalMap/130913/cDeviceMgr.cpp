#include "StdAfx.h"
#include "cDeviceMgr.h"

cDeviceMgr::cDeviceMgr(void)
{
	m_pD3D = NULL;
	m_pD3DDevice = NULL;
}

cDeviceMgr::~cDeviceMgr(void) 
{
	SAFE_RELEASE(m_pD3D);
	SAFE_RELEASE(m_pD3DDevice);
}

cDeviceMgr& cDeviceMgr::GetInstance()
{
	static cDeviceMgr instance;
	return instance;
}

void cDeviceMgr::CreateDevice(HWND hWnd)
{
	//d3d9.lib d3dx9d.lib
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	assert(m_pD3D);

	D3DCAPS9	caps;
	int			nVP;
	m_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);
	if(caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		nVP = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		nVP = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	D3DPRESENT_PARAMETERS d3dpp;
	memset(&d3dpp, 0, sizeof(d3dpp));
	d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed					= TRUE;
	d3dpp.BackBufferFormat			= D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil	= TRUE;
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D16;

	m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		nVP,
		&d3dpp,
		&m_pD3DDevice);

	assert(m_pD3DDevice);
}

LPDIRECT3DDEVICE9 cDeviceMgr::GetDevice()
{
	return m_pD3DDevice;
}
