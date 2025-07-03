
// Test_ThumbCtrlDlg.h: 헤더 파일
//

#pragma once

#include "ThumbCtrl/SCThumbCtrl.h"

// CTestThumbCtrlDlg 대화 상자
class CTestThumbCtrlDlg : public CDialogEx
{
// 생성입니다.
public:
	CTestThumbCtrlDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEST_THUMBCTRL_DIALOG };
#endif

protected:
	CSCThumbCtrl	m_thumb;

	enum ENUM_TIMER_ID
	{
		timer_load_files = 0,
	};

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
