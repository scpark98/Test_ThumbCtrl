﻿
// Test_ThumbCtrlDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Test_ThumbCtrl.h"
#include "Test_ThumbCtrlDlg.h"
#include "afxdialogex.h"

#include "Functions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTestThumbCtrlDlg 대화 상자



CTestThumbCtrlDlg::CTestThumbCtrlDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TEST_THUMBCTRL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestThumbCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestThumbCtrlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CTestThumbCtrlDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTestThumbCtrlDlg::OnBnClickedCancel)
	ON_WM_SIZE()
	ON_WM_WINDOWPOSCHANGED()
	ON_WM_DROPFILES()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CTestThumbCtrlDlg 메시지 처리기

BOOL CTestThumbCtrlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	m_thumb.create(this);
	m_thumb.set_color_theme(CSCColorTheme::color_theme_dark_gray);
	m_thumb.set_font_size(12);

	RestoreWindowPosition(&theApp, this);

	SetTimer(timer_load_files, 100, NULL);

	DragAcceptFiles();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CTestThumbCtrlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CTestThumbCtrlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CTestThumbCtrlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTestThumbCtrlDlg::OnBnClickedOk()
{
	m_thumb.m_thumb[5].score = 5.0f;
	m_thumb.sort_by_title();
	m_thumb.sort_by_info(0);
	m_thumb.sort_by_score();


	CGdiplusBitmap img = m_thumb.m_thumb[5].img;
	m_thumb.m_thumb[5].img.deep_copy(&img);
}

void CTestThumbCtrlDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}

void CTestThumbCtrlDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (m_thumb.m_hWnd == NULL)
		return;

	CRect rc;
	GetClientRect(rc);
	m_thumb.MoveWindow(rc);
}

void CTestThumbCtrlDlg::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	CDialogEx::OnWindowPosChanged(lpwndpos);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	SaveWindowPosition(&theApp, this);
}

void CTestThumbCtrlDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	TCHAR sfile[MAX_PATH] = { 0, };
	CString folder;

	DragQueryFile(hDropInfo, 0, sfile, MAX_PATH);

	if (PathIsDirectory(sfile))
		folder = sfile;
	else
		folder = get_part(sfile, fn_folder);

	m_thumb.set_path(folder);
	theApp.WriteProfileString(_T("setting"), _T("recent folder"), folder);

	CDialogEx::OnDropFiles(hDropInfo);
}

void CTestThumbCtrlDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDEvent == timer_load_files)
	{
		KillTimer(timer_load_files);

		CString recent_folder = theApp.GetProfileString(_T("setting"), _T("recent folder"), _T(""));
		//CString recent_folder = _T("Z:\\내 드라이브\\media\\test_image\\CGdiplusBitmap effects");
		m_thumb.set_path(recent_folder);

		//std::deque<CString> thumb_files;
		//FindAllFiles(_T("G:\\model_faces"), &thumb_files, _T("*"), FILE_EXTENSION_IMAGE);
		//m_thumb.set_path(_T("G:\\model_faces"));
	}

	CDialogEx::OnTimer(nIDEvent);
}
