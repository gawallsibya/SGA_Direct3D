// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

#include <MMSystem.h>

// C�� ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#include <d3dx9.h>
#include <assert.h>
#include <vector>
#include <map>
#include <string>

#define WINSIZE_X 1024
#define WINSIZE_Y 768

#define SAFE_RELEASE(p) {if(p)p->Release(); p = NULL;}
#define SAFE_DELETE_ARRAY(p) {if(p) delete [] p; p = NULL;}
#define SAFE_DELETE(p) {if(p) delete p; p = NULL;}

struct ST_VERTEX
{
	D3DXVECTOR4 p;
	D3DXVECTOR2	t;
	static const DWORD FVF;
};

struct ST_PNT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	D3DXVECTOR2	t;
	static const DWORD FVF;
};

struct ST_NM_VERTEX_TEMP
{
	float x, y, z;
	float nx, ny, nz;
	DWORD diffuse;
	float tu1, tv1;
	float tu2, tv2;
};

struct ST_NM_VERTEX
{
	D3DXVECTOR4 pos;
	D3DXVECTOR3 nor;
	D3DXVECTOR2	tex;
	D3DXVECTOR3	bin;
	D3DXVECTOR3	tan;
	
	static LPDIRECT3DVERTEXDECLARATION9 Decl;
};

struct ST_PT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR2	t;
	static const DWORD FVF;
};

struct ST_PC_VERTEX
{
	D3DXVECTOR3 p;
	D3DCOLOR	c;
	static const DWORD FVF;
};

struct ST_ORIGIN
{
	float x;
	float y;
	ST_ORIGIN() : x(0.0f), y(0.0f) {}
};

struct ST_SIZE
{
	float width;
	float height;
	ST_SIZE() : width(0.0f), height(0.0f) {}
};

struct ST_MTL_TEX
{
	D3DMATERIAL9		Mtl;
	LPDIRECT3DTEXTURE9	pTex;
	ST_MTL_TEX() : pTex(NULL)
	{
		memset(&Mtl, 0, sizeof(D3DMATERIAL9));
	}
	~ST_MTL_TEX()
	{
		SAFE_RELEASE(pTex);
	}
};

struct ST_GROUP
{
	int						nNumTri;
	std::string				sMtlName;
	LPDIRECT3DVERTEXBUFFER9	pVB;
	ST_GROUP() : nNumTri(0), pVB(NULL) {}
	~ST_GROUP()
	{
		SAFE_RELEASE(pVB);
	}
};

//#define MY_FVF D3DFVF_XYZRHW | D3DFVF_DIFFUSE
