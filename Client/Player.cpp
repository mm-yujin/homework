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
		MessageBox(g_hWnd, L"IMG FAILED", L"주의", MB_OK);

	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Stage/Player/Stand/AKIHA_AKI00_00%d.png", TEX_MULTI, L"Player_S", L"Stand", 12)))
		MessageBox(g_hWnd, L"IMG FAILED", L"주의", MB_OK);

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
			m_tInfo.vPos.x + iScrollX,	// x축으로 스크롤 값
			m_tInfo.vPos.y + iScrollY,	// y축으로 스크롤 값
			m_tInfo.vPos.z);

		matWorld = matScale * matTrans;

		if (Move_Player())
		{
			
			float	fX = pTexInfo->tImgInfo.Width / 2.f;
			float	fY = pTexInfo->tImgInfo.Height * 0.8f;

			CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

			CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, // 출력할 이미지 컴객체
				nullptr, // 출력할 이미지 영역에 대한 RECT구조체 포인터, NULL인 경우 이미지의 0,0 기준으로 출력
				&D3DXVECTOR3(fX, fY, 0.f), // 출력할 이미지의 중심 축에 대한 VEC3 구조체 포인터, NULL인 경우 0, 0이 중심 좌표
				nullptr, // 위치 좌표에 대한 VEC3구조체 포인터, NULL인 경우 스크린 상 0, 0 좌표 출력
				D3DCOLOR_ARGB(255, 255, 255, 255));// 출력할 원본 이미지와 섞을 색상 값, 출력 시 섞은 색상이 반영(0xffffffff를 넘겨주면 원본 색상 유지)

		}
		else if (!Move_Player())
		{
			float	fX = pTexInfo2->tImgInfo.Width / 2.f;
			float	fY = pTexInfo2->tImgInfo.Height * 0.8f;

			CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

			CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo2->pTexture, // 출력할 이미지 컴객체
				nullptr, // 출력할 이미지 영역에 대한 RECT구조체 포인터, NULL인 경우 이미지의 0,0 기준으로 출력
				&D3DXVECTOR3(fX, fY, 0.f), // 출력할 이미지의 중심 축에 대한 VEC3 구조체 포인터, NULL인 경우 0, 0이 중심 좌표
				nullptr, // 위치 좌표에 대한 VEC3구조체 포인터, NULL인 경우 스크린 상 0, 0 좌표 출력
				D3DCOLOR_ARGB(255, 255, 255, 255));// 출력할 원본 이미지와 섞을 색상 값, 출력 시 섞은 색상이 반영(0xffffffff를 넘겨주면 원본 색상 유지)

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

