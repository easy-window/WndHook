#pragma once

#include "WndTool.h"

namespace WndHook {

	typedef enum _RECT_TYPE
	{
		RECT_CLINET = 0,
		RECT_WINDOW,

	}RECT_TYPE, *PRECT_TYPE;

	class CWndBase
	{
	public:
		CWndBase(void);
		CWndBase(HWND hWnd);
		CWndBase(CWnd* pWnd);
		~CWndBase(void);

		void  Reset();
		CWnd* GetWindow();
		HWND  GetHandle();
		HWND  GetChild(unsigned int nIndex, HWND hWndChildAfter = NULL, CONST TCHAR* szClass = NULL, CONST TCHAR* szWindow = NULL);
		HWND  GetNext(bool bPrev = false);
		CRect GetRect(RECT_TYPE nType = RECT_CLINET);
		
		bool  IsVisible();
		bool  IsEnabled();

		bool  Enable(bool bEnable);
		void  SetPosTop(bool bAlway = false);

		bool GetText(TCHAR* szText, int& nMaxCount);
		void SetText(TCHAR* szText);
		int  GetTextLength();

		HWND m_hWnd;
	};

}