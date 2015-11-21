#include "StdAfx.h"
#include "cMainGame.h"
#include "cGrid.h"
#include "cCamera.h"
#include "cSkinnedMesh.h"
#include "cHeightMap.h"

cMainGame::cMainGame(void)
	: m_pGrid(NULL)
	, m_pCamera(NULL)
	, m_pCharacter(NULL)
	, m_pMap(NULL)
{
}


cMainGame::~cMainGame(void)
{
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pCharacter);
	SAFE_DELETE(m_pMap);

	g_pTextureManager->Destroy();

	g_pSkinnedMeshManager->Destroy();

	cDeviceManager::GetInstance()->Destroy();
}

void cMainGame::Setup()
{
// 	m_pMap = new cHeightMap;
// 	m_pMap->Setup("HeightMapData", "HeightMap.raw", "terrain.jpg");

	m_vecVertex1.resize(6);
	m_vecVertex2.resize(6);

	m_vecVertex1[0].p = D3DXVECTOR3(-1, -1, 0);
	m_vecVertex1[0].t = D3DXVECTOR2( 0, 1);
	m_vecVertex1[0].c = D3DCOLOR_ARGB(128, 255, 70, 70);

	m_vecVertex1[1].p = D3DXVECTOR3(-1,  1, 0);
	m_vecVertex1[1].t = D3DXVECTOR2( 0, 0);
	m_vecVertex1[1].c = D3DCOLOR_ARGB(128, 255, 70, 70);

	m_vecVertex1[2].p = D3DXVECTOR3( 1,  1, 0);
	m_vecVertex1[2].t = D3DXVECTOR2( 1, 0);
	m_vecVertex1[2].c = D3DCOLOR_ARGB(128, 255, 70, 70);

	m_vecVertex1[3].p = D3DXVECTOR3(-1, -1, 0);
	m_vecVertex1[3].t = D3DXVECTOR2( 0, 1);
	m_vecVertex1[3].c = D3DCOLOR_ARGB(128, 255, 70, 70);

	m_vecVertex1[4].p = D3DXVECTOR3( 1,  1, 0);
	m_vecVertex1[4].t = D3DXVECTOR2( 1, 0);
	m_vecVertex1[4].c = D3DCOLOR_ARGB(128, 255, 70, 70);

	m_vecVertex1[5].p = D3DXVECTOR3( 1, -1, 0);
	m_vecVertex1[5].t = D3DXVECTOR2( 1, 1);
	m_vecVertex1[5].c = D3DCOLOR_ARGB(128, 255, 70, 70);

	for (size_t i = 0; i < m_vecVertex1.size(); ++i)
	{
		m_vecVertex2[i] = m_vecVertex1[i];
		m_vecVertex2[i].c = D3DCOLOR_ARGB(180, 18, 200, 30);
	}

	// D3DBLENDOP_ADD (기본값)	: src + dest
	// D3DBLENDOP_SUBTRACT		: src - dest
	// D3DBLENDOP_REVSUBTRACT	: dest - src
	// D3DBLENDOP_MIN			: MIN(src, dest)
	// D3DBLENDOP_MAX			: MAX(src, dest)
	g_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
		
	// D3DBLEND_ZERO : (0, 0, 0, 0)
	// D3DBLEND_ONE : (1, 1, 1, 1)
	// D3DBLEND_SRCCOLOR : (rs, gs, bs, as)
	// D3DBLEND_INVSRCCOLOR : (1-rs, 1-gs, 1-bs, 1-as)
	// D3DBLEND_SRCALPHA : (as, as, as, as) (Source Blend 기본값)
	// D3DBLEND_INVSRCALPHA : (1-as, 1-as, 1-as, 1-as) (Destination Blend 기본값)
	// D3DBLEND_DESTALPHA : (ad, ad, ad, ad)
	// D3DBLEND_INVDESTALPHA : (1-ad, 1-ad, 1-ad, 1-ad)
	// D3DBLEND_DESTCOLOR : (rd, gd, bd, ad)
	// D3DBLEND_INVDESTCCOLOR : (1-rd, 1-gd, 1-bd, 1-ad)
	// D3DBLEND_SRCALPHASAT : (f, f, f, 1); f=min(as, 1-ad)
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// Result = Src * D3DBLEND_ONE - Dest * D3DBLEND_ZERO
	cSkinnedMesh* pSkinnedMesh = new cSkinnedMesh("Zealot/", "zealot.X");
	pSkinnedMesh->SetAnimationIndex(3);

	m_pCharacter = pSkinnedMesh;

	m_pGrid = new cGrid;
	m_pGrid->Setup();

	m_pCamera = new cCamera;
	m_pCamera->Setup();
	m_pCamera->SetTarget(&m_pCharacter->GetPosition());
	SetLight();
}

void cMainGame::Update()
{
	g_pTimeManager->Update();

	if(m_pCamera)
		m_pCamera->Update();

	m_pCharacter->Update(m_pMap);
	//if(m_pSkinnedMesh)
	//	m_pSkinnedMesh->Update();
	//m_pSkinnedMesh->Update();
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		//D3DCOLOR_XRGB(47, 121, 112),
		D3DCOLOR_XRGB(0, 0, 0),
		1.0f, 0);

	g_pD3DDevice->BeginScene();

	// 그림을 그린다.
	m_pGrid->Render();

	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	
	// 알파블렌딩 ON.
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetFVF(ST_PCT_VERTEX::FVF);

	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
	
	matWorld._43 = 1;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, &m_vecVertex2[0], sizeof(ST_PCT_VERTEX));

	matWorld._43 = 0;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, &m_vecVertex1[0], sizeof(ST_PCT_VERTEX));

	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);

	// 알파블렌딩 OFF.
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);

	if(m_pMap)
		m_pMap->Render();

	//m_pCharacter->Render();
		
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

