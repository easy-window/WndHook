#include "StdAfx.h"
#include "WndEdit.h"

using namespace WndHook;


CWndEdit::CWndEdit(void) 
	: CWndBase()
{
}

CWndEdit::~CWndEdit(void)
{
}

CWndEdit::CWndEdit(HWND hWnd) 
	: CWndBase(hWnd)
{

}

CWndEdit::CWndEdit(CWnd* pWnd) 
	: CWndBase(pWnd)
{
}

void CWndEdit::PasteTo(TCHAR* szText)
{
	CWndTool::CopytoTheClipboard(CString(szText), m_hWnd);
	((CEdit*)GetWindow())->Paste();
}

bool CWndEdit::ReadOnly(bool bReadOnly)
{
	return ((CEdit*)GetWindow())->SetReadOnly(bReadOnly ? TRUE :FALSE) == TRUE;
}

bool CWndEdit::GetText(TCHAR* szText, int& nMaxLen)
{
	LONG dwStyle = GetWindowLong(m_hWnd, GWL_STYLE);			// ��ȡ�༭��ԭ����ʽ
	SetWindowWord(m_hWnd, GWL_STYLE, 0);						// ȡ��������ʽ
	SetWindowLong(m_hWnd, GWL_STYLE, dwStyle & ~ES_PASSWORD);	// ȥ����������(����еĻ�)
	bool bSuccess = CWndBase::GetText(szText, nMaxLen);
	SetWindowLong(m_hWnd, GWL_STYLE, dwStyle);					//��ԭ�༭��ԭ����ʽ
	return bSuccess;
}
