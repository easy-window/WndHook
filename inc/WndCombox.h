#pragma once
#include "WndBase.h"

namespace WndHook {

	class CWndComboBox : public CWndBase
	{
	public:
		CWndComboBox(void);
		CWndComboBox(HWND hWnd);
		CWndComboBox(CWnd* pWnd);

		~CWndComboBox(void);

		int  GetCount();
		int  GetCurSel();
		int	 SetCurSel(int nSelect);

		int  DeleteString(int nIndex);
		int  InsertString(int nIndex, TCHAR* szText);
		void ResetContent();

		void GetLBText(int nIndex, TCHAR* szText);
		int  GetLBTextLen(int nIndex);

		int SetText(TCHAR* szText);

		void ShowDropdown(bool bShow);
	};

}