#pragma once

#include "Include.h"

class CScroll
{
private:
	CScroll();
	~CScroll();

public:
	static CScroll* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CScroll;
		}

		return m_pInstance;
	}
	static void		Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

public:
	float		Get_ScrollX() { return m_fScrollX; }
	float		Get_ScrollY() { return m_fScrollY; }

	void		Set_ScrollX(float _fX) { m_fScrollX += _fX; }
	void		Set_ScrollY(float _fY) { m_fScrollY += _fY; }

	void		Setting_first_ScrollX(void) { m_fScrollX = 0; }
	void		Setting_first_ScrollY(void) { m_fScrollY = 0; }

	void		Setting_first_ScrollX_ver(float _fX) { m_fScrollX = _fX; }
	void		Setting_first_ScrollY_ver(float _fY) { m_fScrollY = _fY; }

	void		Scroll_Lock();

private:
	static CScroll*			m_pInstance;

	float					m_fScrollX;
	float					m_fScrollY;

};
