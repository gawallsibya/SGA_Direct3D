#pragma once
class cDijkstraNode
{
public:
	enum eNodeState
	{
		E_NORMAL,
		E_SELECTED,
		E_MOUSE_OVER,
		E_PATH,
		E_STATE_CNT
	};

private:
	D3DMATERIAL9 m_stMtl[E_STATE_CNT];

	SYNTHESIZE(int, m_nNodeId, NodeId);
	SYNTHESIZE(int, m_nVia, Via);
	SYNTHESIZE(bool, m_isVisited, Visited);
	SYNTHESIZE(float, m_fCost, Cost);
	SYNTHESIZE(float, m_fRadius, Radius);
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);
	SYNTHESIZE(eNodeState, m_eState, State);
	
public:
	cDijkstraNode(void);
	~cDijkstraNode(void);

	void Render(LPD3DXMESH pSphere);
};

