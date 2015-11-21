#include "StdAfx.h"
#include "cBox.h"
#include "cDeviceMgr.h"
#include "iCamera.h"

cBox::cBox(void)
: m_pBox(NULL)
, m_pShader(NULL)
, m_pStoneDM(NULL)
, m_pStoneSM(NULL)
, m_pStoneNM(NULL)
, m_vLightColor(0.7f, 0.7f, 0.7f, 1.0f)
, m_vWorldLightPosition(-500.0f, 500.0f, -500.0f, 1.0f)
{
}

cBox::~cBox(void)
{
	SAFE_RELEASE(m_pBox);
	SAFE_RELEASE(m_pShader);
	SAFE_RELEASE(m_pStoneDM);
	SAFE_RELEASE(m_pStoneSM);
	SAFE_RELEASE(m_pStoneNM);
	SAFE_RELEASE(ST_NM_VERTEX::Decl);
}

void cBox::Setup()
{
	// 텍스처 로딩
	if ( FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "Fieldstone_DM.tga", &m_pStoneDM)) ||
		FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "Fieldstone_SM.tga", &m_pStoneSM)) ||
		FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "Fieldstone_NM.tga", &m_pStoneNM)) )
	{
		assert(false && "텍스쳐 로딩 실패");
	}

	// 쉐이더 로딩
	LPD3DXBUFFER pError = NULL;
	DWORD dwShaderFlags = 0;
#if _DEBUG
	dwShaderFlags |= D3DXSHADER_DEBUG;
#endif
	D3DXCreateEffectFromFile(g_pD3DDevice, "NormalMapping.fx",
		NULL, NULL, dwShaderFlags, NULL, &m_pShader, &pError);

	std::vector<ST_NM_VERTEX>	v;
	v.resize(36);
	
	// 근평명
	v[0].pos = D3DXVECTOR4(-1.0f, -1.0f, -1.0f, 1.0f);
	v[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	v[0].tex = D3DXVECTOR2(0.0f, 1.0f);

	v[1].pos = D3DXVECTOR4( 1.0f,  1.0f, -1.0f, 1.0f);
	v[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	v[1].tex = D3DXVECTOR2(1.0f, 0.0f);

	v[2].pos = D3DXVECTOR4( 1.0f, -1.0f, -1.0f, 1.0f);
	v[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	v[2].tex = D3DXVECTOR2(1.0f, 1.0f);

	v[3].pos = D3DXVECTOR4(-1.0f, -1.0f, -1.0f, 1.0f);
	v[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	v[3].tex = D3DXVECTOR2(0.0f, 1.0f);

	v[4].pos = D3DXVECTOR4(-1.0f, 1.0f, -1.0f, 1.0f);
	v[4].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	v[4].tex = D3DXVECTOR2(0.0f, 0.0f);

	v[5].pos = D3DXVECTOR4(1.0f, 1.0f, -1.0f, 1.0f);
	v[5].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	v[5].tex = D3DXVECTOR2(1.0f, 0.0f);

	// 원 평명 - 흰색
	v[6].pos = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	v[6].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	v[6].tex = D3DXVECTOR2(0.0f, 0.0f);

	v[7].pos = D3DXVECTOR4( -1.0f,  1.0f, 1.0f, 1.0f);
	v[7].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	v[7].tex = D3DXVECTOR2(1.0f, 0.0f);

	v[8].pos = D3DXVECTOR4( -1.0f, -1.0f, 1.0f, 1.0f);
	v[8].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	v[8].tex = D3DXVECTOR2(1.0f, 1.0f);

	v[9].pos = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	v[9].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	v[9].tex = D3DXVECTOR2(0.0f, 0.0f);

	v[10].pos = D3DXVECTOR4(-1.0f, -1.0f, 1.0f, 1.0f);
	v[10].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	v[10].tex = D3DXVECTOR2(1.0f, 1.0f);

	v[11].pos = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 1.0f);
	v[11].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	v[11].tex = D3DXVECTOR2(0.0f, 1.0f);

	// 좌 평명
	v[12].pos = D3DXVECTOR4(-1.0f, 1.0f, 1.0f, 1.0f);
	v[12].nor = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	v[12].tex = D3DXVECTOR2(0.0f, 0.0f);

	v[13].pos = D3DXVECTOR4( -1.0f,  1.0f, -1.0f, 1.0f);
	v[13].nor = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	v[13].tex = D3DXVECTOR2(1.0f, 0.0f);

	v[14].pos = D3DXVECTOR4( -1.0f, -1.0f, -1.0f, 1.0f);
	v[14].nor = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	v[14].tex = D3DXVECTOR2(1.0f, 1.0f);

	v[15].pos = D3DXVECTOR4(-1.0f, 1.0f, 1.0f, 1.0f);
	v[15].nor = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	v[15].tex = D3DXVECTOR2(0.0f, 0.0f);

	v[16].pos = D3DXVECTOR4(-1.0f, -1.0f, -1.0f, 1.0f);
	v[16].nor = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	v[16].tex = D3DXVECTOR2(1.0f, 1.0f);

	v[17].pos = D3DXVECTOR4(-1.0f, -1.0f, 1.0f, 1.0f);
	v[17].nor = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	v[17].tex = D3DXVECTOR2(0.0f, 1.0f);

	// 우 평명
	v[18].pos = D3DXVECTOR4(1.0f, 1.0f, -1.0f, 1.0f);
	v[18].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	v[18].tex = D3DXVECTOR2(0.0f, 0.0f);

	v[19].pos = D3DXVECTOR4( 1.0f,  1.0f, 1.0f, 1.0f);
	v[19].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	v[19].tex = D3DXVECTOR2(1.0f, 0.0f);

	v[20].pos = D3DXVECTOR4( 1.0f, -1.0f, 1.0f, 1.0f);
	v[20].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	v[20].tex = D3DXVECTOR2(1.0f, 1.0f);

	v[21].pos = D3DXVECTOR4(1.0f, 1.0f, -1.0f, 1.0f);
	v[21].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	v[21].tex = D3DXVECTOR2(0.0f, 0.0f);

	v[22].pos = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 1.0f);
	v[22].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	v[22].tex = D3DXVECTOR2(1.0f, 1.0f);

	v[23].pos = D3DXVECTOR4(1.0f, -1.0f, -1.0f, 1.0f);
	v[23].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	v[23].tex = D3DXVECTOR2(0.0f, 1.0f);

	// 상 평명
	v[24].pos = D3DXVECTOR4(-1.0f, 1.0f, 1.0f, 1.0f);
	v[24].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	v[24].tex = D3DXVECTOR2(0.0f, 0.0f);

	v[25].pos = D3DXVECTOR4( 1.0f,  1.0f, 1.0f, 1.0f);
	v[25].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	v[25].tex = D3DXVECTOR2(1.0f, 0.0f);

	v[26].pos = D3DXVECTOR4( -1.0f, 1.0f, -1.0f, 1.0f);
	v[26].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	v[26].tex = D3DXVECTOR2(0.0f, 1.0f);

	v[27].pos = D3DXVECTOR4(-1.0f, 1.0f, -1.0f, 1.0f);
	v[27].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	v[27].tex = D3DXVECTOR2(0.0f, 1.0f);

	v[28].pos = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	v[28].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	v[28].tex = D3DXVECTOR2(1.0f, 0.0f);

	v[29].pos = D3DXVECTOR4(1.0f, 1.0f, -1.0f, 1.0f);
	v[29].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	v[29].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 하 평명
	v[30].pos = D3DXVECTOR4(-1.0f, -1.0f, -1.0f, 1.0f);
	v[30].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	v[30].tex = D3DXVECTOR2(0.0f, 0.0f);

	v[31].pos = D3DXVECTOR4( 1.0f,  -1.0f, 1.0f, 1.0f);
	v[31].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	v[31].tex = D3DXVECTOR2(1.0f, 1.0f);

	v[32].pos = D3DXVECTOR4( -1.0f, -1.0f, 1.0f, 1.0f);
	v[32].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	v[32].tex = D3DXVECTOR2(0.0f, 1.0f);

	v[33].pos = D3DXVECTOR4(-1.0f, -1.0f, -1.0f, 1.0f);
	v[33].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	v[33].tex = D3DXVECTOR2(0.0f, 0.0f);

	v[34].pos = D3DXVECTOR4(1.0f, -1.0f, -1.0f, 1.0f);
	v[34].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	v[34].tex = D3DXVECTOR2(1.0f, 0.0f);

	v[35].pos = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 1.0f);
	v[35].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	v[35].tex = D3DXVECTOR2(1.0f, 1.0f);
	
	D3DVERTEXELEMENT9 decl[] =  
	{  
		{0, 0,  D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, 16, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
		{0, 28, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,0},
		{0, 36, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0},
		{0, 48, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0},
		D3DDECL_END() 
	};  

 	D3DXCreateMesh(12, 36, D3DXMESH_MANAGED, decl, g_pD3DDevice, &m_pBox);

	void *pData;

	m_pBox->LockVertexBuffer(NULL, &pData);
	memcpy(pData, &v[0], v.size() * sizeof(ST_NM_VERTEX));
	m_pBox->UnlockVertexBuffer();

	WORD* pIndex = 0;
	m_pBox->LockIndexBuffer(0, (void**)&pIndex);
	for (size_t i = 0; i < v.size(); i++)
	{
		pIndex[i] = i;
	}
	m_pBox->UnlockIndexBuffer();

	DWORD* pDwAttributeBuffer;
	m_pBox->LockAttributeBuffer(0, &pDwAttributeBuffer);
	for (size_t i = 0; i < v.size()/3; i++)
	{
		pDwAttributeBuffer[i] = 0;
	}
	m_pBox->UnlockAttributeBuffer();

	std::vector<DWORD> adjacencyBuffer(v.size());
	m_pBox->GenerateAdjacency(0.001f, &adjacencyBuffer[0]);

	m_pBox->OptimizeInplace(
		D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_COMPACT |
		D3DXMESHOPT_VERTEXCACHE,
		&adjacencyBuffer[0], 0 , 0, 0);

	D3DXComputeTangentFrameEx(m_pBox,
		D3DDECLUSAGE_TEXCOORD, 0,
		D3DDECLUSAGE_TANGENT, 0,
		D3DDECLUSAGE_BINORMAL, 0,
		D3DDECLUSAGE_NORMAL,0,
		D3DXTANGENT_CALCULATE_NORMALS |
		D3DXTANGENT_GENERATE_IN_PLACE,
		NULL,
		0.01f,0.01f,0.01f, NULL, NULL);

	g_pD3DDevice->CreateVertexDeclaration(decl, &ST_NM_VERTEX::Decl);
}

void cBox::Render(iCamera* pCamera)
{
	g_pD3DDevice->SetVertexDeclaration( ST_NM_VERTEX::Decl );
	
	D3DXMATRIXA16 mWorld;
	D3DXMatrixIdentity(&mWorld);

	// 월드/뷰/투영행렬을 미리 곱한다.
	D3DXMATRIXA16 mView, mProj, mViewProj;
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &mView);
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &mProj);
	mViewProj = mView * mProj;

	// 쉐이더 전역변수들을 설정
	m_pShader->SetMatrix("gWorldMatrix", &mWorld);
	m_pShader->SetMatrix("gWorldViewProjectionMatrix",  &mViewProj);

	D3DXVECTOR4 vEye = pCamera->GetEye();
	vEye.w = 1.0f;
	m_pShader->SetVector("gWorldLightPosition", &m_vWorldLightPosition);
	m_pShader->SetVector("gWorldCameraPosition", &vEye);

	m_pShader->SetVector("gLightColor", &m_vLightColor);
	m_pShader->SetTexture("DiffuseMap_Tex", m_pStoneDM);
	m_pShader->SetTexture("SpecularMap_Tex", m_pStoneSM);

	m_pShader->SetTexture("NormalMap_Tex", m_pStoneNM);

	// 쉐이더를 시작한다.
	UINT numPasses = 0;
	m_pShader->Begin(&numPasses, NULL);
	{
		for (UINT i = 0; i < numPasses; ++i )
		{
			m_pShader->BeginPass(i);
			{
				m_pBox->DrawSubset(0);
			}
			m_pShader->EndPass();
		}
	}
	m_pShader->End();
}
