#pragma once

#include "cNode.h"
#include "cHeap.h"

class cMainGame
{
private:
	enum 
	{
		E_LEFT	= 1 << 0,	//00000001
		E_RIGHT	= 1 << 1,	//00000010
		E_UP	= 1 << 2,	//00000100
		E_DOWN	= 1 << 3,	//00001000
	};

	typedef int eDirection ;


	std::vector<cNode*>			m_vecNode;
	std::set<cNode*>			m_setOpenList;
	cHeap*						m_pHeap;
	std::set<cNode*>			m_setCloseList;
	std::vector<eDirection>		m_vecDirection;
	std::map<eDirection, float> m_mapDistance;

public:
	cMainGame(void);
	~cMainGame(void);

	void	Setup(HWND hWnd);
	void	Render(HDC hdc);
	void	FindPath();
	cNode*	FindNode(cNode::eNodeType e);
	float	CalcHeuristic(cNode* pNode1, cNode* pNode2);
	void	Extend(cNode* pCurrNode, cNode* pDestNode);
	cNode*	GetAdjNode(cNode* pCurrNode, eDirection d);
	bool	IsInList(cNode* pNode, std::set<cNode*>& setNodeList);
	void	MarkNodeType(cNode* pDestNode);
};

