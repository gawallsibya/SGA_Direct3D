#include "StdAfx.h"
#include "cMainGame.h"
#include "cCube.h"
#include "cGrid.h"
#include "cCamera.h"
#include "cBody.h"
#include "cLeftArm.h"
#include "cRightArm.h"
#include "cHead.h"
#include "cLeftLeg.h"
#include "cRightLeg.h"

cMainGame::cMainGame(void)
	: m_pCamera(NULL)
	, m_pGrid(NULL)
	, m_pFont(NULL)
{
}

cMainGame::~cMainGame(void)
{
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pGrid);

	SAFE_RELEASE(m_pFont);

	g_pDeviceManager->Destroy();
}

void cMainGame::Setup()
{
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
	LPDIRECT3DTEXTURE9	pTexture = NULL;
	D3DXCreateTextureFromFile(g_pD3DDevice, "Batman.png", &pTexture);

	cBody* pBody = new cBody;
	pBody->Setup();
	pBody->SetTexture(pTexture);
	m_pRoot = pBody;

	cHead* pHead = new cHead;
	pHead->Setup();
	pHead->SetTexture(pTexture);
	m_pRoot->AddChild(pHead);

	cLeftArm* pLeftArm = new cLeftArm;
	pLeftArm->Setup();
	pLeftArm->SetTexture(pTexture);
	m_pRoot->AddChild(pLeftArm);

	cRightArm* pRightArm = new cRightArm;
	pRightArm->Setup();
	pRightArm->SetTexture(pTexture);
	m_pRoot->AddChild(pRightArm);

	cLeftLeg* pLeftLeg = new cLeftLeg;
	pLeftLeg->Setup();
	pLeftLeg->SetTexture(pTexture);
	m_pRoot->AddChild(pLeftLeg);

	cRightLeg* pRightLeg = new cRightLeg;
	pRightLeg->Setup();
	pRightLeg->SetTexture(pTexture);
	m_pRoot->AddChild(pRightLeg);

	SAFE_RELEASE(pTexture);

	SetLight();
}

void cMainGame::Update()
{
	if(m_pCamera)
		m_pCamera->Update();

	if(m_pRoot)
		m_pRoot->Update(NULL);

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
// 	m_pCube->Render();
	m_pRoot->Render();


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

	D3DXVECTOR3 vDir(0.7, -1, 1);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;
	g_pD3DDevice->SetLight(0, &stLight);
	g_pD3DDevice->LightEnable(0, true);
	g_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	g_pD3DDevice->SetRenderState(D3DRS_SPECULARENABLE, true);
}
