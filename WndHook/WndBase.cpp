#include "StdAfx.h"
#include "WndBase.h"

using namespace WndHook;

CWndBase::CWndBase(void)
{
	Reset();
}

CWndBase::CWndBase(HWND hWnd)
{
	Init(hWnd);
}

CWndBase::CWndBase(CWnd* pWnd)
{
	Reset();
	Init(pWnd);
}

CWndBase::~CWndBase(void)
{
}

void CWndBase::Init(HWND hWnd)
{
	m_hWnd = hWnd;
}

void CWndBase::Init(CWnd* pWnd)
{
	m_hWnd = CWndTool::GetHandle(pWnd);
}

void CWndBase::Reset()
{
	m_hWnd = NULL;
}

CWnd* CWndBase::GetWindow()
{
	if(NULL == m_hWnd) return NULL;
	return CWndTool::GetWindow(m_hWnd);
}

HWND CWndBase::GetHandle()
{
	return m_hWnd;
}
	
HWND CWndBase::GetChild(unsigned int nIndex, HWND hWndChildAfter, CONST TCHAR* szClass, CONST TCHAR* szWindow)
{
	if(NULL == m_hWnd) return NULL;
	HWND hWnd = hWndChildAfter;
	for(unsigned int i = 0; i <= nIndex; i++)
	{
		hWnd = ::FindWindowEx(m_hWnd, hWnd, szClass, szWindow);
	}
	return hWnd;
}

HWND CWndBase::GetNext(bool bPrev)
{
	if(NULL == m_hWnd) return NULL;
	if(bPrev) return CWndTool::GetHandle(GetWindow()->GetNextWindow(GW_HWNDPREV));
	else  return CWndTool::GetHandle(GetWindow()->GetNextWindow(GW_HWNDNEXT));
}

CRect CWndBase::GetRect(RECT_TYPE nType)
{
	CRect rc;
	if(NULL == m_hWnd) return rc;
	GetWindow()->GetClientRect(&rc);
	if (RECT_WINDOW == nType) GetWindow()->ClientToScreen(&rc);
	return rc;
}

bool CWndBase::IsVisible()
{
	if(NULL == m_hWnd) return false;
	return GetWindow()->IsWindowVisible() == TRUE;
}

bool CWndBase::IsEnabled()
{
	if(NULL == m_hWnd) return false;
	return GetWindow()->IsWindowEnabled() == TRUE;
}

bool CWndBase::Enable(bool bEnable)
{
	if(NULL == m_hWnd) return false;
	return GetWindow()->EnableWindow(bEnable ? TRUE : FALSE) == TRUE;
}

void CWndBase::SetPosTop(bool bAlway)
{
	if(NULL == m_hWnd) return;
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
	if(NULL == m_hWnd) return false;
	int nTextLen = ::SendMessage(m_hWnd, WM_GETTEXTLENGTH, 0, 0);
	if(nMaxCount < nTextLen)
	{
		nMaxCount = nTextLen;
		return false;
	}

	nMaxCount = ::SendMessage(m_hWnd, WM_GETTEXT, (WPARAM)nMaxCount, (LPARAM)szText);

	return nMaxCount >= 0;
}

bool CWndBase::SetText(TCHAR* szText)
{
	if(NULL == m_hWnd) return false;
	::SendMessage(m_hWnd, WM_SETTEXT, 0, (LPARAM)szText);
	return true;
}

int CWndBase::GetTextLength()
{
	if(NULL == m_hWnd) return -1;
	return ::SendMessage(m_hWnd, WM_GETTEXTLENGTH, 0, 0);
}
