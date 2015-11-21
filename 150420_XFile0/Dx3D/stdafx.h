// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#include <vector>
#include <list>
#include <map>
#include <set>
#include <string>
#include <assert.h>

#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

extern HWND g_hWnd;


#define SAFE_DELETE(p) {if(p){delete p;p = NULL;}}
#define SAFE_RELEASE(p) {if(p){p->Release();p = NULL;}}
#define SAFE_ADD_REF(p) {if(p){p->AddRef();}}

#define SINGLETONE(class_name) private: class_name(void); ~class_name(void); \
	public: static class_name* GetInstance()\
	{\
		static class_name instance;\
		return &instance;\
	}

// 1. Position ������ ��ǥ x,y,z(float)              :  D3DFVF_XYZ
// 2. RHW (float)                                    :  D3DFVF_XYZRHW
// (D3DFVF_XYZ �Ǵ� D3DFVF_NORMAL�� ���� ���Ұ�)
// 3. Blending Weight Data ���� ����ġ (float)       : D3DFVF_XYZB1 ~ D3DFVF_XYZB5
// 4. Vertex Normal ������ ���� ���� x,y,z(float)    : D3DFVF_NORMAL
// 5. Vertex Point Size ������ �� ũ�� (float)       : D3DFVF_PSIZE
// 6. Diffuse Color (DWORD)                          : D3DFVF_DIFFUSE
// 7. Specular Color (DWORD)                           D3DFVF_SPECULAR
// 8. Texture Coordinate Set 1 (float)               : D3DFVF_TEX0 - D3DFVF_TEX8

struct ST_PC_VERTEX
{
	D3DXVECTOR3 p;
	D3DCOLOR	c;

	enum {FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE};
};

struct ST_PN_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	
	enum {FVF = D3DFVF_XYZ | D3DFVF_NORMAL};
};

struct ST_PT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR2	t;

	enum {FVF = D3DFVF_XYZ | D3DFVF_TEX1};
};

struct ST_PNT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	D3DXVECTOR2	t;

	enum {FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1};
};

struct ST_POS_SAMPLE
{
	int				nKey;
	D3DXVECTOR3		v;
};

struct ST_ROT_SAMPLE
{
	int				nKey;
	D3DXQUATERNION	q;
};

#define COST_INFINITY 99999.f

#define SYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: inline varType Get##funName(void) const { return varName; }\
public: inline void Set##funName(varType var){ varName = var; }

#define SYNTHESIZE_PASS_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: inline varType& Get##funName(void) const { return varName; }\
public: inline void Set##funName(varType& var){ varName = var; }

#define SYNTHESIZE_ADD_REF(varType, varName, funName)    \
protected: varType varName; \
public: virtual varType Get##funName(void) const { return varName; } \
public: virtual void Set##funName(varType var){\
	if (varName != var) {\
	SAFE_ADD_REF(var);\
	SAFE_RELEASE(varName);\
	varName = var;\
	}\
}

#include "cObject.h"
#include "cDeviceManager.h"
#include "cTextureManager.h"