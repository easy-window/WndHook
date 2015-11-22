#pragma once
#include "WndBase.h"

namespace WndHook {

	class CWndDialog : public CWndBase
	{
	public:
		CWndDialog(void);
		CWndDialog(HWND hWnd);
		CWndDialog(CWnd* pWnd);

		~CWndDialog(void);

		bool MaxSize();
		bool MinSize();
		bool Restore();
		bool Close();
		bool MoveTo(CPoint pt);
	};

}