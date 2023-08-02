#include "stdafx.h"
#include "Player.h"
#include "Scroll.h"
#include "TextureMgr.h"
#include "Device.h"

CPlayer::CPlayer() : m_Point()
{
	m_WayPoint = { WINCX * 0.5f, WINCY * 0.5f, 0.f };
}

CPlayer::~CPlayer()
{
}

HRESULT CPlayer::Initialize(void)
{
    m_tInfo.vPos = { WINCX * 0.5f, WINCY * 0.5f, 0.f };

    m_tFrame.fFrame = 0;
	m_tFrame.fMax = 11;
	
	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Stage/Player/Walk/AKIHA_AKI26_00%d.png", TEX_MULTI, L"Player_W", L"Walk", 13)))
		MessageBox(g_hWnd, L"IMG FAILED", L"����", MB_OK);

	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Stage/Player/Stand/AKIHA_AKI00_00%d.png", TEX_MULTI, L"Player_S", L"Stand", 12)))
		MessageBox(g_hWnd, L"IMG FAILED", L"����", MB_OK);

    return E_NOTIMPL;
}

int CPlayer::Update(void)
{
	Move_Player();
    __super::Move_Frame();

    return 0;
}

void CPlayer::Late_Update(void)
{
}

void CPlayer::Render(void)
{
	//HDC hDC = GetDC(g_hWnd);

	const TEXINFO* pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"Player_W", L"Walk", m_tFrame.fFrame);
	const TEXINFO* pTexInfo2 = CTextureMgr::Get_Instance()->Get_Texture(L"Player_S", L"Stand", m_tFrame.fFrame);


	D3DXMATRIX		matWorld, matScale, matTrans;

	TCHAR			szBuf[MIN_STR] = L"";
	int				iIndex = 0;

		int	iScrollX = int(CScroll::Get_Instance()->Get_ScrollX());
		int	iScrollY = int(CScroll::Get_Instance()->Get_ScrollY());

		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
		D3DXMatrixTranslation(&matTrans,
			m_tInfo.vPos.x + iScrollX,	// x������ ��ũ�� ��
			m_tInfo.vPos.y + iScrollY,	// y������ ��ũ�� ��
			m_tInfo.vPos.z);

		matWorld = matScale * matTrans;

		if (Move_Player())
		{
			
			float	fX = pTexInfo->tImgInfo.Width / 2.f;
			float	fY = pTexInfo->tImgInfo.Height * 0.8f;

			CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

			CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, // ����� �̹��� �İ�ü
				nullptr, // ����� �̹��� ������ ���� RECT����ü ������, NULL�� ��� �̹����� 0,0 �������� ���
				&D3DXVECTOR3(fX, fY, 0.f), // ����� �̹����� �߽� �࿡ ���� VEC3 ����ü ������, NULL�� ��� 0, 0�� �߽� ��ǥ
				nullptr, // ��ġ ��ǥ�� ���� VEC3����ü ������, NULL�� ��� ��ũ�� �� 0, 0 ��ǥ ���
				D3DCOLOR_ARGB(255, 255, 255, 255));// ����� ���� �̹����� ���� ���� ��, ��� �� ���� ������ �ݿ�(0xffffffff�� �Ѱ��ָ� ���� ���� ����)

		}
		else if (!Move_Player())
		{
			float	fX = pTexInfo2->tImgInfo.Width / 2.f;
			float	fY = pTexInfo2->tImgInfo.Height * 0.8f;

			CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

			CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo2->pTexture, // ����� �̹��� �İ�ü
				nullptr, // ����� �̹��� ������ ���� RECT����ü ������, NULL�� ��� �̹����� 0,0 �������� ���
				&D3DXVECTOR3(fX, fY, 0.f), // ����� �̹����� �߽� �࿡ ���� VEC3 ����ü ������, NULL�� ��� 0, 0�� �߽� ��ǥ
				nullptr, // ��ġ ��ǥ�� ���� VEC3����ü ������, NULL�� ��� ��ũ�� �� 0, 0 ��ǥ ���
				D3DCOLOR_ARGB(255, 255, 255, 255));// ����� ���� �̹����� ���� ���� ��, ��� �� ���� ������ �ݿ�(0xffffffff�� �Ѱ��ָ� ���� ���� ����)

		}


		//MoveToEx(hDC, m_tInfo.vPos.x + iScrollX - 50, m_tInfo.vPos.y + iScrollY - 50, nullptr);
		//LineTo(hDC, m_tInfo.vPos.x + iScrollX + 50, m_tInfo.vPos.y + iScrollY - 50);
		//LineTo(hDC, m_tInfo.vPos.x + iScrollX + 50, m_tInfo.vPos.y + iScrollY + 50);
		//LineTo(hDC, m_tInfo.vPos.x + iScrollX - 50, m_tInfo.vPos.y + iScrollY + 50);
		//LineTo(hDC, m_tInfo.vPos.x + iScrollX - 50, m_tInfo.vPos.y + iScrollY - 50);

		//swprintf_s(szBuf, L"%d", iIndex);
		//CDevice::Get_Instance()->Get_Font()->DrawTextW(CDevice::Get_Instance()->Get_Sprite(),
		//	szBuf,
		//	lstrlen(szBuf),
		//	nullptr,
		//	0,
		//	D3DCOLOR_ARGB(255, 255, 255, 255));



}

void CPlayer::Release(void)
{
}

bool CPlayer::Move_Player(void)
{
	int	iScrollX = int(CScroll::Get_Instance()->Get_ScrollX());
	int	iScrollY = int(CScroll::Get_Instance()->Get_ScrollY());

	if (GetAsyncKeyState(VK_LBUTTON)) {
		GetCursorPos(&m_Point);
		ScreenToClient(g_hWnd, &m_Point);
		m_WayPoint = { (float)m_Point.x - iScrollX, (float)m_Point.y - iScrollY, 0.f };
	}

	if (m_tInfo.vPos.x != m_WayPoint.x)
	{
		if (m_tInfo.vPos.x > m_WayPoint.x)
		{
			m_tInfo.vPos.x -= 1;
		}
		else if (m_tInfo.vPos.x < m_WayPoint.x)
		{
			m_tInfo.vPos.x += 1;
		}
	}
	if (m_tInfo.vPos.y != m_WayPoint.y)
	{
		if (m_tInfo.vPos.y > m_WayPoint.y)
		{
			m_tInfo.vPos.y -= 1;
		}
		else if (m_tInfo.vPos.y < m_WayPoint.y)
		{
			m_tInfo.vPos.y += 1;
		}

	}

	if ((m_tInfo.vPos.x != m_WayPoint.x) || (m_tInfo.vPos.y != m_WayPoint.y))
		return true;

	else if ((m_tInfo.vPos.x == m_WayPoint.x) && (m_tInfo.vPos.y == m_WayPoint.y))
		return false;
}

