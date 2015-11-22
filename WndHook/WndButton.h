#pragma once
#include "WndBase.h"

namespace WndHook {

	class CWndButton : public CWndBase
	{
	public:
		CWndButton(void);
		CWndButton(HWND hWnd);
		CWndButton(CWnd* pWnd);

		~CWndButton(void);

		bool LeftClick(CPoint pt = CPoint(1, 1));
		bool RightClick(CPoint pt = CPoint(1, 1));
		bool SetCheck(bool bCheck);

		bool IsCheck();

	};

}