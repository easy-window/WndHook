#include "StdAfx.h"
#include "WndButton.h"

using namespace WndHook;


CWndButton::CWndButton(void) 
	: CWndBase()
{

}

CWndButton::~CWndButton(void)
{
}

CWndButton::CWndButton(HWND hWnd) 
	: CWndBase(hWnd)
{

}

CWndButton::CWndButton(CWnd* pWnd) 
	: CWndBase(pWnd)
{
}

bool CWndButton::SetCheck(bool bCheck)
{
	if(NULL == m_hWnd) return false;

	::SendMessage(m_hWnd, BM_SETCHECK, bCheck ? BST_CHECKED : BST_UNCHECKED, 0);

	return true;
}

bool CWndButton::IsCheck()
{
	if(NULL == m_hWnd) return false;

	return ::SendMessage(m_hWnd, BM_GETCHECK , 0, 0) == BST_CHECKED;
}

bool CWndButton::LeftClick(CPoint pt)
{
	if(NULL == m_hWnd) return false;
	::SendMessage(m_hWnd, WM_LBUTTONDOWN, VK_LBUTTON, MAKELONG(pt.x, pt.y));
	::SendMessage(m_hWnd, WM_LBUTTONUP, VK_LBUTTON, MAKELONG(pt.x, pt.y));
	::SendMessage(m_hWnd, BM_CLICK, 0, 0);
	return true;
}

bool CWndButton::RightClick(CPoint pt)
{
	if(NULL == m_hWnd) return false;
	::SendMessage(m_hWnd, WM_RBUTTONDOWN, VK_RBUTTON, MAKELONG(pt.x, pt.y));
	::SendMessage(m_hWnd, WM_RBUTTONUP, VK_RBUTTON, MAKELONG(pt.x, pt.y));
	::SendMessage(m_hWnd, BM_CLICK, 0, 0);
	return true;
}
