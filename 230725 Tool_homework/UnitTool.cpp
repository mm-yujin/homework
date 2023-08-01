// UnitTool.cpp: 구현 파일
//

#include "pch.h"
#include "230725 Tool_homework.h"
#include "UnitTool.h"
#include "afxdialogex.h"


// CUnitTool 대화 상자

IMPLEMENT_DYNAMIC(CUnitTool, CDialog)

CUnitTool::CUnitTool(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CUnitTool, pParent)
	, m_strTemp(_T(""))
	, m_strSrc(_T(""))
	, m_strName(_T(""))
	, m_iHP(0)
	, m_iAttack(0)
	, m_strSearch(_T(""))
	, bCheck(false)
{

}

CUnitTool::~CUnitTool()
{
	for_each(m_mapUnitData.begin(), m_mapUnitData.end(), CDeleteMap());
	m_mapUnitData.clear();
}

void CUnitTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, m_strTemp);
	DDX_Text(pDX, IDC_EDIT2, m_strSrc);
	DDX_Text(pDX, IDC_EDIT4, m_strName);
	DDX_Text(pDX, IDC_EDIT5, m_iHP);
	DDX_Text(pDX, IDC_EDIT6, m_iAttack);
	DDX_Control(pDX, IDC_LIST3, m_ListBox);
	DDX_Control(pDX, IDC_RADIO1, m_Radio[0]);
	DDX_Control(pDX, IDC_RADIO2, m_Radio[1]);
	DDX_Control(pDX, IDC_RADIO3, m_Radio[2]);
	DDX_Control(pDX, IDC_CHECK1, m_Check[0]);
	DDX_Control(pDX, IDC_CHECK2, m_Check[1]);
	DDX_Control(pDX, IDC_CHECK3, m_Check[2]);
	DDX_Text(pDX, IDC_EDIT7, m_strSearch);
}


BEGIN_MESSAGE_MAP(CUnitTool, CDialog)
	
	ON_BN_CLICKED(IDC_BUTTON1, &CUnitTool::OnBnClickedButton1)


	ON_BN_CLICKED(IDC_BUTTON2, &CUnitTool::OnCreateUnit)
	ON_LBN_SELCHANGE(IDC_LIST3, &CUnitTool::OnListBox)
	ON_BN_CLICKED(IDC_BUTTON3, &CUnitTool::OnSaveButton)
	ON_BN_CLICKED(IDC_BUTTON4, &CUnitTool::OnLoadButton)
	ON_BN_CLICKED(IDC_BUTTON5, &CUnitTool::OnSearchButton)
	ON_BN_CLICKED(IDC_BUTTON6, &CUnitTool::OnDeleteButton)
END_MESSAGE_MAP()


// CUnitTool 메시지 처리기



void CUnitTool::OnBnClickedButton1() //COPY
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	m_strSrc = m_strTemp;

	UpdateData(FALSE);
}


void CUnitTool::OnCreateUnit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	UNITDATA* pUnit = new UNITDATA;

	pUnit->strName = m_strName;
	pUnit->iHp = m_iHP;
	pUnit->iAttack = m_iAttack;

	for (int i = 0; i < 3; ++i)
	{
		if (m_Radio[i].GetCheck())
		{
			pUnit->byJobIndex = i;
			break;
		}
	}

	pUnit->byItem = 0x00;

	if (m_Check[0].GetCheck())
		pUnit->byItem |= RUBY;

	if (m_Check[1].GetCheck())
		pUnit->byItem |= TOPAZ;

	if (m_Check[2].GetCheck())
		pUnit->byItem |= SAPPHIRE;



	// AddString : 리스트 박스에 문자열을 추가
	m_ListBox.AddString(pUnit->strName);

	m_mapUnitData.insert({ pUnit->strName, pUnit });

	m_strName = L"";
	m_iHP = 0;
	m_iAttack = 0;

	for (int i = 0; i < 3; ++i)
	{
		m_Radio[i].SetCheck(FALSE);
		m_Check[i].SetCheck(FALSE);
	}

	UpdateData(FALSE);

}


void CUnitTool::OnListBox()
{
	UpdateData(TRUE);

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString		strFindName;

	//GetCurSel : 리스트 박스에서 선택한 목록의 인덱스를 반환
	int		iIndex = m_ListBox.GetCurSel();

	if (LB_ERR == iIndex)
		return;

	// GetText : 해당 인덱스의 문자열을 얻어오는 함수
	m_ListBox.GetText(iIndex, strFindName);

	auto		iter = m_mapUnitData.find(strFindName);

	if (iter == m_mapUnitData.end())
		return;

	m_strName = iter->second->strName;
	m_iHP = iter->second->iHp;
	m_iAttack = iter->second->iAttack;

	for (int i = 0; i < 3; ++i)
	{
		m_Radio[i].SetCheck(FALSE);
		m_Check[i].SetCheck(FALSE);
	}


	m_Radio[iter->second->byJobIndex].SetCheck(TRUE);

	if (iter->second->byItem & RUBY)
		m_Check[0].SetCheck(TRUE);

	if (iter->second->byItem & TOPAZ)
		m_Check[1].SetCheck(TRUE);

	if (iter->second->byItem & SAPPHIRE)
		m_Check[2].SetCheck(TRUE);


	UpdateData(FALSE);

}


void CUnitTool::OnSaveButton()
{
	UpdateData(TRUE);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.


	//string stri = "Test";
	//WriteFile.write(stri.c_str(), stri.size());

	//const size_t size = m_mapUnitData.size();

	//ofstream WriteFile;
	//WriteFile.open("Test.txt");

	//int iNumber = 0;
	//string str[100];

	//for (auto& iter = m_mapUnitData.begin(); iter != m_mapUnitData.end(); ++iter)
	//{
	//	str[iNumber] = string(CT2CA(iter->second->strName));
	//	str[iNumber + 1] = string(to_string(iter->second->iHp));
	//	str[iNumber + 2] = string(to_string(iter->second->iAttack));
	//	str[iNumber + 3] = string(to_string(iter->second->byJobIndex));
	//	str[iNumber + 4] = string(to_string(iter->second->byItem));

	//	iNumber += 5;
	//}

	//for (int j = 0; j < iNumber; ++j)
	//{
	//WriteFile.write(str[iNumber].c_str(), str[iNumber].size());
	//}

	//WriteFile.close();

	//다른 이름으로 저장하거나 열기 할 '창' 생성하는 코드 CFileDialog
	CFileDialog Dlg(FALSE,	L"dat",	L"*.dat", OFN_OVERWRITEPROMPT, L"Data File(*.dat) | *.dat||",	this);

	TCHAR szPath[MAX_PATH] = L"";
	GetCurrentDirectory(MAX_PATH, szPath);
	PathRemoveFileSpec(szPath);
	lstrcat(szPath, L"\\Data");
	Dlg.m_ofn.lpstrInitialDir = szPath;
	
	if (Dlg.DoModal())  //모달 방식은 메시지 발생을 점유한다는 것(다른 부분 안눌러지거나 하는 거 )
	{
		CString wstrFilePath = Dlg.GetPathName();
		HANDLE hFile = CreateFile(wstrFilePath.GetString(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (INVALID_HANDLE_VALUE == hFile)
		{
			ERR_MSG(L"파일 개방 실패");
			return;
		}
		DWORD dwByte = 0;
		DWORD dwStringSize = 0;
		for (auto& rPair : m_mapUnitData)
		{
			dwStringSize = sizeof(wchar_t) * (rPair.second->strName.GetLength() + 1);
			WriteFile(hFile, &dwStringSize, sizeof(DWORD), &dwByte, nullptr);
			WriteFile(hFile, rPair.second->strName.GetString(), dwStringSize, &dwByte, nullptr);
			WriteFile(hFile, &rPair.second->iHp, sizeof(int), &dwByte, nullptr);
			WriteFile(hFile, &rPair.second->iAttack, sizeof(int), &dwByte, nullptr);
			WriteFile(hFile, &rPair.second->byJobIndex, sizeof(BYTE), &dwByte, nullptr);
			WriteFile(hFile, &rPair.second->byItem, sizeof(BYTE), &dwByte, nullptr);
		}

		CloseHandle(hFile);
	}


	m_ListBox.ResetContent();
	

	UpdateData(FALSE);

}


void CUnitTool::OnLoadButton()
{
	UpdateData(TRUE);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	//ifstream readFile;
	//readFile.open("Test.txt");    //파일 열기

	//if (readFile.is_open())
	//{
	//	//readFile.seekg(0, std::ios::end);
	//	//size_t size = readFile.tellg();
	//	readFile.seekg(0, std::ios::beg);

	//	while (!readFile.eof())
	//	{
	//		string str;
	//		getline(readFile, str);
	//	}
	//	AfxMessageBox(L"READ OK");
	//	readFile.close();    //파일 닫기
	//}

	for (auto& rPair : m_mapUnitData)
		Safe_Delete(rPair.second);
	m_mapUnitData.clear();
	m_ListBox.ResetContent();

	CFileDialog Dlg(TRUE, L"dat", L"*.dat", OFN_OVERWRITEPROMPT, L"Data File(*.dat) | *.dat||", this);

	TCHAR szPath[MAX_PATH] = L"";
	GetCurrentDirectory(MAX_PATH, szPath);
	PathRemoveFileSpec(szPath);
	lstrcat(szPath, L"\\Data");
	Dlg.m_ofn.lpstrInitialDir = szPath;

	if (Dlg.DoModal())
	{
		CString wstrFilePath = Dlg.GetPathName();
		HANDLE hFile = CreateFile(wstrFilePath.GetString(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (INVALID_HANDLE_VALUE == hFile)
		{
			ERR_MSG(L"파일 개방 실패.");
			return;
		}
		DWORD dwByte = 0;
		DWORD dwStringSize = 0;
		UNITDATA* pUnitInfo = nullptr;
		while (true)
		{
			pUnitInfo = new UNITDATA;
			ReadFile(hFile, &dwStringSize, sizeof(DWORD), &dwByte, nullptr);
			TCHAR* pTemp = new TCHAR[dwStringSize];
			ReadFile(hFile, pTemp, dwStringSize, &dwByte, nullptr);
			ReadFile(hFile, &pUnitInfo->iHp, sizeof(int), &dwByte, nullptr);
			ReadFile(hFile, &pUnitInfo->iAttack, sizeof(int), &dwByte, nullptr);
			ReadFile(hFile, &pUnitInfo->byJobIndex, sizeof(BYTE), &dwByte, nullptr);
			ReadFile(hFile, &pUnitInfo->byItem, sizeof(BYTE), &dwByte, nullptr);

			if (0 == dwByte)
			{
				Safe_Delete(pUnitInfo);
				if (pTemp)
				{
					delete[] pTemp;
					pTemp = nullptr;
				}
				break;
			}
			pUnitInfo->strName = pTemp;
			m_mapUnitData.emplace(pUnitInfo->strName, pUnitInfo);
			m_ListBox.AddString(pUnitInfo->strName);
		}
		CloseHandle(hFile);
	}


	UpdateData(FALSE);
}




void CUnitTool::OnSearchButton()
{
	UpdateData(TRUE);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (m_strSearch == L"")
		AfxMessageBox(L"검색할 수 있는 값이 없습니다.", MB_OK | MB_SERVICE_NOTIFICATION);

	bCheck = false;
	for (auto iter = m_mapUnitData.begin(); iter != m_mapUnitData.end(); ++iter)
	{
		if (iter->second->strName == m_strSearch)
			bCheck = true;
	}

	if (bCheck == false) {
		AfxMessageBox(L"일치하는 값이 없습니다.", MB_OK | MB_SERVICE_NOTIFICATION);
	}

	else if (bCheck == true) {
		m_ListBox.SetCurSel(m_ListBox.FindString(-1, m_strSearch));

		CString		strFindName;

		//GetCurSel : 리스트 박스에서 선택한 목록의 인덱스를 반환
		int		iIndex = m_ListBox.GetCurSel();

		if (LB_ERR == iIndex)
			return;

		// GetText : 해당 인덱스의 문자열을 얻어오는 함수
		m_ListBox.GetText(iIndex, strFindName);

		auto		iter = m_mapUnitData.find(strFindName);

		if (iter == m_mapUnitData.end())
			return;

		m_strName = iter->second->strName;
		m_iHP = iter->second->iHp;
		m_iAttack = iter->second->iAttack;

		for (int i = 0; i < 3; ++i)
		{
			m_Radio[i].SetCheck(FALSE);
			m_Check[i].SetCheck(FALSE);
		}

		m_Radio[iter->second->byJobIndex].SetCheck(TRUE);

		if (iter->second->byItem & RUBY)
			m_Check[0].SetCheck(TRUE);

		if (iter->second->byItem & TOPAZ)
			m_Check[1].SetCheck(TRUE);

		if (iter->second->byItem & SAPPHIRE)
			m_Check[2].SetCheck(TRUE);

	}



	UpdateData(FALSE);
}


void CUnitTool::OnDeleteButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	if ((m_strSearch == L"") || (bCheck == false))
		AfxMessageBox(L"삭제할 수 있는 값이 없습니다.", MB_OK | MB_SERVICE_NOTIFICATION);

	if ((m_strSearch != L"") && (bCheck == true))
		m_ListBox.DeleteString(m_ListBox.FindString(-1, m_strSearch));

	m_strName = L"";
	m_iHP = 0;
	m_iAttack = 0;

	for (int i = 0; i < 3; ++i)
	{
		m_Radio[i].SetCheck(FALSE);
		m_Check[i].SetCheck(FALSE);
	}


	UpdateData(FALSE);

}
