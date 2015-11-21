#pragma once
class cNode
{
public:
	cNode(void);
	~cNode(void);

	enum eNodeType
	{
		E_NONE,
		E_EMPTY,
		E_WALL,
		E_START,
		E_DEST,
		E_CLOSE,
		E_OPEN,
		E_PATH,
	};

	float		m_fF;
	float		m_fG;
	float		m_fH;
	cNode*		m_pParent;
	int			m_nRow;
	int			m_nCol;
	eNodeType	m_eNodeType;
	RECT		m_rc;
	bool		m_isClosed;
	int			m_nIndexAtHeap;

	void Setup(int nIndex, eNodeType e);

	void Render(HDC hdc);
};

