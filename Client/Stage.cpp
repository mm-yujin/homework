#include "stdafx.h"
#include "Stage.h"
#include "TextureMgr.h"
#include "ObjMgr.h"
#include "Mouse.h"
#include "Player.h"

CStage::CStage()
{
}

CStage::~CStage()
{
	Release_Scene();
}

HRESULT CStage::Ready_Scene()
{
	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Stage/Terrain/Tile/Tile%d.png", TEX_MULTI, L"Terrain", L"Tile", 36)))
	{
		ERR_MSG(L"Stage Tile Image Insert failed");
		return E_FAIL;
	}	

	CObj*	pObj = new CMyTerrain;
	if (nullptr == pObj)
		return E_FAIL;
	pObj->Initialize();	
	CObjMgr::Get_Instance()->Add_Object(CObjMgr::TERRAIN, pObj);


	CObj* ppObj = new CMouse;
	if (nullptr == ppObj)
		return E_FAIL;
	ppObj->Initialize();
	CObjMgr::Get_Instance()->Add_Object(CObjMgr::MOUSE, ppObj);


	// �÷��̾�
	CObj* pppObj = new CPlayer;
	if (nullptr == pppObj)
		return E_FAIL;
	pppObj->Initialize();
	CObjMgr::Get_Instance()->Add_Object(CObjMgr::PLAYER, pppObj);
	
	return S_OK;
}

void CStage::Update_Scene()
{
	CObjMgr::Get_Instance()->Update();
}

void CStage::Late_Update_Scene()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CStage::Render_Scene()
{
	CObjMgr::Get_Instance()->Render();
}

void CStage::Release_Scene()
{
}
