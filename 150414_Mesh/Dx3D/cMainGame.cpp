#include "StdAfx.h"
#include "cMainGame.h"
#include "cCube.h"
#include "cGrid.h"
#include "cCamera.h"
#include "cObjLoader.h"
#include "cGroup.h"
#include "cAseLoader.h"
#include "cFrame.h"
#include "cMtlTex.h"

cMainGame::cMainGame(void)
	: m_pCamera(NULL)
	, m_pGrid(NULL)
	, m_pFont(NULL)
	, m_pRoot(NULL)
	, m_pMesh(NULL)
	, m_pGroupHead(NULL)
	, m_pSphere(NULL)
{
}

cMainGame::~cMainGame(void)
{
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pGrid);

	SAFE_RELEASE(m_pFont);
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pSphere);

	for (size_t i = 0; i < m_vecMtlTex.size(); ++i)
	{
		SAFE_RELEASE(m_vecMtlTex[i]);
	}
	m_vecMtlTex.clear();

	m_pRoot->Destroy();

	m_pGroupHead->Destroy();

	g_pTextureManager->Destroy();

	g_pDeviceManager->Destroy();
}

void cMainGame::Setup()
{
 	cObjLoader l;
 	m_pGroupHead = l.Load("./obj/Map.obj");

	m_pMesh = l.LoadMesh("./obj/Map.obj", m_vecMtlTex);

	D3DXCreateSphere(g_pD3DDevice, 2, 10, 10, &m_pSphere, NULL);
	//D3DXCreateBox(g_pD3DDevice, 2, 2, 2, &m_pSphere, NULL);
	//D3DXCreateTeapot(g_pD3DDevice, &m_pSphere, NULL);

	cAseLoader loader;
	m_pRoot = loader.Load("woman/woman_01_all.ASE");

	//폰트 생성
	D3DXFONT_DESC fd;
	ZeroMemory(&fd,sizeof(D3DXFONT_DESC));
	fd.Height			= 45;
	fd.Width			= 28;
	fd.Weight			= FW_MEDIUM;
	fd.Italic			= false;
	fd.CharSet			= DEFAULT_CHARSET;
	fd.OutputPrecision  = OUT_DEFAULT_PRECIS;
	fd.PitchAndFamily   = FF_DONTCARE;
	//strcpy_s(fd.FaceName, "궁서체");	//글꼴 스타일
	AddFontResource("umberto.ttf");
	strcpy(fd.FaceName, "umberto");

	D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_pFont);

	m_pCamera = new cCamera;
	m_pCamera->Setup(NULL);

	m_pGrid = new cGrid;
	m_pGrid->Setup(15, 1.0f);
	
	SetLight();
}

void cMainGame::Update()
{
	if(m_pCamera)
		m_pCamera->Update();

	int nKey = GetTickCount() % (3200 - 640) + 640;
	if(m_pRoot)
		m_pRoot->Update(NULL, nKey);

	// 조명을 끈다.
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
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

	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
 	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	//m_pCube->Render();

	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_pSphere->DrawSubset(0);
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	m_pRoot->Render();

// 	DWORD dwStart, dwFinish, dwGroup, dwMesh;
// 
// 	D3DXMatrixIdentity(&matWorld);
// 	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
// 
// 	dwStart = GetTickCount();
// 	for (int k = 0; k < 1000; ++k)
// 		m_pGroupHead->Render();
// 
// 	dwFinish = GetTickCount();
// 	dwGroup = dwFinish - dwStart;
// 	dwStart = dwFinish;
// 
// 	for (int k = 0; k < 1000; ++k)
// 		for (size_t i = 0; i < m_vecMtlTex.size(); ++i)
// 		{
// 			g_pD3DDevice->SetTexture(0, m_vecMtlTex[i]->GetTexture());
// 			g_pD3DDevice->SetMaterial(&m_vecMtlTex[i]->GetMaterial());
// 			m_pMesh->DrawSubset(i);
// 		}
// 	
// 	dwFinish = GetTickCount();
// 	dwMesh = dwFinish - dwStart;

	if(m_pFont)
	{
		RECT rc;
		SetRect(&rc, 100, 100, 101, 101);
		char szTemp[1024] = "ABC 123 ?!";
		//sprintf(szTemp, "%f", dwGroup / (float)dwMesh);
		m_pFont->DrawTextA(NULL,
			szTemp,
			strlen(szTemp),
			&rc,
			DT_LEFT | DT_TOP | DT_NOCLIP,
			D3DCOLOR_XRGB(255, 255, 0));
	}

// 	D3DXMatrixIdentity(&matWorld);
// 	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
// 	g_pD3DDevice->SetFVF(ST_PT_VERTEX::FVF);
// 	g_pD3DDevice->SetTexture(0, m_pTexture);
// 	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
// 		1, 
// 		m_aVertex,
// 		sizeof(ST_PT_VERTEX));

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	if(m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);
}

void cMainGame::SetLight()
{
	D3DLIGHT9 stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));
	stLight.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	stLight.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	stLight.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	stLight.Type = D3DLIGHT_DIRECTIONAL;

	D3DXVECTOR3 vDir(0.7f, -1, 1);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;
	g_pD3DDevice->SetLight(0, &stLight);
	g_pD3DDevice->LightEnable(0, true);
	g_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	//g_pD3DDevice->SetRenderState(D3DRS_SPECULARENABLE, true);
}
