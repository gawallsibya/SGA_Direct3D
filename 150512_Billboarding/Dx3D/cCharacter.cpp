#include "StdAfx.h"
#include "cCharacter.h"
#include "cHeightMap.h"

cCharacter::cCharacter(void)
	: m_vDirection(0, 0, -1)
	, m_vPosition(0, 0, 0)
	, m_fAngle(0.0f)
	, m_pStringMesh(NULL)
{
	D3DXMatrixIdentity(&m_matWorld);


	// Get a handle to a device context
	HDC hdc = CreateCompatibleDC(NULL);

	// Describe the font we want.

	LOGFONT lf;
	ZeroMemory(&lf, sizeof(LOGFONT));

	lf.lfHeight         = 2;    // in logical units
	lf.lfWidth          = 1;    // in logical units
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

	strcpy(lf.lfFaceName, "±¼¸²Ã¼"); // font style

	// Create the font and select it with the device context.
	HFONT hFont = CreateFontIndirect(&lf);
	HFONT hFontOld = (HFONT)SelectObject(hdc, hFont); 

	// Create the text mesh based on the selected font in the HDC.
	D3DXCreateTextW(g_pD3DDevice,
		hdc, 
		L"±èÈ¿»ó",
		0.001f, 
		0.001f, 
		&m_pStringMesh,
		NULL,
		NULL);    

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

		D3DXMATRIXA16 matS;
		D3DXMatrixScaling(&matS, 0.5f, 0.5f, 0.5f);
		for(DWORD i = 0; i < dwNumVertices; ++i) 
		{ 
			D3DXVec3TransformCoord(&pVertex[i].p, &pVertex[i].p, &matS);
		}


		pVB->Unlock(); 
		SAFE_RELEASE(pVB);
	}

	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));

	m_stMtl.Ambient = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f);
	m_stMtl.Diffuse = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f);
	m_stMtl.Specular = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f);
}


cCharacter::~cCharacter(void)
{
	SAFE_RELEASE(m_pStringMesh);
}

void cCharacter::Update(cHeightMap* pMap)
{
	m_vDirection = D3DXVECTOR3(0, 0, -1);

	D3DXMATRIXA16 matR;
	D3DXMatrixRotationY(&matR, m_fAngle);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);

	if (GetKeyState('W') & 0x8000)
	{
		m_vPosition += (m_vDirection * 0.05f);
	}

	if (GetKeyState('S') & 0x8000)
	{
		m_vPosition -= (m_vDirection * 0.05f);
	}

	if (GetKeyState('A') & 0x8000)
	{
		m_fAngle -= 0.05f;
	}

	if (GetKeyState('D') & 0x8000)
	{
		m_fAngle += 0.05f;
	}

	if(pMap)
	{
		pMap->GetHeight(m_vPosition.x, m_vPosition.y, m_vPosition.z);
	}
	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matR * matT;
}

void cCharacter::Render()
{
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetTexture(0, 0);
	g_pD3DDevice->SetMaterial(&m_stMtl);


	D3DXMATRIXA16 mView, mInvView;
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &mView);
	
// 	/*mView._11 = 1;*/ mView._12 = 0; /*mView._13 = 1;*/ mView._14 = 0;
// 	mView._21 = 0; mView._22 = 1; mView._23 = 0; mView._24 = 0;
// 	/*mView._31 = 1;*/ mView._32 = 0; /*mView._33 = 1;*/ mView._34 = 0;

	mView._41 = 0;
	mView._42 = 0;
	mView._43 = 0;

	D3DXMatrixInverse(&mInvView, 0, &mView);
	mInvView._41 = m_matWorld._41;
	mInvView._42 = m_matWorld._42 + 1.3f;
	mInvView._43 = m_matWorld._43;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mInvView);

	m_pStringMesh->DrawSubset(0);
}

void cCharacter::GetWorldMatrix( D3DXMATRIXA16* pmatWorld )
{
	*pmatWorld = m_matWorld;
}
