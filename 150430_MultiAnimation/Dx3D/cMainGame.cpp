#include "StdAfx.h"
#include "cMainGame.h"
#include "cGrid.h"
#include "cCamera.h"
#include "cSkinnedMesh.h"

cMainGame::cMainGame(void)
	: m_pGrid(NULL)
	, m_pCamera(NULL)
{
}


cMainGame::~cMainGame(void)
{
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pCamera);

	for each(auto p in m_vecSkinnedMesh)
	{
		SAFE_DELETE(p);
	}

	g_pTextureManager->Destroy();

	g_pSkinnedMeshManager->Destroy();

	cDeviceManager::GetInstance()->Destroy();
}

void cMainGame::Setup()
{
	for (int x = -10; x <= 10; ++x)
	{
		for (int z = -10; z <= 10; ++z)
		{
			cSkinnedMesh* pSkinnedMesh = new cSkinnedMesh("Zealot/", "zealot.X");
			pSkinnedMesh->SetPosition(D3DXVECTOR3(x, 0, z));
			pSkinnedMesh->SetAnimationIndex(rand() % 5);
			pSkinnedMesh->SetRandomTrackPosition();
			m_vecSkinnedMesh.push_back(pSkinnedMesh);
		}
	}
	

	m_pGrid = new cGrid;
	m_pGrid->Setup();

	m_pCamera = new cCamera;
	m_pCamera->Setup();

	SetLight();
}

void cMainGame::Update()
{
	g_pTimeManager->Update();

	if(m_pCamera)
		m_pCamera->Update();

	//if(m_pSkinnedMesh)
	//	m_pSkinnedMesh->Update();
	//m_pSkinnedMesh->Update();
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(47, 121, 112),
		//D3DCOLOR_XRGB(0, 0, 255),
		1.0f, 0);

	g_pD3DDevice->BeginScene();

	// 그림을 그린다.
	m_pGrid->Render();
// 
// 	D3DXMATRIXA16 matWorld;
// 	D3DXMatrixIdentity(&matWorld);
	
	for each(auto p in m_vecSkinnedMesh)
	{
		p->UpdateAndRender();
	}
	
	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	if(m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);
	switch (message)
	{
	case WM_LBUTTONDOWN:
		{
// 			static int nIndex = 0;
// 			m_pSkinnedMesh->SetAnimationIndex(nIndex);
// 			++nIndex;
		}
		break;
	}
}

void cMainGame::SetLight()
{
	D3DXVECTOR3 vDir(1, -1, 1);
	D3DXVec3Normalize(&vDir, &vDir);

	D3DLIGHT9 stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));
	stLight.Type = D3DLIGHT_DIRECTIONAL;
	stLight.Direction = vDir;
	stLight.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	stLight.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	stLight.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);

	g_pD3DDevice->SetLight(0, &stLight);
	g_pD3DDevice->LightEnable(0, true);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
}

