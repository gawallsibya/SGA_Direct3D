#include "StdAfx.h"
#include "cAseCharacter.h"
#include "cAseLoader.h"
#include "cFrame.h"
#include "cMtlTex.h"

cAseCharacter::cAseCharacter(void)
	: m_pRoot(NULL)
{
}


cAseCharacter::~cAseCharacter(void)
{
	m_pRoot->Destroy();
}

void cAseCharacter::Setup()
{
	cAseLoader loader;
	m_pRoot = loader.Load("woman/woman_01_all.ASE");

}

void cAseCharacter::Update()
{
	if(m_pRoot)
	{
		//D3DXMatrixTranslation(*m_matWorld, m_vPosition.x, m_vPosition.y, m_vPosition.z);
		m_pRoot->Update(&m_matWorld);
	}
	cCharacter::Update();
}

void cAseCharacter::Render()
{
	if(m_pRoot)
		m_pRoot->Render();
}
