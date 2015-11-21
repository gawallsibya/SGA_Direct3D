#include "StdAfx.h"
#include "cCube.h"


cCube::cCube(void)
	: m_pEffect(NULL)
{
}

cCube::~cCube(void)
{
	SAFE_RELEASE(m_pEffect);
}

void cCube::Setup()
{
	LoadEffect("shader.fx");

	ST_P_VERTEX v;

	v.p = D3DXVECTOR3(-1, -1, -1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1,  1, -1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1,  1, -1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1, -1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1,  1, -1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1, -1, -1); m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1, -1,  1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1,  1,  1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1,  1,  1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1,  1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1, -1,  1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1,  1,  1); m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1, -1,  1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1,  1,  1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1,  1, -1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1,  1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1,  1, -1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1, -1); m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3( 1, -1, -1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1,  1, -1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1,  1,  1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1, -1, -1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1,  1,  1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1, -1,  1); m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1,  1, -1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1,  1,  1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1,  1,  1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1,  1, -1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1,  1,  1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1,  1, -1); m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1, -1,  1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1, -1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1, -1, -1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1,  1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1, -1, -1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1, -1,  1); m_vecVertex.push_back(v);
}

void cCube::Update()
{

}

void cCube::Render()
{
	D3DXMATRIXA16 matView, matProjection;
	// �� ����� �����.
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);

	// ��������� �����.
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProjection);

	// ��������� �����.
	D3DXMATRIXA16			matWorld;
	D3DXMatrixIdentity(&matWorld);

	// ���̴� ������������ ����
	m_pEffect->SetMatrix("matWorld", &matWorld);
	m_pEffect->SetMatrix("matView",  &matView);
	m_pEffect->SetMatrix("matProjection",  &matProjection);

	g_pD3DDevice->SetFVF(ST_P_VERTEX::FVF);

	// ���̴��� �����Ѵ�.
	UINT numPasses = 0;
	m_pEffect->Begin(&numPasses, NULL);

	for (UINT i = 0; i < numPasses; ++i )
	{
		m_pEffect->BeginPass(i);
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
			m_vecVertex.size() / 3,
			&m_vecVertex[0],
			sizeof(ST_P_VERTEX));
		m_pEffect->EndPass();
	}

	m_pEffect->End();
}

LPD3DXEFFECT cCube::LoadEffect( const char* szFileName )
{
	LPD3DXEFFECT pEffect = NULL;

	// ���̴� �ε�
	LPD3DXBUFFER		pError = NULL;			//���� ���� ( ���̴��� �������Ҷ� �߸� �� �����̳� ���������� �������ִ� ���� )
	DWORD				dwShaderFlag = 0;		//���̴� �÷��� 0 

#ifdef _DEBUG
	dwShaderFlag = dwShaderFlag | D3DXSHADER_DEBUG;		//���̴��� ����׸��� �������ϰڴ� ( ����׸��� �ؾ� �߸��� ������ ������ ���� Error ���ۿ� ���������� ���� ) 
#endif

	//fx ���Ϸ� ���� ���̴� ��ü ����
	D3DXCreateEffectFromFile(
		g_pD3DDevice,				// ����̽�
		szFileName,					// �ҷ��� ���̴� �ڵ� �����̸�
		NULL,						// ���̴��� �������Ҷ� �߰��� ����� #define ���� ( �ϴ� NULL )
		NULL,						// ���̴��� �������Ҷ� #include ���ù��� ó���Ҷ� ����� �������̽� �÷��� ( �ϴ� NULL )
		dwShaderFlag,				// ���̴� ������ �÷���
		NULL,						// ���̴� �Ű������� ������ �޸�Ǯ ( �ϴ� NULL )
		&pEffect,					// �ε��� ���̴� Effect ������
		&pError						// ���̴��� �ε��ϰ� �������Ҷ� ������ ����� �ش� ���ۿ� �����޽����� ���� ( ���������� �ε��Ǹ� NULL �� �����ȴ� )
		);

	//���̴� ���Ϸε������簡 �ִٸ�..
	if( pError != NULL || pEffect == NULL ){

		//������ ������ ���� ���ڿ��� Ȯ��
		int size = pError->GetBufferSize();
		char* str = new char[ size ];

		//str�� ���ۿ��ִ� ������ �����Ѵ�.
		sprintf_s( str, size,(const char*)pError->GetBufferPointer() );
		
		OutputDebugString(str);
		//���������� ��������� �������� ����
		SAFE_RELEASE( pError );
		SAFE_DELETE_ARRAY(str);

		return NULL;
	}

	m_pEffect = pEffect;

	return pEffect;
}