#pragma once

class cSkinnedMesh
{
private:
	D3DXFRAME*	m_pRoot;

public:
	cSkinnedMesh(void);
	~cSkinnedMesh(void);

	void Setup(char* szFolder, char* szFile);
	void Update();
	void Render();
};

