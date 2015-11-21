#include "StdAfx.h"
#include "cMainGame.h"
#include "cDeviceMgr.h"
#include "cBox.h"
#include "cGrid.h"
#include "iCamera.h"
#include "cTPSCamera.h"

cMainGame::cMainGame(void)
: m_pGrid(NULL)	
, m_pBox(NULL)		
, m_pCamera(NULL)	
, m_vLookAt(0,0,0)
{
}

cMainGame::~cMainGame(void)
{
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pBox);
	SAFE_DELETE(m_pCamera);
}

void cMainGame::Setup( HWND hWnd )
{
	cDeviceMgr::GetInstance().CreateDevice(hWnd);
	
	m_pGrid = new cGrid;
	m_pGrid->Setup(3, 20);

	m_pBox = new cBox;
	m_pBox->Setup();

	m_pCamera = new cTPSCamera;
	m_pCamera->Setup();
	m_pCamera->SetTarget(&m_vLookAt);

	D3DMATERIAL9 Mtl;
	memset(&Mtl, 0, sizeof(D3DMATERIAL9));

	Mtl.Ambient.r = 0.7f;
	Mtl.Ambient.g = 0.7f;
	Mtl.Ambient.b = 0.7f;
	Mtl.Ambient.a = 1.0f;

	Mtl.Diffuse.r = 0.7f;
	Mtl.Diffuse.g = 0.7f;
	Mtl.Diffuse.b = 0.7f;
	Mtl.Diffuse.a = 1.0f;
	
	g_pD3DDevice->SetMaterial(&Mtl);

	// 조명 세팅
	D3DLIGHT9 DirLight;
	memset(&DirLight, 0, sizeof(D3DLIGHT9));
	
	DirLight.Type = D3DLIGHT_DIRECTIONAL;
	DirLight.Ambient.r = 0.3f;
	DirLight.Ambient.g = 0.3f;
	DirLight.Ambient.b = 0.3f;
	DirLight.Ambient.a = 1.0f;

	DirLight.Diffuse.r = 0.8f;
	DirLight.Diffuse.g = 0.8f;
	DirLight.Diffuse.b = 0.8f;
	DirLight.Diffuse.a = 1.0f;
	
	D3DXVECTOR3 Dir = D3DXVECTOR3(1.0f, -1.0f, 1.0f);
	D3DXVec3Normalize(&Dir, &Dir);
	DirLight.Direction = Dir;
	
	g_pD3DDevice->SetLight(0, &DirLight);
	g_pD3DDevice->LightEnable(0, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

void cMainGame::Update()
{
	m_pCamera->Update();
// 
// 	if(GetKeyState(VK_SPACE) & 0x8000)
// 	{
// 		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
// 	}
// 	else
// 	{
// 		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
// 	}
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(
		0,
		0,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(128,128,128),
		1.0f,
		0);
	
	g_pD3DDevice->BeginScene();

	m_pGrid->Render();

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pBox->Render(m_pCamera);

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(0,0,0,0);
}

bool cMainGame::MsgProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	if(m_pCamera && m_pCamera->MsgProc(hWnd, message, wParam, lParam))
		return true;

	switch (message)
	{
		
	case WM_MOUSEHWHEEL:
		{
			HIWORD(wParam); // 얼마나 회전 했는지..
			// > 0 위쪽
			// < 0 아래쪽
		}
		break;
	case WM_KEYDOWN:
		{
			switch(wParam)
			{
			case VK_UP:
				// TODO : 어떤 처리	
				return true;
			}
		}
		break;
	}
	return false;
}


