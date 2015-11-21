#include "StdAfx.h"
#include "cCharacter.h"


cCharacter::cCharacter(void)
	: m_vDirection(0, 0, 1)
	, m_vPosition(0, 0, 0)
	, m_fAngle(0.0f)
{
	D3DXMatrixIdentity(&m_matWorld);
}


cCharacter::~cCharacter(void)
{
}

void cCharacter::Setup()
{

}

void cCharacter::Update()
{
	m_vDirection = D3DXVECTOR3(0, 0, 1);

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

	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matR * matT;
}

void cCharacter::Render()
{

}
