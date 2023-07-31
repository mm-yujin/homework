#pragma once

#include "afxwin.h"

#include "Include.h"

// CUnitTool 대화 상자

class CUnitTool : public CDialog
{
	DECLARE_DYNAMIC(CUnitTool)

public:
	CUnitTool(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CUnitTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CUnitTool };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedButton1();

	CString m_strTemp;
	CString m_strSrc;
	CString m_strName;
	int m_iHP;
	int m_iAttack;

public:



	map<CString, UNITDATA*>		m_mapUnitData;

	CListBox m_ListBox;
	CButton m_Radio[3];
	CButton m_Check[3];

	afx_msg void OnCreateUnit();
	afx_msg void OnListBox();
	afx_msg void OnSaveButton();
	afx_msg void OnLoadButton();
	afx_msg void OnSearchButton();
	afx_msg void OnDeleteButton();

	CString m_strSearch;
	bool bCheck;
};
