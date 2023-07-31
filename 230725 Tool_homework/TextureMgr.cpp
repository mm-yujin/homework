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
	//	���ٽ� : [��� �ܺκ����� ������ ĸó] (���� ���۷���, myPair �� ��������)  ->�Լ������ boolŸ������ ��ȯ�ǰ�
	auto	iter = find_if(m_mapTex.begin(), m_mapTex.end(), [&](auto& MyPair)->bool {

		//�� �� ���鼭 �� ù���� objkey�� �����ϸ� true, �ƴϸ� false
		if (pObjKey == MyPair.first)
			return true;

		return false;
		});

	if (iter == m_mapTex.end())  //���� ���ͷ����Ͱ� ���� �����ߴٸ�(�� ���� �� �ڿ���)
	{
		CTexture* pTexture = nullptr;  //�ؽ�ó �����͸� ����� nullptr�� ������ ����

		switch (eType)				//�Ʊ� Insert �Լ��� ���� Ÿ�� ������ �ͼ� �̱��̾����� ��Ƽ�������� ���� �ٸ��� �Ҵ�
		{
		case TEX_SINGLE:
			pTexture = new CSingleTexture;
			break;


		case TEX_MULTI:
			pTexture = new CMultiTexture;
			break;
		}

		if (FAILED(pTexture->Insert_Texture(pFilePath, pStateKey, iCnt)))    //���࿡, ���� Insert�� ������ ���,
		{
			AfxMessageBox(pFilePath);   //�� �����н��� �޽����ڽ��� ����༭ ���� ����� �˷��شٴ� �׷� ����!
			return E_FAIL;
		}

		m_mapTex.insert({ pObjKey, pTexture });  //���� return false�鿡 �ϳ��� �� �ɸ��� �����Ƿ� �̻� ���� -> insert ����
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