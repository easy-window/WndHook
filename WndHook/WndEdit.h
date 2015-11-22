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

		void PasteTo(TCHAR* szText);
		bool ReadOnly(bool bReadOnly = true);
		bool GetText(TCHAR* szText, int& nMaxLen);
	};

}