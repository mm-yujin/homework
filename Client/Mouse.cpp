#include "stdafx.h"
#include "Mouse.h"
#include "Scroll.h"

CMouse::CMouse() : m_Point()
{
}

CMouse::~CMouse()
{
	Release();
}

HRESULT CMouse::Initialize(void)
{
    GetCursorPos(&m_Point);
    ScreenToClient(g_hWnd, &m_Point);
    m_tInfo.vPos = { (float)m_Point.x, (float)m_Point.y, 0.f };

	

    return E_NOTIMPL;
}

int CMouse::Update(void)
{
    OffSet();

    return 0;
}

void CMouse::Late_Update(void)
{
    GetCursorPos(&m_Point);
    ScreenToClient(g_hWnd, &m_Point);
    m_tInfo.vPos = { (float)m_Point.x, (float)m_Point.y, 0.f };

}

void CMouse::Render(void)
{ 
}

void CMouse::Release(void)
{
}

void CMouse::OffSet(void)
{
	int m_iSpeed = 2;

	float	iOffSetMinX = WINCX * 0.5f - 100; 		
	float	iOffSetMaxX = WINCX * 0.5f + 100;
	float	iOffSetMinY = WINCY * 0.5f - 100;		
	float	iOffSetMaxY = WINCY * 0.5f + 100;

	int	iScrollX = int(CScroll::Get_Instance()->Get_ScrollX());
	int	iScrollY = int(CScroll::Get_Instance()->Get_ScrollY());

	if ((m_tInfo.vPos.x < WINCX + 200) && (m_tInfo.vPos.x > -200)
		&& (m_tInfo.vPos.y < WINCY + 200) && (m_tInfo.vPos.y > -200))
	{

	if (iOffSetMinX > m_tInfo.vPos.x)
		CScroll::Get_Instance()->Set_ScrollX(m_iSpeed);

	if (iOffSetMaxX < m_tInfo.vPos.x)
		CScroll::Get_Instance()->Set_ScrollX(-m_iSpeed);

	if (iOffSetMinY > m_tInfo.vPos.y)
		CScroll::Get_Instance()->Set_ScrollY(m_iSpeed);

	if (iOffSetMaxY < m_tInfo.vPos.y)
		CScroll::Get_Instance()->Set_ScrollY(-m_iSpeed);

	}
}
