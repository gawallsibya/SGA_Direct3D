#pragma once

class cGrid;
class cCamera;
//class cFrame;
//class cMtlTex;
//class cGroup;
class cDijkstraNode;
class cSkinnedMesh;
class cFrustum;

class cMainGame
{
private:
	cCamera*						m_pCamera;
	cGrid*							m_pGrid;
	cSkinnedMesh*					m_pSkinnedMesh;
	//cGroup*						m_pGroupHead;
	//cFrame*						m_pRoot;
	LPD3DXFONT						m_pFont;
	//LPD3DXMESH					m_pMesh;
	//std::vector<cMtlTex*>			m_vecMtlTex;
	LPD3DXMESH						m_pTeapot;
	LPD3DXMESH						m_pSphere;
	D3DMATERIAL9					m_stWhiteMtl;
	D3DMATERIAL9					m_stRedMtl;
	D3DXVECTOR3						m_vTeapotPos;
	float							m_fTeapotRadius;
	cDijkstraNode*					m_pPickedNode;
	cDijkstraNode*					m_pStartNode;
	cDijkstraNode*					m_pDestNode;
	std::vector<ST_PC_VERTEX>		m_vecEdge;
	cFrustum*						m_pFrustum;

	std::vector<cDijkstraNode*>		m_vecDijkstraNode;
	std::vector<std::vector<float>> m_vecEdgeCost;
	std::vector<D3DXVECTOR3>		m_vecSpherePosition;

	LPD3DXSPRITE					m_pSprite;
public:
	cMainGame(void);
	~cMainGame(void);

	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	cDijkstraNode* GetPickedNode(int x, int y);
	void ResetAllNode();
	void FindPath();
	cDijkstraNode* GetMinCostNode();
private:
	void SetLight();
};

