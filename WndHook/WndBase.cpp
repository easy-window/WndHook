#include "StdAfx.h"
#include "WndBase.h"

using namespace WndHook;

CWndBase::CWndBase(void)
{
	Reset();
}

CWndBase::CWndBase(HWND hWnd)
{
	m_hWnd = hWnd;
}

CWndBase::CWndBase(CWnd* pWnd)
{
	Reset();
	m_hWnd = CWndTool::GetHandle(pWnd);
}

CWndBase::~CWndBase(void)
{
}

void CWndBase::Reset()
{
	m_hWnd = NULL;
}

CWnd* CWndBase::GetWindow()
{
	return CWndTool::GetWindow(m_hWnd);
}

HWND CWndBase::GetHandle()
{
	return m_hWnd;
}
	
HWND CWndBase::GetChild(unsigned int nIndex, HWND hWndChildAfter, CONST TCHAR* szClass, CONST TCHAR* szWindow)
{
	HWND hWnd = hWndChildAfter;
	for(unsigned int i = 0; i <= nIndex; i++)
	{
		hWnd = ::FindWindowEx(hWnd, hWndChildAfter, szClass, szWindow);
	}
	return hWnd;
}

HWND CWndBase::GetNext(bool bPrev)
{
	if(bPrev) return CWndTool::GetHandle(GetWindow()->GetNextWindow(GW_HWNDPREV));
	else  return CWndTool::GetHandle(GetWindow()->GetNextWindow(GW_HWNDNEXT));
}

CRect CWndBase::GetRect(RECT_TYPE nType)
{
	CRect rc;
	GetWindow()->GetClientRect(&rc);
	if (RECT_WINDOW == nType) GetWindow()->ClientToScreen(&rc);
	return rc;
}

bool CWndBase::IsVisible()
{
	return GetWindow()->IsWindowVisible() == TRUE;
}

bool CWndBase::IsEnabled()
{
	return GetWindow()->IsWindowEnabled() == TRUE;
}

bool CWndBase::Enable(bool bEnable)
{
	return GetWindow()->EnableWindow(bEnable ? TRUE : FALSE) == TRUE;
}

void CWndBase::SetPosTop(bool bAlway)
{
	if(bAlway)
	{
		GetWindow()->SetWindowPos(&CWnd::wndTopMost, 0, 0 , 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	}
	else
	{
		GetWindow()->SetForegroundWindow();
	}
}

bool CWndBase::GetText(TCHAR* szText, int& nMaxCount)
{
	int nTextLen = ::SendMessage(m_hWnd, WM_GETTEXTLENGTH, 0, 0);
	if(nMaxCount < nTextLen)
	{
		nMaxCount = nTextLen;
		return false;
	}

	nMaxCount = ::SendMessage(m_hWnd, WM_GETTEXT, (WPARAM)nMaxCount, (LPARAM)szText);

	return nMaxCount >= 0;
}

void CWndBase::SetText(TCHAR* szText)
{
	::SendMessage(m_hWnd, WM_SETTEXT, 0, (LPARAM)szText);
}

int CWndBase::GetTextLength()
{
	return ::SendMessage(m_hWnd, WM_GETTEXTLENGTH, 0, 0);
}
