#pragma once
#include "wndbase.h"

class CWndEdit : public CWndBase
{
public:
	CWndEdit(void);
	~CWndEdit(void);

	void PasteTo(TCHAR* szText);
	bool ReadOnly(bool bReadOnly = true);
	bool GetText(TCHAR* szText, int& nMaxLen);
};
