#include "StdAfx.h"
#include "cMainGame.h"
#include "cCube.h"
#include "cGrid.h"
#include "cCamera.h"

cMainGame::cMainGame(void)
	: m_pCamera(NULL)
	, m_pCube(NULL)
	, m_pGrid(NULL)
	, m_pTexture(NULL)
{
}

cMainGame::~cMainGame(void)
{
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pCube);
	SAFE_DELETE(m_pGrid);

	SAFE_RELEASE(m_pTexture);

	g_pDeviceManager->Destroy();
}

void cMainGame::Setup()
{
	m_pCube = new cCube;
	m_pCube->Setup();

	m_pCamera = new cCamera;
	m_pCamera->Setup(&(m_pCube->GetPosition()));

	m_pGrid = new cGrid;
	m_pGrid->Setup(15, 1.0f);

	D3DXCreateTextureFromFile(g_pD3DDevice, "texture.png", &m_pTexture);

	m_aVertex[0].p = D3DXVECTOR3(2, 0, 0);
	m_aVertex[0].t = D3DXVECTOR2(0, 1);

	m_aVertex[1].p = D3DXVECTOR3(2, 2, 0);
	m_aVertex[1].t = D3DXVECTOR2(0, 0);

	m_aVertex[2].p = D3DXVECTOR3(4, 0, 0);
	m_aVertex[2].t = D3DXVECTOR2(1, 1);
}

void cMainGame::Update()
{
	if(m_pCube)
		m_pCube->Update();

	if(m_pCamera)
		m_pCamera->Update();

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
	m_pCube->Render();


	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetFVF(ST_PT_VERTEX::FVF);
	g_pD3DDevice->SetTexture(0, m_pTexture);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		1, 
		m_aVertex,
		sizeof(ST_PT_VERTEX));

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	if(m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);
}
