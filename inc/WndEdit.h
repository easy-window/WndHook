#pragma once
#include "WndBase.h"

namespace WndHook {

	class CWndEdit : public CWndBase
	{
	public:
		CWndEdit(void);
		CWndEdit(HWND hWnd);
		CWndEdit(CWnd* pWnd);

		~CWndEdit(void);

		bool SetSelect(int nBegin, int nEnd, bool bFocus = true); // 0 ~ -1 is select all
		bool PasteTo(TCHAR* szText);
		bool ReadOnly(bool bReadOnly = true);
		bool GetText(TCHAR* szText, int& nMaxLen);

		bool IsReadOnly();

	};

}