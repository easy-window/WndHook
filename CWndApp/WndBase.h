#pragma once

#include "WndTool.h"

class CWndBase
{
public:
	CWndBase(void);
	CWndBase(HWND hWnd);
	CWndBase(CWnd* pWnd);
	~CWndBase(void);

	void Reset();
	CWnd* GetWindow();
	HWND  GetHandle();

	HWND m_hWnd;
};
