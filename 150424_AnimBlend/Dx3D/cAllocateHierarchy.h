#pragma once

struct ST_BONE_MESH : public D3DXMESHCONTAINER
{
	std::vector<LPDIRECT3DTEXTURE9>	vecTexture;
	std::vector<D3DMATERIAL9>		vecMaterial;
	LPD3DXMESH		pOrigMesh;				// 원본 메쉬 CloneMeshFVF로 복사
	D3DXMATRIX**	ppBoneMatrixPtrs;		// 이 메쉬에 영향을 주는 프레임'들'의 월드매트릭스 포인터 배열
	D3DXMATRIX*		pBoneOffsetMatrices;	// 원본 메쉬를 로컬스페이스로 보내는 매트릭스들.
	D3DXMATRIX*		pCurrentBoneMatrices;	// 각 본의 계산된 월드매트릭스
};


struct ST_BONE : public D3DXFRAME
{
	D3DXMATRIX matWorld;

	void Update(D3DXMATRIX* pParent)
	{
		matWorld = TransformationMatrix;
		if(pParent)
		{
			matWorld *= (*pParent);
		}
		if(pFrameFirstChild)
		{
			((ST_BONE*)pFrameFirstChild)->Update(&matWorld);
		}

		if(pFrameSibling)
		{
			((ST_BONE*)pFrameSibling)->Update(pParent);
		}
	}

	void Render()
	{
		if(pMeshContainer)
		{
			ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pMeshContainer;
			LPD3DXMESH pMesh = pBoneMesh->MeshData.pMesh;
			if(pMesh)
			{
				for (size_t i = 0; i < pBoneMesh->vecMaterial.size(); ++i)
				{
					g_pD3DDevice->SetTexture(0, pBoneMesh->vecTexture[i]);
					g_pD3DDevice->SetMaterial(&pBoneMesh->vecMaterial[i]);
					pMesh->DrawSubset(i);
				}
			}
		}

		if(pFrameFirstChild)
		{
			((ST_BONE*)pFrameFirstChild)->Render();
		}

		if(pFrameSibling)
		{
			((ST_BONE*)pFrameSibling)->Render();
		}
	}
};



class cAllocateHierarchy : public ID3DXAllocateHierarchy
{
private:
	SYNTHESIZE(std::string, m_sFolder, Folder);

public:
	cAllocateHierarchy(void);
	~cAllocateHierarchy(void);

	STDMETHOD(CreateFrame)(THIS_ LPCSTR Name, 
		LPD3DXFRAME *ppNewFrame) override;

	STDMETHOD(CreateMeshContainer)(THIS_ 
		LPCSTR Name, 
		CONST D3DXMESHDATA *pMeshData, 
		CONST D3DXMATERIAL *pMaterials, 
		CONST D3DXEFFECTINSTANCE *pEffectInstances, 
		DWORD NumMaterials, 
		CONST DWORD *pAdjacency, 
		LPD3DXSKININFO pSkinInfo, 
		LPD3DXMESHCONTAINER *ppNewMeshContainer) override;

	STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree) override; 

	STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree) override; 
};

