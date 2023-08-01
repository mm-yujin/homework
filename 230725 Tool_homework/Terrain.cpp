#include "pch.h"
#include "MainFrm.h"
#include "Terrain.h"
#include "TextureMgr.h"
#include "Device.h"
#include "230725 Tool_homeworkView.h"

CTerrain::CTerrain()
{
    //벡터 reserve로 처음부터 카파시티 정하고 시작해서 속도 안 떨어지게 만드는 모양
    m_vecTile.reserve(TILEX * TILEY);
}

CTerrain::~CTerrain()
{
    Release();
}

void CTerrain::Initialize()
{
    // 텍스처 매니저 : 오류나면 오류 출력하는 코드
    if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Stage/Terrain/Tile/Tile%d.png", TEX_MULTI, L"Terrain", L"Tile", 36)))
        AfxMessageBox(L"TILE IMG FAILED");

    for (int i = 0; i < TILEY; ++i) {
        for (int j = 0; j < TILEX; ++j) {

            TILE* m_Tile = new TILE;

            if (i % 2 == 0) { 
                m_Tile->vPos = { (float)j * TILECX, i * TILECY * 0.5f, 0.f };
                m_Tile->byDrawID = 2; }
            else if (i % 2 == 1) { 
                m_Tile->vPos = { j * TILECX - (TILECX * 0.5f), i * TILECY * 0.5f, 0.f };
                m_Tile->byDrawID = 5; }
            m_Tile->byOption = 0;
            m_Tile->vSize.x = TILECX;
            m_Tile->vSize.y = TILECY;
                 
            m_vecTile.push_back(m_Tile);
        }
    }
    //중점, 사이즈 설정하고 벡터에 담는 내용
}

void CTerrain::Update()
{
}

void CTerrain::Render()
{
    D3DXMATRIX matWorld, matScale, matTrans;

    TCHAR       szBuf[MIN_STR] = L"";
    int         iIndex = 0;

    for (auto& iter : m_vecTile)
    {
        const TEXINFO* pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"Terrain", L"Tile", iter->byDrawID);
        //m_vecTile.front()->byDrawID 라고 써서인가? pTexInfo이(가) nullptr였습니다 < 오류 나옴
        //아니,,, L"Terrain"을 L"Terrian"으로 잘못 써서 그랬는 듯;;;

        D3DXMatrixIdentity(&matWorld);
        D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
        D3DXMatrixTranslation(&matTrans, iter->vPos.x - m_pMainView->GetScrollPos(0) + m_pMainView->Get_ScrollX(),
                                         iter->vPos.y - m_pMainView->GetScrollPos(1) + m_pMainView->Get_ScrollY(),
                                         iter->vPos.z);

        matWorld = matScale * matTrans;

        RECT		rc{};

        // GetClientRect : 현재 클라이언트 영역의 렉트 정보를 얻어옴
        GetClientRect(m_pMainView->m_hWnd, &rc);

        float fX = WINCX / float(rc.right - rc.left);
        float fY = WINCY / float(rc.bottom - rc.top);

        Set_Ratio(&matWorld, fX, fY);

        float   fCenterX = iter->vSize.x * 0.5f;
        float   fCenterY = iter->vSize.y * 0.5f;

        CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

        CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

        swprintf_s(szBuf, L"%d", iIndex);

        CDevice::Get_Instance()->Get_Font()->DrawTextW(CDevice::Get_Instance()->Get_Sprite(), szBuf, lstrlen(szBuf), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

        ++iIndex;

    }
    //렌더하는 내용
    //폰트, 타일
}


void CTerrain::Mini_Render()
{

    D3DXMATRIX	matWorld, matScale, matTrans;

    for (auto& iter : m_vecTile)
    {
        const TEXINFO* pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"Terrain", L"Tile", iter->byDrawID);

        D3DXMatrixIdentity(&matWorld);
        D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
        D3DXMatrixTranslation(&matTrans,
            iter->vPos.x,
            iter->vPos.y,
            iter->vPos.z);

        matWorld = matScale * matTrans;

        float		fCenterX = pTexInfo->tImgInfo.Width / 2.f;
        float		fCenterY = pTexInfo->tImgInfo.Height / 2.f;

        Set_Ratio(&matWorld, 0.3f, 0.3f);

        CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

        CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,	// 텍스처 객체 주소
            nullptr, // 출력할 이미지 영역에 대한 렉트 구조체 주소, null인경우 이미지의 0, 0기준으로 출력
            &D3DXVECTOR3(fCenterX, fCenterY, 0.f), // 출력할 이미지의 중심 축에 대한 vector3 구조체 포인터, nullptr인 경우 0, 0이 중심 좌표
            nullptr, // 위치 좌표에 따른 vector3 구조체 포인어
            D3DCOLOR_ARGB(255, 255, 255, 255));	// 출력할 원본 이미지와 섞을 색상 값, 출력 시 섞은 색이 반영, 0xffffffff를 넘겨주면 원본 색상 유지

    }
}

void CTerrain::Set_Ratio(D3DXMATRIX* pOut, float fRatioX, float fRatioY)
{
    pOut->_11 *= fRatioX;
    pOut->_21 *= fRatioX;
    pOut->_31 *= fRatioX;
    pOut->_41 *= fRatioX;

    pOut->_12 *= fRatioY;
    pOut->_22 *= fRatioY;
    pOut->_32 *= fRatioY;
    pOut->_42 *= fRatioY;
}

void CTerrain::Release()
{
    //벡터 할당 해제(deleteobj)
    //클리어, 쉬링크 투 핏(스왑으로 벡터 카파시티 삭제하는 함수)

    for_each(m_vecTile.begin(), m_vecTile.end(), CDeleteObj());
    m_vecTile.clear();
    m_vecTile.shrink_to_fit();
}

void CTerrain::Tile_Change(const D3DXVECTOR3& vPos, const BYTE& byDrawID)
{
    //피킹된 경우 호출해서 타일 정보 수정하기
    int iIndex = Get_TileIdx(vPos);

    if (-1 == iIndex)
        return;

    m_vecTile[iIndex]->byDrawID = byDrawID;
    m_vecTile[iIndex]->byOption = 1;
}

int CTerrain::Get_TileIdx(const D3DXVECTOR3& vPos)
{
    //인덱스 첨부터 끝까지 돌다가 피킹이 true 뜨면 해당 인덱스 값 반환하기 위해 분리해 만든 함수
    //if 안에 쓰는 걸 Picking으로 하냐 Picking_Dot으로 하느냐의 차이
    for (size_t index = 0; index < m_vecTile.size(); ++index)
    {
        if (Picking_Dot(vPos, index))
            return index;
    }

    return -1;
}

bool CTerrain::Picking(const D3DXVECTOR3& vPos, const int& iIndex)  //그냥 vPos는 마우스좌표;
{
    //직선의 방정식으로 피킹 검사하는 방식
    //y = ax + b

    //1. 중점 4개 구하기 : 시계방향
    D3DXVECTOR3 m_Point[4] {
		{ m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y + (TILECY / 2.f), 0.f },
		{ m_vecTile[iIndex]->vPos.x + (TILECX / 2.f), m_vecTile[iIndex]->vPos.y, 0.f },
		{ m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y - (TILECY / 2.f), 0.f },
		{ m_vecTile[iIndex]->vPos.x - (TILECX / 2.f), m_vecTile[iIndex]->vPos.y, 0.f }
    };

    //2. 각 선분의 기울기 구하기: 시계방향
    float m_incli[4]{
        (TILECY / 2.f) / (TILECX / 2.f) * -1.f,
        (TILECY / 2.f) / (TILECX / 2.f),
        (TILECY / 2.f) / (TILECX / 2.f) * -1.f,
        (TILECY / 2.f) / (TILECX / 2.f)
    };

    //y = ax + b
    //b = y - ax 
    //3. 방정식 풀기(a값인 기울기가 있으니 b값인 y절편 구하기)
    float LineEqu[4]{
        m_Point[0].y - m_incli[0] * m_Point[0].x,
        m_Point[1].y - m_incli[1] * m_Point[1].x,
        m_Point[2].y - m_incli[2] * m_Point[2].x,
        m_Point[3].y - m_incli[3] * m_Point[3].x
    };

    // 0 == ax + b - y		// 점이 직선 상에 놓여 있는 경우
    // 0 > ax + b - y		// 점이 직선보다 위 쪽에 놓여 있는 경우
    // 0 < ax + b - y		// 점이 직선보다 아래 쪽에 놓여 있는 경우

    bool bCheck[4]{ false };

    if (0 < m_incli[0] * vPos.x + LineEqu[0] - vPos.y)
        bCheck[0] = true;

    if (0 >= m_incli[1] * vPos.x + LineEqu[1] - vPos.y)
        bCheck[1] = true;

    if (0 >= m_incli[2] * vPos.x + LineEqu[2] - vPos.y)
        bCheck[2] = true;

    if (0 < m_incli[3] * vPos.x + LineEqu[3] - vPos.y)
        bCheck[3] = true;

    return bCheck[0] && bCheck[1] && bCheck[2] && bCheck[3];
}

bool CTerrain::Picking_Dot(const D3DXVECTOR3& vPos, const int& iIndex)
{
    //내적으로 피킹 검사하는 방식

    //1. 중점 구하기 : 시계방향
    D3DXVECTOR3 m_Point[4]{
    { m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y + (TILECY / 2.f), 0.f },
    { m_vecTile[iIndex]->vPos.x + (TILECX / 2.f), m_vecTile[iIndex]->vPos.y, 0.f },
    { m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y - (TILECY / 2.f), 0.f },
    { m_vecTile[iIndex]->vPos.x - (TILECX / 2.f), m_vecTile[iIndex]->vPos.y, 0.f }
    };

    //2. 방향벡터 시계방향으로 구하기
    D3DXVECTOR3 v_Dir[4]{
        m_Point[1] - m_Point[0],
        m_Point[2] - m_Point[1],
        m_Point[3] - m_Point[2],
        m_Point[0] - m_Point[3]
    };

    //3. 법선벡터 구하기 : 중점이 아니라 방향벡터가지고 해야지!!!!
    D3DXVECTOR3 v_Normal[4]{
        { -v_Dir[0].y, v_Dir[0].x, 0.f },
        { -v_Dir[1].y, v_Dir[1].x, 0.f },
        { -v_Dir[2].y, v_Dir[2].x, 0.f },
        { -v_Dir[3].y, v_Dir[3].x, 0.f }
    };

    //4. 마우스 방향벡터 구하기
    D3DXVECTOR3 v_Mouse[4]{
        vPos - m_Point[0],
        vPos - m_Point[1],
        vPos - m_Point[2],
        vPos - m_Point[3]
    };

    //5. 마우스-법선벡터 정규화, 각 벡터간 내적
    for (int i = 0; i < 4; ++i) {
        D3DXVec3Normalize(&v_Normal[i], &v_Normal[i]);
        D3DXVec3Normalize(&v_Mouse[i], &v_Mouse[i]);
    }

    //6. 각도비교를 통한 내외판정
    for (int i = 0; i < 4; ++i) {
        if (0.f < D3DXVec3Dot(&v_Mouse[i], &v_Normal[i]))
            return false;
    }

    return true;
}
