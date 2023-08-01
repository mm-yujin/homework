#include "stdafx.h"
#include "Scroll.h"


CScroll* CScroll::m_pInstance = nullptr;

CScroll::CScroll()
	: m_fScrollX(0.f), m_fScrollY(0.f)
{
}


CScroll::~CScroll()
{
}

void CScroll::Scroll_Lock()
{
	if (0.f < m_fScrollX)
		m_fScrollX = 0.f;

	if (0.f < m_fScrollY)
		m_fScrollY = 0.f;

	if (WINCX - (TILECX * TILEX) > m_fScrollX)
		m_fScrollX = WINCX - (TILECX * TILEX);

	if (WINCY - (TILECY * TILEY) > m_fScrollY)
		m_fScrollY = WINCY - (TILECY * TILEY);

}
