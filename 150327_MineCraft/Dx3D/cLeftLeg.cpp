#include "StdAfx.h"
#include "cLeftLeg.h"


cLeftLeg::cLeftLeg(void)
{
}


cLeftLeg::~cLeftLeg(void)
{
}

void cLeftLeg::Setup()
{
	ST_PT_VERTEX v;
	//왼발
	//정면
	v.p = D3DXVECTOR3(0.0f, -3, -0.5f); v.t = D3DXVECTOR2(0.0625f, 1.0f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.0f,  0, -0.5f); v.t = D3DXVECTOR2(0.0625f, 0.625f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, -3, -0.5f); v.t = D3DXVECTOR2(0.125f, 1.0f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.0f,  0, -0.5f); v.t = D3DXVECTOR2(0.0625f, 0.625f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f,  0, -0.5f); v.t = D3DXVECTOR2(0.125f, 0.625f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, -3, -0.5f); v.t = D3DXVECTOR2(0.125f, 1.0f); m_vecVertex.push_back(v);
	//왼쪽				   			 							    
	v.p = D3DXVECTOR3(0.0f, -3, 0.5f); v.t = D3DXVECTOR2(0.0f, 1.0f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.0f,  0, 0.5f); v.t = D3DXVECTOR2(0.0f, 0.625f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.0f, -3, -0.5f); v.t = D3DXVECTOR2(0.0625f, 1.0f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.0f,  0, 0.5f); v.t = D3DXVECTOR2(0.0f, 0.625f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.0f,  0, -0.5f); v.t = D3DXVECTOR2(0.0625f, 0.625f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.0f, -3, -0.5f); v.t = D3DXVECTOR2(0.0625f, 1.0f); m_vecVertex.push_back(v);
	//오른쪽				   			 							    
	v.p = D3DXVECTOR3(1.0f, -3, -0.5f); v.t = D3DXVECTOR2(0.125f, 1.0f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f,  0, -0.5f); v.t = D3DXVECTOR2(0.125f, 0.625f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, -3, 0.5f); v.t = D3DXVECTOR2(0.1875f, 1.0f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f,  0, -0.5f); v.t = D3DXVECTOR2(0.125f, 0.625f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f,  0, 0.5f); v.t = D3DXVECTOR2(0.1875f, 0.625f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, -3, 0.5f); v.t = D3DXVECTOR2(0.1875f, 1.0f); m_vecVertex.push_back(v);
	//뒤				   			 								    
	v.p = D3DXVECTOR3(1.0f, -3, 0.5f); v.t = D3DXVECTOR2(0.1875f, 1.0f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f,  0, 0.5f); v.t = D3DXVECTOR2(0.1875f, 0.625f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.0f, -3, 0.5f); v.t = D3DXVECTOR2(0.25f, 1.0f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f,  0, 0.5f); v.t = D3DXVECTOR2(0.1875f, 0.625f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.0f,  0, 0.5f); v.t = D3DXVECTOR2(0.25f, 0.625f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.0f, -3, 0.5f); v.t = D3DXVECTOR2(0.25f, 1.0f); m_vecVertex.push_back(v);
	//위				   			  
	v.p = D3DXVECTOR3(0.0f,  0, -0.5f); v.t = D3DXVECTOR2(0.0625f, 0.5625f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.0f,  0, 0.5f); v.t = D3DXVECTOR2(0.0625f, 0.5f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f,  0, -0.5f); v.t = D3DXVECTOR2(0.125f, 0.5625f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.0f,  0, 0.5f); v.t = D3DXVECTOR2(0.0625f, 0.5f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f,  0, 0.5f); v.t = D3DXVECTOR2(0.125f, 0.5f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f,  0, -0.5f); v.t = D3DXVECTOR2(0.125f, 0.5625f); m_vecVertex.push_back(v);
	//아래				   			  
	v.p = D3DXVECTOR3(0.0f, -3, 0.5f); v.t = D3DXVECTOR2(0.125f, 0.5625f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.0f, -3, -0.5f); v.t = D3DXVECTOR2(0.125f, 0.5f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, -3, 0.5f); v.t = D3DXVECTOR2(0.1875f, 0.5625f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.0f, -3, -0.5f); v.t = D3DXVECTOR2(0.125f, 0.5f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, -3, -0.5f); v.t = D3DXVECTOR2(0.1875f, 0.5f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, -3, 0.5f); v.t = D3DXVECTOR2(0.1875f, 0.5625f); m_vecVertex.push_back(v);

}

void cLeftLeg::Update( D3DXMATRIXA16* pParent )
{
	if(m_fRotX > D3DX_PI / 4.0f)
	{
		m_fRotX = D3DX_PI / 4.0f;
		m_fRotXSpeed *= -1;
	}
	if(m_fRotX < -D3DX_PI / 4.0f)
	{
		m_fRotX = -D3DX_PI / 4.0f;
		m_fRotXSpeed *= -1;
	}

	m_fRotX += m_fRotXSpeed;
	D3DXMATRIXA16 matR, matT;
	D3DXMatrixRotationX(&matR, m_fRotX);
	D3DXMatrixTranslation(&matT, 0.0f, -1.5f, 0.0f);
	m_matLocal = matR * matT;
	m_matWorld = m_matLocal * (*pParent);
}
