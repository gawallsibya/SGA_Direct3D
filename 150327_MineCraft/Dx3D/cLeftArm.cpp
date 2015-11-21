#include "StdAfx.h"
#include "cLeftArm.h"


cLeftArm::cLeftArm(void)
{
}


cLeftArm::~cLeftArm(void)
{
}

void cLeftArm::Setup()
{
	ST_PT_VERTEX v;
	//¿ÞÆÈ
	//Á¤¸é
	v.p = D3DXVECTOR3(0.0f, -3, -0.5f); v.t = D3DXVECTOR2(0.6875f,   1.0f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.0f,  0, -0.5f); v.t = D3DXVECTOR2(0.6875f, 0.625f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, -3, -0.5f); v.t = D3DXVECTOR2(  0.75f,   1.0f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.0f,  0, -0.5f); v.t = D3DXVECTOR2(0.6875f, 0.625f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f,  0, -0.5f); v.t = D3DXVECTOR2(  0.75f, 0.625f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, -3, -0.5f); v.t = D3DXVECTOR2(  0.75f,   1.0f); m_vecVertex.push_back(v);
	//¿ÞÂÊ				   			 							    
	v.p = D3DXVECTOR3(0.0f, -3,  0.5f); v.t = D3DXVECTOR2( 0.625f,   1.0f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.0f,  0,  0.5f); v.t = D3DXVECTOR2( 0.625f, 0.625f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.0f, -3, -0.5f); v.t = D3DXVECTOR2(0.6875f,   1.0f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.0f,  0,  0.5f); v.t = D3DXVECTOR2( 0.625f, 0.625f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.0f,  0, -0.5f); v.t = D3DXVECTOR2(0.6875f, 0.625f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.0f, -3, -0.5f); v.t = D3DXVECTOR2(0.6875f,   1.0f); m_vecVertex.push_back(v);
	//¿À¸¥ÂÊ				   			 							    
	v.p = D3DXVECTOR3(1.0f, -3, -0.5f); v.t = D3DXVECTOR2(  0.75f,   1.0f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f,  0, -0.5f); v.t = D3DXVECTOR2(  0.75f, 0.625f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, -3,  0.5f); v.t = D3DXVECTOR2(0.8125f,   1.0f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f,  0, -0.5f); v.t = D3DXVECTOR2(  0.75f, 0.625f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f,  0,  0.5f); v.t = D3DXVECTOR2(0.8125f, 0.625f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, -3,  0.5f); v.t = D3DXVECTOR2(0.8125f,   1.0f); m_vecVertex.push_back(v);
	//µÚ				   			 								    
	v.p = D3DXVECTOR3(1.0f, -3,  0.5f); v.t = D3DXVECTOR2(0.8125f,   1.0f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f,  0,  0.5f); v.t = D3DXVECTOR2(0.8125f, 0.625f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.0f, -3,  0.5f); v.t = D3DXVECTOR2( 0.875f,   1.0f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f,  0,  0.5f); v.t = D3DXVECTOR2(0.8125f, 0.625f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.0f,  0,  0.5f); v.t = D3DXVECTOR2( 0.875f, 0.625f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.0f, -3,  0.5f); v.t = D3DXVECTOR2( 0.875f,   1.0f); m_vecVertex.push_back(v);
	//À§				   			  
	v.p = D3DXVECTOR3(0.0f,  0, -0.5f); v.t = D3DXVECTOR2(0.6875f,0.5625f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.0f,  0,  0.5f); v.t = D3DXVECTOR2(0.6875f,   0.5f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f,  0, -0.5f); v.t = D3DXVECTOR2(  0.75f,0.5625f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.0f,  0,  0.5f); v.t = D3DXVECTOR2(0.6875f,   0.5f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f,  0,  0.5f); v.t = D3DXVECTOR2(  0.75f,   0.5f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f,  0, -0.5f); v.t = D3DXVECTOR2(  0.75f,0.5625f); m_vecVertex.push_back(v);
	//¾Æ·¡				   			  
	v.p = D3DXVECTOR3(0.0f, -3,  0.5f); v.t = D3DXVECTOR2(  0.75f,0.5625f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.0f, -3, -0.5f); v.t = D3DXVECTOR2(  0.75f,   0.5f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, -3,  0.5f); v.t = D3DXVECTOR2(0.8125f,0.5625f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.0f, -3, -0.5f); v.t = D3DXVECTOR2(  0.75f,   0.5f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, -3, -0.5f); v.t = D3DXVECTOR2(0.8125f,   0.5f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, -3,  0.5f); v.t = D3DXVECTOR2(0.8125f,0.5625f); m_vecVertex.push_back(v);

}

void cLeftArm::Update( D3DXMATRIXA16* pParent )
{
	D3DXMatrixTranslation(&m_matLocal, 1.0f, 1.5f, 0.0f);
	m_matWorld = m_matLocal * (*pParent);
}