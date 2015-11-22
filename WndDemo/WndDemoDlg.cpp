// WndDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WndDemo.h"
#include "WndDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWndDemoDlg dialog
using namespace WndHook;



CWndDemoDlg::CWndDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWndDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWndDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWndDemoDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_EDT_GETTEXT, &CWndDemoDlg::OnBnClickedBtnEdtGettext)
	ON_BN_CLICKED(IDC_BTN_GETDIALOG, &CWndDemoDlg::OnBnClickedBtnGetdialog)
	ON_BN_CLICKED(IDC_BTN_GETEDIT, &CWndDemoDlg::OnBnClickedBtnGetedit)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_DLG_MIN, &CWndDemoDlg::OnBnClickedBtnDlgMin)
	ON_BN_CLICKED(IDC_BTN_DLG_MAX, &CWndDemoDlg::OnBnClickedBtnDlgMax)
	ON_BN_CLICKED(IDC_BTN_DLG_RESTORE, &CWndDemoDlg::OnBnClickedBtnDlgRestore)
	ON_BN_CLICKED(IDC_BTN_DLG_CLOSE, &CWndDemoDlg::OnBnClickedBtnDlgClose)
	ON_BN_CLICKED(IDC_BTN_EDT_SETTEXT, &CWndDemoDlg::OnBnClickedBtnEdtSettext)
	ON_BN_CLICKED(IDC_BTN_PASTE, &CWndDemoDlg::OnBnClickedBtnPaste)
	ON_BN_CLICKED(IDC_BTN_READONLY, &CWndDemoDlg::OnBnClickedBtnReadonly)
	ON_BN_CLICKED(IDC_BTN_EDT_SELECT, &CWndDemoDlg::OnBnClickedBtnEdtSelect)
END_MESSAGE_MAP()


// CWndDemoDlg message handlers

BOOL CWndDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWndDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWndDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CWndDemoDlg::OnBnClickedBtnGetdialog()
{
	m_dlgHook.Init(::FindWindow(NULL, _T("Test")));
}

void CWndDemoDlg::OnBnClickedBtnGetedit()
{
	CString sText;
	((CEdit*)GetDlgItem(IDC_EDIT_INDEX))->GetWindowText(sText);
	m_editHook.Init(m_dlgHook.GetChild(_ttoi(sText), NULL, _T("Edit"), NULL));
}

void CWndDemoDlg::OnBnClickedBtnDlgMin()
{
	m_dlgHook.MinSize();
}

void CWndDemoDlg::OnBnClickedBtnDlgMax()
{
	m_dlgHook.MaxSize();
}

void CWndDemoDlg::OnBnClickedBtnDlgRestore()
{
	m_dlgHook.Restore();
}

void CWndDemoDlg::OnBnClickedBtnDlgClose()
{
	m_dlgHook.Close();
}

void CWndDemoDlg::OnBnClickedBtnEdtGettext()
{
	TCHAR szText[1024];
	int nLen = 1024;
	if(m_editHook.GetText(szText, nLen))
		AfxMessageBox(szText);
}
void CWndDemoDlg::OnBnClickedBtnEdtSettext()
{
	CString sText;
	((CEdit*)GetDlgItem(IDC_EDIT_TEXT))->GetWindowText(sText);
	m_editHook.SetText(sText.GetBuffer());
	sText.ReleaseBuffer();
}

void CWndDemoDlg::OnBnClickedBtnPaste()
{
	CString sText;
	((CEdit*)GetDlgItem(IDC_EDIT_TEXT))->GetWindowText(sText);
	m_editHook.PasteTo(sText.GetBuffer());
	sText.ReleaseBuffer();
}

void CWndDemoDlg::OnBnClickedBtnReadonly()
{
	m_editHook.ReadOnly(!m_editHook.IsReadOnly());
}

void CWndDemoDlg::OnBnClickedBtnEdtSelect()
{
	CString sBegin, sEnd;
	((CEdit*)GetDlgItem(IDC_EDIT_BEGIN))->GetWindowText(sBegin);
	((CEdit*)GetDlgItem(IDC_EDIT_END))->GetWindowText(sEnd);
	m_editHook.SetSelect(_ttoi(sBegin), _ttoi(sEnd));
}
