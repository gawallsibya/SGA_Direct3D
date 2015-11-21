#include "StdAfx.h"
#include "cObject.h"


cObject::cObject(void)
	: m_nRefCount(1)
{
	g_pObjectManager->AddObject(this);
}


cObject::~cObject(void)
{
	assert(m_nRefCount == 0 && "�̷��� ����..");
	g_pObjectManager->RemoveObject(this);
}
