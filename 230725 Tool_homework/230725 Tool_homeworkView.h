
// 230725 Tool_homeworkView.h: CMy230725ToolhomeworkView 클래스의 인터페이스
//

#pragma once

#include "Device.h"
#include "Terrain.h"

//#include "TextureMgr.h"

class CMy230725ToolhomeworkDoc;


class CMy230725ToolhomeworkView : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	CMy230725ToolhomeworkView() noexcept;
	DECLARE_DYNCREATE(CMy230725ToolhomeworkView)

// 특성입니다.
public:
	CMy230725ToolhomeworkDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMy230725ToolhomeworkView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

public:
	CTerrain* m_pTerrain = nullptr;

public:
	
};

#ifndef _DEBUG  // 230725 Tool_homeworkView.cpp의 디버그 버전
inline CMy230725ToolhomeworkDoc* CMy230725ToolhomeworkView::GetDocument() const
   { return reinterpret_cast<CMy230725ToolhomeworkDoc*>(m_pDocument); }
#endif

