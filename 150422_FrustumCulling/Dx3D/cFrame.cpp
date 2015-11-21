#include "StdAfx.h"
#include "cFrame.h"
#include "cMtlTex.h"

cFrame::cFrame(void)
	: m_pMtlTex(NULL)
	, m_pMesh(NULL)
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matLocal);
}


cFrame::~cFrame(void)
{	
	SAFE_RELEASE(m_pMtlTex);
	SAFE_RELEASE(m_pMesh);
}

void cFrame::Setup()
{

}

void cFrame::Update(D3DXMATRIXA16* pParent, int nKey)
{
	D3DXMATRIXA16 matT, matR;
	CalcLocalTranslation(matT, nKey);
	CalcLocalRotation(matR, nKey);
	
	m_matLocal = matR * matT;

	if(pParent)
	{
		m_matWorld = m_matLocal * (*pParent);
	}
	else
	{
		m_matWorld = m_matLocal;
	}

	for each(auto f in m_vecChild)
	{
		f->Update(&m_matWorld, nKey);
	}
}

void cFrame::Render()
{
	if (m_pMtlTex)
	{
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
		g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
		g_pD3DDevice->SetMaterial(&m_pMtlTex->m_stMtl);
		g_pD3DDevice->SetTexture(0, m_pMtlTex->m_pTexture);
		//g_pD3DDevice->SetStreamSource(0, m_pVB, 0, sizeof(ST_PNT_VERTEX));
		//g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_nNumTri);
		m_pMesh->DrawSubset(0);
	}

	for each(auto f in m_vecChild)
	{
		f->Render();
	}
}

void cFrame::AddChild( cFrame* pFrame )
{
	m_vecChild.push_back(pFrame);
}

void cFrame::Destroy()
{
	for each(auto f in m_vecChild)
	{
		f->Destroy();
	}
	delete this;
}

void cFrame::BuildMesh( std::vector<ST_PNT_VERTEX>& vecVertex )
{
	D3DXMATRIXA16 matInvWorld;
	D3DXMatrixInverse(&matInvWorld, NULL, &m_matWorld);

	for (size_t i = 0; i < vecVertex.size(); ++i)
	{
		D3DXVec3TransformCoord(&vecVertex[i].p, &vecVertex[i].p, &matInvWorld);
		D3DXVec3TransformNormal(&vecVertex[i].n, &vecVertex[i].n, &matInvWorld);
	}



	D3DXCreateMeshFVF(vecVertex.size() / 3,
		vecVertex.size(),
		D3DXMESH_MANAGED,
		ST_PNT_VERTEX::FVF,
		g_pD3DDevice,
		&m_pMesh);

	ST_PNT_VERTEX* pV = NULL;
	m_pMesh->LockVertexBuffer(0, (LPVOID*)&pV);
	memcpy(pV, &vecVertex[0], vecVertex.size() * sizeof(ST_PNT_VERTEX));
	m_pMesh->UnlockVertexBuffer();

	WORD* pI = NULL;
	m_pMesh->LockIndexBuffer(0, (LPVOID*)&pI);
	for (size_t i = 0; i < vecVertex.size(); ++i)
	{
		pI[i] = i;
	}
	m_pMesh->UnlockIndexBuffer();

	DWORD* pA = NULL;
	m_pMesh->LockAttributeBuffer(0, &pA);
	for (size_t i = 0; i < vecVertex.size() / 3; ++i)
	{
		pA[i] = 0;
	}
	m_pMesh->UnlockAttributeBuffer();

	std::vector<DWORD> vecAdjBuffer(vecVertex.size());
	m_pMesh->GenerateAdjacency(0.0f, &vecAdjBuffer[0]);

	m_pMesh->OptimizeInplace(
		D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_COMPACT |
		D3DXMESHOPT_VERTEXCACHE,
		&vecAdjBuffer[0]
		,0, 0, 0);
}

void cFrame::SetOriginLocalTM( D3DXMATRIXA16* pParent )
{
	if(pParent)
	{
		D3DXMATRIXA16 matInvPW;
		D3DXMatrixInverse(&matInvPW, NULL, pParent);
		m_matLocal = m_matWorld * matInvPW;
	}
	else
	{
		m_matLocal = m_matWorld;
	}

	for each(auto f in m_vecChild)
	{
		f->SetOriginLocalTM(&m_matWorld);
	}
}

void cFrame::CalcLocalTranslation( D3DXMATRIXA16& matT, int nKey )
{
	D3DXMatrixIdentity(&matT);

	if(m_vecPosTrack.empty())
	{
		matT._41 = m_matLocal._41;
		matT._42 = m_matLocal._42;
		matT._43 = m_matLocal._43;
		return;
	}
	else
	{
		if (nKey <= m_vecPosTrack.front().nKey)
		{
			matT._41 = m_vecPosTrack.front().v.x;
			matT._42 = m_vecPosTrack.front().v.y;
			matT._43 = m_vecPosTrack.front().v.z;
		}
		else if (nKey >= m_vecPosTrack.back().nKey)
		{
			matT._41 = m_vecPosTrack.back().v.x;
			matT._42 = m_vecPosTrack.back().v.y;
			matT._43 = m_vecPosTrack.back().v.z;
		}
		else
		{
			int nNextIndex = 0;
			for (size_t i = 0; i < m_vecPosTrack.size(); ++i)
			{
				if (nKey < m_vecPosTrack[i].nKey)
				{
					nNextIndex = i;
					break;
				}
			}
			int nPrevIndex = nNextIndex - 1;
			float t = (nKey - m_vecPosTrack[nPrevIndex].nKey)
				/ (float)(m_vecPosTrack[nNextIndex].nKey - m_vecPosTrack[nPrevIndex].nKey);
			D3DXVECTOR3 v;
			D3DXVec3Lerp(&v, &m_vecPosTrack[nPrevIndex].v, &m_vecPosTrack[nNextIndex].v, t);
			matT._41 = v.x;
			matT._42 = v.y;
			matT._43 = v.z;
		}
	}
}

void cFrame::CalcLocalRotation( D3DXMATRIXA16& matR, int nKey )
{
	D3DXMatrixIdentity(&matR);

	if(m_vecRotTrack.empty())
	{
		matR = m_matLocal;
		matR._41 = 0.f;
		matR._42 = 0.f;
		matR._43 = 0.f;
		return;
	}
	else
	{
		D3DXQUATERNION q;
		if (nKey <= m_vecRotTrack.front().nKey)
		{
			q = m_vecRotTrack.front().q;
			D3DXMatrixRotationQuaternion(&matR, &q);
		}
		else if (nKey >= m_vecRotTrack.back().nKey)
		{
			q = m_vecRotTrack.back().q;
			D3DXMatrixRotationQuaternion(&matR, &q);
		}
		else
		{
			int nNextIndex = 0;
			for (size_t i = 0; i < m_vecRotTrack.size(); ++i)
			{
				if (nKey < m_vecRotTrack[i].nKey)
				{
					nNextIndex = i;
					break;
				}
			}
			int nPrevIndex = nNextIndex - 1;
			float t = (nKey - m_vecRotTrack[nPrevIndex].nKey)
				/ (float)(m_vecRotTrack[nNextIndex].nKey - m_vecRotTrack[nPrevIndex].nKey);
			
			D3DXQuaternionSlerp(&q, &m_vecRotTrack[nPrevIndex].q, &m_vecRotTrack[nNextIndex].q, t);
			D3DXMatrixRotationQuaternion(&matR, &q);
		}
	}
}
