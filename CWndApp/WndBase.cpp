#include "StdAfx.h"
#include "WndBase.h"

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

HWND  CWndBase::GetHandle()
{
	return m_hWnd;
}

