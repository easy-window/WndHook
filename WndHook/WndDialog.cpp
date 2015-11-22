#include "StdAfx.h"
#include "WndDialog.h"

using namespace WndHook;


CWndDialog::CWndDialog(void) 
	: CWndBase()
{
}

CWndDialog::~CWndDialog(void)
{
}

CWndDialog::CWndDialog(HWND hWnd) 
	: CWndBase(hWnd)
{

}

CWndDialog::CWndDialog(CWnd* pWnd) 
	: CWndBase(pWnd)
{
}

bool CWndDialog::MaxSize()
{
	if(NULL == m_hWnd) return false;
	::SendMessage(m_hWnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
	return true;
}

bool CWndDialog::MinSize()
{
	if(NULL == m_hWnd) return false;
	::SendMessage(m_hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
	return true;
}

bool CWndDialog::Restore()
{
	if(NULL == m_hWnd) return false;
	::SendMessage(m_hWnd, WM_SYSCOMMAND, SC_RESTORE, 0);
	return true;
}

bool CWndDialog::Close()
{
	if(NULL == m_hWnd) return false;
	::SendMessage(m_hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
	return true;
}

bool CWndDialog::MoveTo(CPoint pt)
{
	if(NULL == m_hWnd) return false;
	return GetWindow()->SetWindowPos(NULL, pt.x, pt.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE) == TRUE;
}
