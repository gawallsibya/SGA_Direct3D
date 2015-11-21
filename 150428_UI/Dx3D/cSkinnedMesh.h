#pragma once

struct ST_BONE;

class cSkinnedMesh
{
private:
	D3DXFRAME*					m_pRoot;
	LPD3DXANIMATIONCONTROLLER	m_pAnimController;
	float						m_fBlendTime;
	float						m_fPassedBlendTime;
	bool						m_isAnimBlending;

public:
	cSkinnedMesh(void);
	~cSkinnedMesh(void);

	void Setup(char* szFolder, char* szFile);
	void Update();
	void Render();

	void SetupBoneMatrixPtrs(ST_BONE* pBone);
	void UpdateSkinnedMesh(ST_BONE* pBone);
	void SetAnimationIndex(int n);
	void SetAnimationIndexBlend(int n);
};

