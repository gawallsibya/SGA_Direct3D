#pragma once

class cMtlTex;
class cGroup;

class cObjLoader
{
private:
	std::map<std::string, cMtlTex*> m_mapMtlTex;
	cGroup*							m_pHead;
public:
	cObjLoader(void);
	~cObjLoader(void);

	cGroup* Load(char* szFullPath);
	void LoadMtlLib(char* szFullPath);
	LPD3DXMESH LoadMesh(char* szFullPath, std::vector<cMtlTex*>& vecMtlTex);
};

