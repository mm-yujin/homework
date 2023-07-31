
// 230725 Tool_homeworkView.cpp: CMy230725ToolhomeworkView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "230725 Tool_homework.h"
#endif

#include "230725 Tool_homeworkDoc.h"
#include "230725 Tool_homeworkView.h"

#include "TextureMgr.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HWND	g_hWnd;


// CMy230725ToolhomeworkView

IMPLEMENT_DYNCREATE(CMy230725ToolhomeworkView, CScrollView)

BEGIN_MESSAGE_MAP(CMy230725ToolhomeworkView, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CMy230725ToolhomeworkView 생성/소멸

CMy230725ToolhomeworkView::CMy230725ToolhomeworkView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMy230725ToolhomeworkView::~CMy230725ToolhomeworkView()
{
}


#pragma region 생략

BOOL CMy230725ToolhomeworkView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CMy230725ToolhomeworkView 인쇄

BOOL CMy230725ToolhomeworkView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMy230725ToolhomeworkView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMy230725ToolhomeworkView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMy230725ToolhomeworkView 진단

#ifdef _DEBUG
void CMy230725ToolhomeworkView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMy230725ToolhomeworkView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMy230725ToolhomeworkDoc* CMy230725ToolhomeworkView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy230725ToolhomeworkDoc)));
	return (CMy230725ToolhomeworkDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy230725ToolhomeworkView 메시지 처리기


#pragma endregion 생략


void CMy230725ToolhomeworkView::OnInitialUpdate()
{
	//Scrollview라서 스크롤이 없으면 프로그램이 터짐. 그래서 SetScroll을 해줘야만 이상없이 수행됨
	//타일 갯수 * 타일 사이즈 만큼의 길이를 스크롤로 만들기
	SetScrollSizes(MM_TEXT, CSize(TILEX * TILECX, TILEY * TILECY / 2));
	//여기까지 하면 스크롤바는 생기고 작동은 안 됨. DC가 아닌 Device에 적용되도록 바꿔야 작동됨

	// AfxGetMainWnd : 현재 메인 윈도우를 반환하는 전역 함수

	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();


	RECT	rcWnd{};

	// GetWindowRect : 현재 윈도우의 렉트 정보를 얻어와 기록하는 함수
	pMainFrm->GetWindowRect(&rcWnd);

	// SetRect : 지정한 매개 변수대로 렉트 정보를 기록하는 함수
	SetRect(&rcWnd, 0, 0, rcWnd.right - rcWnd.left, rcWnd.bottom - rcWnd.top);



	RECT	rcMainView{};

	// GetClientRect : 현재 view 창의 렉트 정보를 얻어오는 함수
	GetClientRect(&rcMainView);

	float	fRowFrm = float(rcWnd.right - rcMainView.right);
	float	fColFrm = float(rcWnd.bottom - rcMainView.bottom);

	// SetWindowPos : 매개 변수 대로 새롭게 윈도우의 위치와 크기를 조정하는 함수
	// SetWindowPos(배치할 윈도우의 z순서, x좌표, y좌표, 가로 크기, 세로 크릭, 배치할 윈도우의 크기 및 위지 지정(현재 순서를 유지하겠다는 옵션))

	pMainFrm->SetWindowPos(nullptr, 0, 0, int(WINCX + fRowFrm), int(WINCY + fColFrm), SWP_NOZORDER);

	CScrollView::OnInitialUpdate();

	g_hWnd = m_hWnd;

	if (FAILED(CDevice::Get_Instance()->Initialize()))
		AfxMessageBox(L"CDevice Initialize FAILED");


	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Cube.png", TEX_SINGLE, L"Cube")))
		AfxMessageBox(L"CUBE IMG FAILED");

	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Stage/Terrain/Tile/Tile%d.png", TEX_MULTI, L"Terrain", L"Tile", 36)))
		AfxMessageBox(L"TILE IMG FAILED");


	m_pTerrain = new CTerrain;
	m_pTerrain->Initialize();
	m_pTerrain->Set_MainView(this);

}



// CMy230725ToolhomeworkView 그리기

void CMy230725ToolhomeworkView::OnDraw(CDC* /*pDC*/)
{
	CMy230725ToolhomeworkDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

#pragma region 생략2
	//const TEXINFO* pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"Terrain", L"Tile", 3);
	//D3DXMATRIX	matWorld, matScale, matRotZ, matTrans;

	//D3DXMatrixIdentity(&matWorld);
	//D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	//D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(45.f));
	//D3DXMatrixTranslation(&matTrans, 400.f, 300.f, 0.f);  //타일 중점좌표

	//matWorld = matScale/* * matRotZ*/ * matTrans;

	//float		fCenterX = pTexInfo->tImgInfo.Width / 2.f;
	//float		fCenterY = pTexInfo->tImgInfo.Height / 2.f;

	//CDevice::Get_Instance()->Render_Begin();

	//CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

	//CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,	// 텍스처 객체 주소
	//	nullptr, // 출력할 이미지 영역에 대한 렉트 구조체 주소, null인경우 이미지의 0, 0기준으로 출력
	//	&D3DXVECTOR3(fCenterX, fCenterY, 0.f), // 출력할 이미지의 중심 축에 대한 vector3 구조체 포인터, nullptr인 경우 0, 0이 중심 좌표
	//	nullptr, // 위치 좌표에 따른 vector3 구조체 포인어
	//	D3DCOLOR_ARGB(255, 255, 255, 255));	// 출력할 원본 이미지와 섞을 색상 값, 출력 시 섞은 색이 반영, 0xffffffff를 넘겨주면 원본 색상 유지

#pragma endregion 생략2
	

	CDevice::Get_Instance()->Render_Begin();



	m_pTerrain->Render();


	CDevice::Get_Instance()->Render_End();
}

void CMy230725ToolhomeworkView::OnDestroy()
{
	CScrollView::OnDestroy();

	Safe_Delete(m_pTerrain);

	CTextureMgr::Destroy_Instance();
	CDevice::Get_Instance()->Destroy_Instance();
}


void CMy230725ToolhomeworkView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CScrollView::OnLButtonDown(nFlags, point);

	m_pTerrain->Tile_Change(D3DXVECTOR3((float)point.x + GetScrollPos(0), (float)point.y + GetScrollPos(1), 0.f), 0);
	Invalidate(FALSE);
}
