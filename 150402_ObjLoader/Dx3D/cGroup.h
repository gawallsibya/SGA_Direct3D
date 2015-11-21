#pragma once

#include "cMtlTex.h"

class cGroup
{
	friend class cObjLoader;
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	cGroup*					m_pNext;
	int						m_nNumTri;
	
	SYNTHESIZE_ADD_REF(cMtlTex*, m_pMtlTex, MtlTex);

public:
	cGroup(void);
	~cGroup(void);

	void BuildVertexBuffer(std::vector<ST_PNT_VERTEX>& vecVertex);
	void Render();
	void Destroy();

};

