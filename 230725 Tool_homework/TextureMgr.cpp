#include "pch.h"
#include "TextureMgr.h"


IMPLEMENT_SINGLETON(CTextureMgr)

CTextureMgr::CTextureMgr()
{
}


CTextureMgr::~CTextureMgr()
{
	Release();
}

const TEXINFO* CTextureMgr::Get_Texture(const TCHAR* pObjKey, const TCHAR* pStateKey, const int& iCnt)
{

	auto	iter = find_if(m_mapTex.begin(), m_mapTex.end(), [&](auto& MyPair)->bool {

		if (pObjKey == MyPair.first)
			return true;

		return false;
		});

	if (iter == m_mapTex.end())
		return nullptr;

	return iter->second->Get_Texture(pStateKey, iCnt);
}

HRESULT CTextureMgr::Insert_Texture(const TCHAR* pFilePath, TEXTYPE eType, const TCHAR* pObjKey, const TCHAR* pStateKey, const int& iCnt)
{
	//	람다식 : [모든 외부변수를 참조로 캡처] (오토 레퍼런스, myPair 값 직접참조)  ->함수결과가 bool타입으로 반환되게
	auto	iter = find_if(m_mapTex.begin(), m_mapTex.end(), [&](auto& MyPair)->bool {

		//페어를 다 돌면서 그 첫값이 objkey와 동일하면 true, 아니면 false
		if (pObjKey == MyPair.first)
			return true;

		return false;
		});

	if (iter == m_mapTex.end())  //만약 이터레이터가 끝에 도달했다면(다 돌고 난 뒤에는)
	{
		CTexture* pTexture = nullptr;  //텍스처 포인터를 만들고 nullptr로 선언한 다음

		switch (eType)				//아까 Insert 함수에 들어온 타입 가지고 와서 싱글이었는지 멀티였는지에 따라 다르게 할당
		{
		case TEX_SINGLE:
			pTexture = new CSingleTexture;
			break;


		case TEX_MULTI:
			pTexture = new CMultiTexture;
			break;
		}

		if (FAILED(pTexture->Insert_Texture(pFilePath, pStateKey, iCnt)))    //만약에, 파일 Insert가 실패한 경우,
		{
			AfxMessageBox(pFilePath);   //그 파일패스를 메시지박스로 띄워줘서 실패 사실을 알려준다는 그런 내용!
			return E_FAIL;
		}

		m_mapTex.insert({ pObjKey, pTexture });  //위에 return false들에 하나도 안 걸리고 왔으므로 이상 없음 -> insert 수행
	}

	return S_OK;
}

void CTextureMgr::Release()
{
	for_each(m_mapTex.begin(), m_mapTex.end(), [](auto& MyPair)
		{
			Safe_Delete(MyPair.second);
		});
	m_mapTex.clear();
}