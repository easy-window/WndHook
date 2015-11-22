// WndDemoDlg.h : header file
//

#pragma once


// CWndDemoDlg dialog
class CWndDemoDlg : public CDialog
{
// Construction
public:
	CWndDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_WNDDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedBtnGetdialog();
	afx_msg void OnBnClickedBtnGetedit();
	afx_msg void OnBnClickedBtnEdtGettext();
	DECLARE_MESSAGE_MAP()

public:
	CWndDialog m_dlgHook;
	CWndEdit m_editHook;
	afx_msg void OnBnClickedBtnDlgMin();
	afx_msg void OnBnClickedBtnDlgMax();
	afx_msg void OnBnClickedBtnDlgRestore();
	afx_msg void OnBnClickedBtnDlgClose();
	afx_msg void OnBnClickedBtnEdtSettext();
	afx_msg void OnBnClickedBtnPaste();
	afx_msg void OnBnClickedBtnReadonly();
};
