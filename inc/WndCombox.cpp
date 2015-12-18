#include "StdAfx.h"
#include "WndButton.h"

using namespace WndHook;


CWndComboBox::CWndComboBox(void) 
	: CWndBase()
{

}

CWndComboBox::~CWndComboBox(void)
{
}

CWndComboBox::CWndComboBox(HWND hWnd) 
	: CWndBase(hWnd)
{

}

CWndComboBox::CWndComboBox(CWnd* pWnd) 
	: CWndBase(pWnd)
{
}

int CWndComboBox::GetCount()
{
	return ::SendMessage(m_hWnd, CB_GETCOUNT, 0, 0);
}

int CWndComboBox::GetCurSel()
{
	return ::SendMessage(m_hWnd, CB_GETCURSEL, 0, 0);
}

int CWndComboBox::SetCurSel(int nSelect)
{
	return ::SendMessage(m_hWnd, CB_SETCURSEL, nSelect, 0);
}

int CWndComboBox::DeleteString(int nIndex)
{
	return ::SendMessage(m_hWnd, CB_DELETESTRING, nIndex, 0); 
}

int CWndComboBox::InsertString(int nIndex, TCHAR* szText)
{
	return ::SendMessage(m_hWnd , CB_INSERTSTRING, 0, (LPARAM)szText);
}

void CWndComboBox::ResetContent()
{
	::SendMessage(m_hWnd, CB_RESETCONTENT, 0, 0);
}

void CWndComboBox::GetLBText(int nIndex, TCHAR* szText)
{
	::SendMessage(m_hWnd, CB_GETLBTEXT, nIndex, (LPARAM)szText);
}

int CWndComboBox::GetLBTextLen(int nIndex)
{
	return ::SendMessage(m_hWnd, CB_GETLBTEXTLEN, nIndex, 0);
}

int CWndComboBox::SetText(TCHAR* szText)
{
	return ::SendMessage(m_hWnd, CB_SELECTSTRING, 0, (LPARAM)szText);
}

void CWndComboBox::ShowDropdown(bool bShow)
{
	::SendMessage(m_hWnd, CB_SHOWDROPDOWN, bShow ? TRUE : FALSE, 0);
}