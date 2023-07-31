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
	float		fFrame; // �������� ���� ���� ����
	float		fMax;	// �ִ� �̹����� ������ ��

}FRAME;

typedef struct tagTexture
{
	LPDIRECT3DTEXTURE9		pTexture;   // �� ��ü

	D3DXIMAGE_INFO			tImgInfo;	// ����ü

}TEXINFO;

typedef struct tagTile
{
	D3DXVECTOR3	vPos;			// Ÿ���� ���� ��ǥ
	D3DXVECTOR3 vSize;			// Ÿ���� ����, ���� ������

	BYTE		byOption;		// 0, 1��(��ֹ�)
	BYTE		byDrawID;		// �� �� Ÿ�� �̹���

	int			iIndex = 0;
	int			iParentIndex = 0;

}TILE;

typedef	struct tagUnitData
{
	CString	strName;	
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

