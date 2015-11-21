#pragma once

#include "cMtlTex.h"

class cFrame
{
	friend class cAseLoader;
protected:
	D3DXMATRIXA16				m_matWorld;
	D3DXMATRIXA16				m_matLocal;
	std::vector<cFrame*>		m_vecChild;
	LPDIRECT3DVERTEXBUFFER9		m_pVB;
	int							m_nNumTri;
	std::vector<ST_POS_SAMPLE>	m_vecPosTrack;
	std::vector<ST_ROT_SAMPLE>	m_vecRotTrack;

	SYNTHESIZE(std::string, m_sFrameName, FrameName);
	SYNTHESIZE_ADD_REF(cMtlTex*, m_pMtlTex, MtlTex);
	
public:
	cFrame(void);
	virtual ~cFrame(void);

	virtual void Setup();
	virtual void Update(D3DXMATRIXA16* pParent, int nKey);
	virtual void Render();
	virtual void AddChild(cFrame* pFrame);
	virtual void Destroy();
	virtual void BuildVB(std::vector<ST_PNT_VERTEX>& vecVertex);
	virtual void SetOriginLocalTM(D3DXMATRIXA16* pParent);

private:
	virtual void CalcLocalTranslation(D3DXMATRIXA16& matT, int nKey);
	virtual void CalcLocalRotation(D3DXMATRIXA16& matR, int nKey);
};

