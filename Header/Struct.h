#pragma once

typedef struct tagInfo
{
	D3DXVECTOR3		vPos;
	D3DXVECTOR3		vDir;
	D3DXVECTOR3		vLook;
	D3DXVECTOR3		vSize;

	D3DXMATRIX		matWorld;
}INFO;

typedef	struct tagFrame
{
	float		fFrame; // 프레임을 세기 위한 변수
	float		fMax;	// 최대 이미지의 프레임 수
	DWORD		dwTime;
	//만들고 나서 쿼리퍼포먼스카운터로 바꿀 것

}FRAME;

typedef struct tagTexture
{
	LPDIRECT3DTEXTURE9		pTexture;   // 컴 객체

	D3DXIMAGE_INFO			tImgInfo;	// 구조체

}TEXINFO;

typedef struct tagTile
{
	D3DXVECTOR3	vPos;			// 타일의 중점 좌표
	D3DXVECTOR3 vSize;			// 타일의 가로, 세로 사이즈

	BYTE		byOption;		// 0, 1번(장애물)
	BYTE		byDrawID;		// 몇 번 타일 이미지

	int			iIndex = 0;
	int			iParentIndex = 0;

}TILE;

typedef	struct tagUnitData
{
	//Cstring이 MFC에서만 되는 거여서 오류가 나는 거

#ifdef _AFX
	CString	strName;	
#else
	wstring	strName;
#endif
	int		iAttack;
	int		iHp;
	BYTE	byJobIndex;
	BYTE	byItem;

}UNITDATA;

typedef struct tagTexturePath
{
	wstring		wstrObjKey		= L"";
	wstring		wstrStateKey	= L"";
	wstring		wstrPath = L"";
	int			iCount = 0;

}IMGPATH;

