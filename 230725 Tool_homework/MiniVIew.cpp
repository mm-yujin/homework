// MiniVIew.cpp: 구현 파일
//

#include "pch.h"
#include "230725 Tool_homework.h"
#include "MiniVIew.h"

#include "Device.h"
#include "MainFrm.h"
#include "230725 Tool_homeworkView.h"

// CMiniVIew

IMPLEMENT_DYNCREATE(CMiniView, CView)

CMiniView::CMiniView()
{

}

CMiniView::~CMiniView()
{
}

BEGIN_MESSAGE_MAP(CMiniView, CView)
END_MESSAGE_MAP()


// CMiniVIew 그리기

void CMiniView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.


	// AfxGetApp : 메인 쓰레드를 갖고 있는 현재 메인 app을 반환
	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());

	//GetPane(행, 열) : 해당하는 창의 정보를 얻어오는 함수 
	CMy230725ToolhomeworkView* pMainView = dynamic_cast<CMy230725ToolhomeworkView*>(pMainFrm->m_MainSplitter.GetPane(0, 1));

	//GetParentFrame : 현재 View를 둘러 싸고 있는 FrameWnd를 반환
	//CMainFrame*		pMainFrm = dynamic_cast<CMainFrame*>(GetParentFrame());

	CTerrain* pTerrain = pMainView->m_pTerrain;

	CDevice::Get_Instance()->Render_Begin();


	pTerrain->Mini_Render();

	CDevice::Get_Instance()->Render_End(m_hWnd);

	Invalidate(FALSE);
}


// CMiniVIew 진단

#ifdef _DEBUG
void CMiniView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CMiniView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMiniVIew 메시지 처리기
