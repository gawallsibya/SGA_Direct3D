#include "StdAfx.h"
#include "cUIObject.h"


cUIObject::cUIObject(void)
	: m_vLocalPos(0, 0, 0)
	, m_vWorldPos(0, 0, 0)
	, m_isVisible(false)
{
}


cUIObject::~cUIObject(void)
{
}

void cUIObject::Update( D3DXVECTOR3* pvParentWorld )
{
	m_vWorldPos = m_vLocalPos;
	if(pvParentWorld)
	{
		m_vWorldPos += (*pvParentWorld);
	}

	for each(auto p in m_setChild)
	{
		p->Update(&m_vWorldPos);
	}
}

void cUIObject::Render(LPD3DXSPRITE pSprite)
{
	for each(auto p in m_setChild)
	{
		p->Render(pSprite);
	}
}

void cUIObject::AddChild( cUIObject* pChild )
{
	m_setChild.insert(pChild);
}

void cUIObject::Destroy()
{
	for each(auto p in m_setChild)
	{
		p->Destroy();
	}

	this->Release();
}

void cUIObject::SetVisible( bool isVisible )
{
	m_isVisible = isVisible;
	for each(auto p in m_setChild)
	{
		p->SetVisible(isVisible);
	}
}

void cUIObject::SetPosition( D3DXVECTOR3& vPosition )
{
	m_vLocalPos = vPosition;
}

cUIObject* cUIObject::FindByTag( int nTag )
{
	if (m_nTag == nTag)
		return this;
	for each(auto p in m_setChild)
	{
		cUIObject* pChild = p->FindByTag(nTag);
		if(pChild)
			return pChild;
	}
	return NULL;
}
