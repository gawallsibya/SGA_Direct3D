#include "StdAfx.h"
#include "cMainGame.h"
#include "cGrid.h"
#include "cCamera.h"
#include "cSkinnedMesh.h"
#include "cCube.h"

cMainGame::cMainGame(void)
	: m_pGrid(NULL)
	, m_pCamera(NULL)
	, m_pSkinnedMesh(NULL)
	, m_pStringMesh(NULL)
	, m_pCube(NULL)
{
}


cMainGame::~cMainGame(void)
{
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pSkinnedMesh);
	SAFE_DELETE(m_pCube);

	SAFE_RELEASE(m_pStringMesh);

	g_pTextureManager->Destroy();

	g_pSkinnedMeshManager->Destroy();

	cDeviceManager::GetInstance()->Destroy();
}

void cMainGame::Setup()
{
	m_pGrid = new cGrid;
	m_pGrid->Setup();

	m_pCamera = new cCamera;
	m_pCamera->Setup();

	m_pCube = new cCube;
	m_pCube->Setup();

	m_pSkinnedMesh = new cSkinnedMesh("Zealot/", "zealot.X");


	// Get a handle to a device context
	HDC hdc = CreateCompatibleDC(NULL);

	// Describe the font we want.

	LOGFONT lf;
	ZeroMemory(&lf, sizeof(LOGFONT));

	lf.lfHeight         = 6;    // in logical units
	lf.lfWidth          = 3;    // in logical units
	lf.lfEscapement     = 0;        
	lf.lfOrientation    = 0;     
	lf.lfWeight         = 500;   // boldness, range 0(light) - 1000(bold)
	lf.lfItalic         = FALSE;   
	lf.lfUnderline      = FALSE;    
	lf.lfStrikeOut      = FALSE;    
	lf.lfCharSet        = DEFAULT_CHARSET;
	lf.lfOutPrecision   = 0;              
	lf.lfClipPrecision  = 0;          
	lf.lfQuality        = 0;           
	lf.lfPitchAndFamily = 0;   

	strcpy(lf.lfFaceName, "굴림체"); // font style

	// Create the font and select it with the device context.
	HFONT hFont = CreateFontIndirect(&lf);
	HFONT hFontOld = (HFONT)SelectObject(hdc, hFont); 

	// Create the text mesh based on the selected font in the HDC.
	D3DXCreateTextW(g_pD3DDevice, hdc, L"조원석", 0.001f, 0.001f, &m_pStringMesh, NULL, NULL);    

	// Restore the old font and free the acquired HDC.    
	SelectObject(hdc, hFontOld);
	DeleteObject(hFont);
	DeleteDC(hdc);



	if(ST_PN_VERTEX::FVF == m_pStringMesh->GetFVF())
	{
		LPDIRECT3DVERTEXBUFFER9 pVB; 
		m_pStringMesh->GetVertexBuffer(&pVB); 

		DWORD dwNumVertices = m_pStringMesh->GetNumVertices();

		VOID* pVertices; 
		pVB->Lock(0, sizeof(ST_PN_VERTEX) * dwNumVertices, (void**)&pVertices, 0); 

		D3DXVECTOR3 vMin, vMax;
		D3DXComputeBoundingBox((D3DXVECTOR3*)pVertices,
			dwNumVertices, 
			D3DXGetFVFVertexSize(ST_PN_VERTEX::FVF),
			&vMin,
			&vMax);
		float fCenterX = (vMin.x + vMax.x) / 2.0f;
		ST_PN_VERTEX* pVertex = (ST_PN_VERTEX*)pVertices; 

		for(DWORD i = 0; i < dwNumVertices; ++i) 
		{ 
			pVertex[i].p.x -= fCenterX; 
		}

		pVB->Unlock(); 
		SAFE_RELEASE(pVB);
	}



	SetLight();
}

void cMainGame::Update()
{
	g_pTimeManager->Update();

	if(m_pCamera)
		m_pCamera->Update();
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

	if(m_pGrid)
		m_pGrid->Render();
	
	if(m_pCube)
		m_pCube->Render();

// 	if(m_pSkinnedMesh)
// 		m_pSkinnedMesh->UpdateAndRender();
// 	
// 	D3DXMATRIXA16 mView, mInvView;
// 	g_pD3DDevice->GetTransform(D3DTS_VIEW, &mView);
// 	mView._41 = 0;
// 	mView._42 = 0;
// 	mView._43 = 0;
// 
// 	D3DXMatrixInverse(&mInvView, 0, &mView);
// 	mInvView._41 = 0;
// 	mInvView._42 = 1;
// 	mInvView._43 = 0;
// 
// 	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mInvView);
// 
// 	m_pStringMesh->DrawSubset(0);

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

