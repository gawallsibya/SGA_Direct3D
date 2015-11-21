#include "StdAfx.h"
#include "cMainGame.h"

cMainGame::cMainGame(void)
{
}


cMainGame::~cMainGame(void)
{
	for (size_t i = 0; i < m_vecNode.size(); ++i)
	{
		delete m_vecNode[i];
	}
	m_vecNode.clear();
}

void cMainGame::Setup(HWND hWnd)
{
	m_vecDirection.push_back(E_LEFT);
	m_vecDirection.push_back(E_RIGHT);
	m_vecDirection.push_back(E_UP);
	m_vecDirection.push_back(E_DOWN);
	m_vecDirection.push_back(E_LEFT | E_UP);	//00000101
	m_vecDirection.push_back(E_LEFT | E_DOWN);
	m_vecDirection.push_back(E_RIGHT | E_UP);
	m_vecDirection.push_back(E_RIGHT | E_DOWN);

	std::map<char, cNode::eNodeType> mapNodeType;
	mapNodeType['E'] = cNode::E_EMPTY;
	mapNodeType['B'] = cNode::E_WALL;
	mapNodeType['S'] = cNode::E_START;
	mapNodeType['D'] = cNode::E_DEST;

	m_mapDistance[E_LEFT] = 1.0f;
	m_mapDistance[E_RIGHT] = 1.0f;
	m_mapDistance[E_UP] = 1.0f;
	m_mapDistance[E_DOWN] = 1.0f;
	m_mapDistance[E_LEFT | E_UP] = sqrt(2.0f);	//00000101
	m_mapDistance[E_LEFT | E_DOWN] = sqrt(2.0f);
	m_mapDistance[E_RIGHT | E_UP] = sqrt(2.0f);
	m_mapDistance[E_RIGHT | E_DOWN] = sqrt(2.0f);
	FILE* fp;
	fopen_s(&fp, "astar.txt", "r");

	int nIndex = 0;
	while(true)
	{
		char c = fgetc(fp);
		
		if(feof(fp))
			break;
		
		if(c < 33)
			continue;

		cNode* pNode = new cNode;
		pNode->Setup(nIndex, mapNodeType[c]);
		++nIndex;
		m_vecNode.push_back(pNode);
	}

	fclose(fp);

	FindPath();

	InvalidateRect(hWnd, NULL, false);
}

void cMainGame::Render( HDC hdc )
{
	for each(auto p in m_vecNode)
	{
		p->Render(hdc);
	}
}

void cMainGame::FindPath()
{
	cNode* pStartNode = FindNode(cNode::E_START);
	cNode* pDestNode = FindNode(cNode::E_DEST);

	pStartNode->m_fG = 0.0f;
	pStartNode->m_fH = CalcHeuristic(pStartNode, pDestNode);
	pStartNode->m_fF = pStartNode->m_fG + pStartNode->m_fH;

	m_setOpenList.insert(pStartNode);

	while(true)
	{
		cNode* pMinFNode = GetMinFNodeAtOpenList();
		
		if(pMinFNode == NULL)
		{
			// 길 없음.
			MarkNodeType(pDestNode);
			break;
		}

		m_setOpenList.erase(pMinFNode);
		m_setCloseList.insert(pMinFNode);
		
		pMinFNode->m_isClosed = true;

		Extend(pMinFNode, pDestNode);

		if(pMinFNode == pDestNode)
		{
			//  길 찾음
			MarkNodeType(pDestNode);
			break;
		}
	}
}

cNode* cMainGame::FindNode( cNode::eNodeType e )
{
	for each(auto p in m_vecNode)
	{
		if(p->m_eNodeType == e)
			return p;
	}
	return NULL;
}

float cMainGame::CalcHeuristic( cNode* pNode1, cNode* pNode2 )
{
	return fabs(pNode1->m_nRow - (float)pNode2->m_nRow) + 
		fabs(pNode1->m_nCol - (float)pNode2->m_nCol);
}

cNode* cMainGame::GetMinFNodeAtOpenList()
{
	cNode* pMinFNode = NULL;

	for each(auto p in m_setOpenList)
	{
		if(pMinFNode == NULL)
		{
			pMinFNode = p;
			continue;
		}

		if(p->m_fF < pMinFNode->m_fF)
			pMinFNode = p;
	}
	
	return pMinFNode;
}

void cMainGame::Extend( cNode* pCurrNode, cNode* pDestNode )
{
	for each(eDirection d in m_vecDirection)
	{
		cNode* pAdjNode = GetAdjNode(pCurrNode, d);
		
		if(pAdjNode == NULL)
			continue;

		if(IsInList(pAdjNode, m_setOpenList))
		{
			if(pAdjNode->m_fG > pCurrNode->m_fG + m_mapDistance[d])
			{
				pAdjNode->m_fG = pCurrNode->m_fG + m_mapDistance[d];
				pAdjNode->m_fF = pAdjNode->m_fG + pAdjNode->m_fH;
				pAdjNode->m_pParent = pCurrNode;
			}
		}
		else
		{
			pAdjNode->m_fG = pCurrNode->m_fG + m_mapDistance[d];
			pAdjNode->m_fH = CalcHeuristic(pAdjNode, pDestNode);
			pAdjNode->m_fF = pAdjNode->m_fG + pAdjNode->m_fH;
			pAdjNode->m_pParent = pCurrNode;
			m_setOpenList.insert(pAdjNode);
		}
	}
}

cNode* cMainGame::GetAdjNode( cNode* pCurrNode, eDirection d )
{
	//int nIndex = pCurrNode->m_nRow * TILE_N + pCurrNode->m_nCol;
	int nAdjRow = pCurrNode->m_nRow;
	int nAdjCol = pCurrNode->m_nCol;
	
	if(d & E_LEFT)
	{
		if(pCurrNode->m_nCol == 0)
			return NULL;
		int nIndex = pCurrNode->m_nRow * TILE_N + pCurrNode->m_nCol - 1;
		if(m_vecNode[nIndex]->m_eNodeType == cNode::E_WALL)
			return NULL;
		nAdjCol -= 1;
	}
	else if(d & E_RIGHT)
	{
		if(pCurrNode->m_nCol == TILE_N - 1)
			return NULL;
		int nIndex = pCurrNode->m_nRow * TILE_N + pCurrNode->m_nCol + 1;
		if(m_vecNode[nIndex]->m_eNodeType == cNode::E_WALL)
			return NULL;
		nAdjCol += 1;
	}

	if(d & E_UP)
	{
		if(pCurrNode->m_nRow == 0)
			return NULL;
		int nIndex = (pCurrNode->m_nRow - 1) * TILE_N + pCurrNode->m_nCol;
		if(m_vecNode[nIndex]->m_eNodeType == cNode::E_WALL)
			return NULL;
		nAdjRow -= 1;
	}
	else if(d & E_DOWN)
	{
		if(pCurrNode->m_nRow == TILE_N - 1)
			return NULL;
		int nIndex = (pCurrNode->m_nRow + 1) * TILE_N + pCurrNode->m_nCol;
		if(m_vecNode[nIndex]->m_eNodeType == cNode::E_WALL)
			return NULL;
		nAdjRow += 1;
	}

	int nIndex = nAdjRow * TILE_N + nAdjCol;
	if(m_vecNode[nIndex]->m_eNodeType == cNode::E_WALL)
		return NULL;

	if(m_vecNode[nIndex]->m_isClosed)
		return NULL;

	return m_vecNode[nIndex];
}

bool cMainGame::IsInList( cNode* pNode, std::set<cNode*>& setNodeList )
{
	return setNodeList.find(pNode) != setNodeList.end();
}

void cMainGame::MarkNodeType(cNode* pDestNode)
{
	for each(auto p in m_setOpenList)
	{
		p->m_eNodeType = cNode::E_OPEN;
	}

	for each(auto p in m_setCloseList)
	{
		p->m_eNodeType = cNode::E_CLOSE;
	}

	cNode* pTemp = pDestNode;
	while(pTemp)
	{
		pTemp->m_eNodeType = cNode::E_PATH;
		pTemp = pTemp->m_pParent;
	}
}
