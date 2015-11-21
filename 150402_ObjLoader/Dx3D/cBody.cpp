#include "StdAfx.h"
#include "cBody.h"


cBody::cBody(void)
	: m_pCharacter(NULL)
{
}


cBody::~cBody(void)
{
	SAFE_DELETE(m_pCharacter);
}

void cBody::Setup()
{
	m_pCharacter = new cCharacter;
	m_pCharacter->Setup();

	ST_PNT_VERTEX v;

	//몸통
	//정면
	v.p = D3DXVECTOR3(-1.0f, -1.5f, -0.5f); v.t = D3DXVECTOR2(0.3125f,   1.0f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0f,  1.5f, -0.5f); v.t = D3DXVECTOR2(0.3125f, 0.625f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1.0f, -1.5f, -0.5f); v.t = D3DXVECTOR2(0.4375f,   1.0f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0f,  1.5f, -0.5f); v.t = D3DXVECTOR2(0.3125f, 0.625f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1.0f,  1.5f, -0.5f); v.t = D3DXVECTOR2(0.4375f, 0.625f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1.0f, -1.5f, -0.5f); v.t = D3DXVECTOR2(0.4375f,   1.0f); m_vecVertex.push_back(v);
	//왼쪽				   			 							    
	v.p = D3DXVECTOR3(-1.0f, -1.5f,  0.5f); v.t = D3DXVECTOR2(  0.25f,   1.0f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0f,  1.5f,  0.5f); v.t = D3DXVECTOR2(  0.25f, 0.625f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0f, -1.5f, -0.5f); v.t = D3DXVECTOR2(0.3125f,   1.0f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0f,  1.5f,  0.5f); v.t = D3DXVECTOR2(  0.25f, 0.625f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0f,  1.5f, -0.5f); v.t = D3DXVECTOR2(0.3125f, 0.625f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0f, -1.5f, -0.5f); v.t = D3DXVECTOR2(0.3125f,   1.0f); m_vecVertex.push_back(v);
	//오른쪽				   			 							    
	v.p = D3DXVECTOR3( 1.0f, -1.5f, -0.5f); v.t = D3DXVECTOR2(0.4375f,   1.0f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1.0f,  1.5f, -0.5f); v.t = D3DXVECTOR2(0.4375f, 0.625f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1.0f, -1.5f,  0.5f); v.t = D3DXVECTOR2(   0.5f,   1.0f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1.0f,  1.5f, -0.5f); v.t = D3DXVECTOR2(0.4375f, 0.625f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1.0f,  1.5f,  0.5f); v.t = D3DXVECTOR2(   0.5f, 0.625f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1.0f, -1.5f,  0.5f); v.t = D3DXVECTOR2(   0.5f,   1.0f); m_vecVertex.push_back(v);
	//뒤				   			 								    
	v.p = D3DXVECTOR3( 1.0f, -1.5f,  0.5f); v.t = D3DXVECTOR2(   0.5f,   1.0f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1.0f,  1.5f,  0.5f); v.t = D3DXVECTOR2(   0.5f, 0.625f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0f, -1.5f,  0.5f); v.t = D3DXVECTOR2( 0.625f,   1.0f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1.0f,  1.5f,  0.5f); v.t = D3DXVECTOR2(   0.5f, 0.625f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0f,  1.5f,  0.5f); v.t = D3DXVECTOR2( 0.625f, 0.625f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0f, -1.5f,  0.5f); v.t = D3DXVECTOR2( 0.625f,   1.0f); m_vecVertex.push_back(v);
	//위				   			  
	v.p = D3DXVECTOR3(-1.0f,  1.5f, -0.5f); v.t = D3DXVECTOR2(0.3125f,0.5625f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0f,  1.5f,  0.5f); v.t = D3DXVECTOR2(0.3125f,   0.5f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1.0f,  1.5f, -0.5f); v.t = D3DXVECTOR2(0.4375f,0.5625f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0f,  1.5f,  0.5f); v.t = D3DXVECTOR2(0.3125f,   0.5f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1.0f,  1.5f,  0.5f); v.t = D3DXVECTOR2(0.4375f,   0.5f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1.0f,  1.5f, -0.5f); v.t = D3DXVECTOR2(0.4375f,0.5625f); m_vecVertex.push_back(v);
	//아래				   			  
	v.p = D3DXVECTOR3( 1.0f, -1.5f,  0.5f); v.t = D3DXVECTOR2(0.4375f,0.5625f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0f, -1.5f,  0.5f); v.t = D3DXVECTOR2(0.5625f,0.5625f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1.0f, -1.5f, -0.5f); v.t = D3DXVECTOR2(0.4375f,   0.5f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1.0f, -1.5f, -0.5f); v.t = D3DXVECTOR2(0.4375f,   0.5f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0f, -1.5f,  0.5f); v.t = D3DXVECTOR2(0.5625f,0.5625f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0f, -1.5f, -0.5f); v.t = D3DXVECTOR2(0.5625f,   0.5f); m_vecVertex.push_back(v);
}

void cBody::Update( D3DXMATRIXA16* pParent )
{
	m_pCharacter->Update();

	m_pCharacter->GetWorldMatrix(&m_matWorld);

	for each(auto f in m_vecChild)
	{
		f->Update(&m_matWorld);
	}
}

