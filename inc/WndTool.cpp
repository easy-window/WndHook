#include "StdAfx.h"
#include "WndTool.h"

using namespace WndHook;

CWnd* CWndTool::GetWindow(HWND hWnd)
{
	return CWnd::FromHandle(hWnd);
}

HWND CWndTool::GetHandle(CWnd* pWnd)
{
	if(NULL == pWnd) return NULL;
	return pWnd->GetSafeHwnd();
}

CString CWndTool::GetCurDirectory()
{
	CString sDirectory = _T("");
	GetModuleFileName(NULL, sDirectory.GetBuffer(MAX_PATH), MAX_PATH);
	sDirectory.ReleaseBuffer();
	sDirectory = sDirectory.Mid(0, sDirectory.ReverseFind(_T('\\')) + 1);

	return sDirectory;
}

LPTSTR CWndTool::ConvertErrorCodeToString(DWORD dwErrorCode)
{
	HLOCAL hLocalAddress = NULL;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, dwErrorCode, 0, (PTSTR)&hLocalAddress, 0, NULL);
	return (LPTSTR)hLocalAddress;
}

bool CWndTool::CopytoTheClipboard(CString sValue, HWND hWnd)
{
	if(NULL == hWnd) return NULL;
	if(::OpenClipboard(hWnd))
	{   
		HGLOBAL hClip;
		size_t cbStr = (sValue.GetLength() + 1) * sizeof(TCHAR);
		::EmptyClipboard();  
		hClip = GlobalAlloc(GMEM_MOVEABLE, cbStr);  
		LPTSTR lpDest = (TCHAR *)GlobalLock(hClip);  
		memcpy_s(lpDest, cbStr, sValue.LockBuffer(), cbStr);
		sValue.UnlockBuffer();
		GlobalUnlock(hClip);
		UINT uiFormat = (sizeof(TCHAR) == sizeof(WCHAR)) ? CF_UNICODETEXT : CF_TEXT;
		SetClipboardData(uiFormat, hClip);
		CloseClipboard();
		return true;
	}
	return false;
} 

bool CWndTool::KeyBoardPress(BYTE vk, bool bAlt, bool bShift, bool bCtrl)
{
	if(0 == vk)
	{
		return false;
	}

	if(bAlt)   { keybd_event(VK_MENU,    MapVirtualKey(VK_MENU,    0), 0, 0); }
	if(bShift) { keybd_event(VK_SHIFT,   MapVirtualKey(VK_SHIFT,   0), 0, 0); }
	if(bCtrl)  { keybd_event(VK_CONTROL, MapVirtualKey(VK_CONTROL, 0), 0, 0); }

	keybd_event(vk, MapVirtualKey(vk, 0), 0, 0);
	Sleep(100);
	keybd_event(vk, MapVirtualKey(vk, 0), KEYEVENTF_KEYUP, 0);

	if(bAlt)   { keybd_event(VK_MENU,    MapVirtualKey(VK_MENU,    0), KEYEVENTF_KEYUP, 0); }
	if(bShift) { keybd_event(VK_SHIFT,   MapVirtualKey(VK_SHIFT,   0), KEYEVENTF_KEYUP, 0); }
	if(bCtrl)  { keybd_event(VK_CONTROL, MapVirtualKey(VK_CONTROL, 0), KEYEVENTF_KEYUP, 0); }

	return true;
}

bool CWndTool::MouseClick(int nX, int nY)
{
	if(!SetCursorPos(nX, nY))
	{
		return false;
	}
	Sleep(10);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, NULL);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, NULL);
	return true;
}
