#include "pch.h"
#include "MainFrm.h"
#include "Terrain.h"
#include "TextureMgr.h"
#include "Device.h"
#include "230725 Tool_homeworkView.h"

CTerrain::CTerrain()
{
    //���� reserve�� ó������ ī�Ľ�Ƽ ���ϰ� �����ؼ� �ӵ� �� �������� ����� ���
    m_vecTile.reserve(TILEX * TILEY);
}

CTerrain::~CTerrain()
{
    Release();
}

void CTerrain::Initialize()
{
    // �ؽ�ó �Ŵ��� : �������� ���� ����ϴ� �ڵ�
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
    //����, ������ �����ϰ� ���Ϳ� ��� ����
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
        //m_vecTile.front()->byDrawID ��� �Ἥ�ΰ�? pTexInfo��(��) nullptr�����ϴ� < ���� ����
        //�ƴ�,,, L"Terrain"�� L"Terrian"���� �߸� �Ἥ �׷��� ��;;;

        D3DXMatrixIdentity(&matWorld);
        D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
        D3DXMatrixTranslation(&matTrans, iter->vPos.x - m_pMainView->GetScrollPos(0) + m_pMainView->Get_ScrollX(),
                                         iter->vPos.y - m_pMainView->GetScrollPos(1) + m_pMainView->Get_ScrollY(),
                                         iter->vPos.z);

        matWorld = matScale * matTrans;

        RECT		rc{};

        // GetClientRect : ���� Ŭ���̾�Ʈ ������ ��Ʈ ������ ����
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
    //�����ϴ� ����
    //��Ʈ, Ÿ��
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

        CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,	// �ؽ�ó ��ü �ּ�
            nullptr, // ����� �̹��� ������ ���� ��Ʈ ����ü �ּ�, null�ΰ�� �̹����� 0, 0�������� ���
            &D3DXVECTOR3(fCenterX, fCenterY, 0.f), // ����� �̹����� �߽� �࿡ ���� vector3 ����ü ������, nullptr�� ��� 0, 0�� �߽� ��ǥ
            nullptr, // ��ġ ��ǥ�� ���� vector3 ����ü ���ξ�
            D3DCOLOR_ARGB(255, 255, 255, 255));	// ����� ���� �̹����� ���� ���� ��, ��� �� ���� ���� �ݿ�, 0xffffffff�� �Ѱ��ָ� ���� ���� ����

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
    //���� �Ҵ� ����(deleteobj)
    //Ŭ����, ����ũ �� ��(�������� ���� ī�Ľ�Ƽ �����ϴ� �Լ�)

    for_each(m_vecTile.begin(), m_vecTile.end(), CDeleteObj());
    m_vecTile.clear();
    m_vecTile.shrink_to_fit();
}

void CTerrain::Tile_Change(const D3DXVECTOR3& vPos, const BYTE& byDrawID)
{
    //��ŷ�� ��� ȣ���ؼ� Ÿ�� ���� �����ϱ�
    int iIndex = Get_TileIdx(vPos);

    if (-1 == iIndex)
        return;

    m_vecTile[iIndex]->byDrawID = byDrawID;
    m_vecTile[iIndex]->byOption = 1;
}

int CTerrain::Get_TileIdx(const D3DXVECTOR3& vPos)
{
    //�ε��� ÷���� ������ ���ٰ� ��ŷ�� true �߸� �ش� �ε��� �� ��ȯ�ϱ� ���� �и��� ���� �Լ�
    //if �ȿ� ���� �� Picking���� �ϳ� Picking_Dot���� �ϴ����� ����
    for (size_t index = 0; index < m_vecTile.size(); ++index)
    {
        if (Picking_Dot(vPos, index))
            return index;
    }

    return -1;
}

bool CTerrain::Picking(const D3DXVECTOR3& vPos, const int& iIndex)  //�׳� vPos�� ���콺��ǥ;
{
    //������ ���������� ��ŷ �˻��ϴ� ���
    //y = ax + b

    //1. ���� 4�� ���ϱ� : �ð����
    D3DXVECTOR3 m_Point[4] {
		{ m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y + (TILECY / 2.f), 0.f },
		{ m_vecTile[iIndex]->vPos.x + (TILECX / 2.f), m_vecTile[iIndex]->vPos.y, 0.f },
		{ m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y - (TILECY / 2.f), 0.f },
		{ m_vecTile[iIndex]->vPos.x - (TILECX / 2.f), m_vecTile[iIndex]->vPos.y, 0.f }
    };

    //2. �� ������ ���� ���ϱ�: �ð����
    float m_incli[4]{
        (TILECY / 2.f) / (TILECX / 2.f) * -1.f,
        (TILECY / 2.f) / (TILECX / 2.f),
        (TILECY / 2.f) / (TILECX / 2.f) * -1.f,
        (TILECY / 2.f) / (TILECX / 2.f)
    };

    //y = ax + b
    //b = y - ax 
    //3. ������ Ǯ��(a���� ���Ⱑ ������ b���� y���� ���ϱ�)
    float LineEqu[4]{
        m_Point[0].y - m_incli[0] * m_Point[0].x,
        m_Point[1].y - m_incli[1] * m_Point[1].x,
        m_Point[2].y - m_incli[2] * m_Point[2].x,
        m_Point[3].y - m_incli[3] * m_Point[3].x
    };

    // 0 == ax + b - y		// ���� ���� �� ���� �ִ� ���
    // 0 > ax + b - y		// ���� �������� �� �ʿ� ���� �ִ� ���
    // 0 < ax + b - y		// ���� �������� �Ʒ� �ʿ� ���� �ִ� ���

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
    //�������� ��ŷ �˻��ϴ� ���

    //1. ���� ���ϱ� : �ð����
    D3DXVECTOR3 m_Point[4]{
    { m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y + (TILECY / 2.f), 0.f },
    { m_vecTile[iIndex]->vPos.x + (TILECX / 2.f), m_vecTile[iIndex]->vPos.y, 0.f },
    { m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y - (TILECY / 2.f), 0.f },
    { m_vecTile[iIndex]->vPos.x - (TILECX / 2.f), m_vecTile[iIndex]->vPos.y, 0.f }
    };

    //2. ���⺤�� �ð�������� ���ϱ�
    D3DXVECTOR3 v_Dir[4]{
        m_Point[1] - m_Point[0],
        m_Point[2] - m_Point[1],
        m_Point[3] - m_Point[2],
        m_Point[0] - m_Point[3]
    };

    //3. �������� ���ϱ� : ������ �ƴ϶� ���⺤�Ͱ����� �ؾ���!!!!
    D3DXVECTOR3 v_Normal[4]{
        { -v_Dir[0].y, v_Dir[0].x, 0.f },
        { -v_Dir[1].y, v_Dir[1].x, 0.f },
        { -v_Dir[2].y, v_Dir[2].x, 0.f },
        { -v_Dir[3].y, v_Dir[3].x, 0.f }
    };

    //4. ���콺 ���⺤�� ���ϱ�
    D3DXVECTOR3 v_Mouse[4]{
        vPos - m_Point[0],
        vPos - m_Point[1],
        vPos - m_Point[2],
        vPos - m_Point[3]
    };

    //5. ���콺-�������� ����ȭ, �� ���Ͱ� ����
    for (int i = 0; i < 4; ++i) {
        D3DXVec3Normalize(&v_Normal[i], &v_Normal[i]);
        D3DXVec3Normalize(&v_Mouse[i], &v_Mouse[i]);
    }

    //6. �����񱳸� ���� ��������
    for (int i = 0; i < 4; ++i) {
        if (0.f < D3DXVec3Dot(&v_Mouse[i], &v_Normal[i]))
            return false;
    }

    return true;
}
