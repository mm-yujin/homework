﻿// MapTool.cpp: 구현 파일
//

#include "pch.h"
#include "230725 Tool_homework.h"
#include "MapTool.h"
#include "afxdialogex.h"


// CMapTool 대화 상자

IMPLEMENT_DYNAMIC(CMapTool, CDialog)

CMapTool::CMapTool(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CMapTool, pParent)
{

}

CMapTool::~CMapTool()
{
}

void CMapTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMapTool, CDialog)
END_MESSAGE_MAP()


// CMapTool 메시지 처리기
