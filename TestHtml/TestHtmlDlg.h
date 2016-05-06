
// TestHtmlDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CTestHtmlDlg dialog
class CTestHtmlDlg : public CDialogEx
{
// Construction
public:
	CTestHtmlDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TESTHTML_DIALOG };
	void httpRequest();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CListBox m_listbox;
};
