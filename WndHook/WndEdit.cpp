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
	if(NULL == m_hWnd) return;
	CWndTool::CopytoTheClipboard(CString(szText), m_hWnd);
	((CEdit*)GetWindow())->Paste();
}

bool CWndEdit::ReadOnly(bool bReadOnly)
{
	if(NULL == m_hWnd) return false;
	return ((CEdit*)GetWindow())->SetReadOnly(bReadOnly ? TRUE :FALSE) == TRUE;
}

bool CWndEdit::IsReadOnly()
{
	if(NULL == m_hWnd) return false;
	return (::GetWindowLong(m_hWnd, GWL_STYLE) & ES_READONLY) != 0;
}

bool CWndEdit::GetText(TCHAR* szText, int& nMaxLen)
{
	if(NULL == m_hWnd) return false;
	LONG dwStyle = ::GetWindowLong(m_hWnd, GWL_STYLE);			// ��ȡ�༭��ԭ����ʽ
	::SetWindowWord(m_hWnd, GWL_STYLE, 0);						// ȡ��������ʽ
	::SetWindowLong(m_hWnd, GWL_STYLE, dwStyle & ~ES_PASSWORD);	// ȥ����������(����еĻ�)
	bool bSuccess = CWndBase::GetText(szText, nMaxLen);
	::SetWindowLong(m_hWnd, GWL_STYLE, dwStyle);					//��ԭ�༭��ԭ����ʽ
	return bSuccess;
}
