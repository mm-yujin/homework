// MyForm.cpp: 구현 파일
//

#include "pch.h"
#include "230725 Tool_homework.h"
#include "MyForm.h"


// CMyForm

IMPLEMENT_DYNCREATE(CMyForm, CFormView)

CMyForm::CMyForm()
	: CFormView(IDD_CMyForm)
{

}

CMyForm::~CMyForm()
{
}

void CMyForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyForm, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CMyForm::OnUnitTool)
	ON_BN_CLICKED(IDC_BUTTON2, &CMyForm::OnMapTool)
END_MESSAGE_MAP()


// CMyForm 진단

#ifdef _DEBUG
void CMyForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMyForm 메시지 처리기

void CMyForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// CreatePointFont(폰트 크기, 글씨체)
	m_pFont.CreatePointFont(100, L"바탕");

	GetDlgItem(IDC_BUTTON1)->SetFont(&m_pFont);
	GetDlgItem(IDC_BUTTON2)->SetFont(&m_pFont);
}


void CMyForm::OnUnitTool()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// GetSafeHwnd : 현재 다이얼로그의 윈도우 핸들을 반환, 핸들이 null이면 아직 생성되어 있지 않음을 의미

	if(nullptr == m_UnitTool.GetSafeHwnd())
		m_UnitTool.Create(IDD_CUnitTool);

	m_UnitTool.ShowWindow(SW_SHOW);
}




void CMyForm::OnMapTool()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (nullptr == m_MapTool.GetSafeHwnd())
		m_MapTool.Create(IDD_CMapTool);

	m_MapTool.ShowWindow(SW_SHOW);
}
