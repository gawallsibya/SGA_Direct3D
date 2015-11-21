#include "StdAfx.h"
#include "cObject.h"


cObject::cObject(void)
	: m_nRefCount(1)
	, m_nTag(0)
{
}


cObject::~cObject(void)
{
}
