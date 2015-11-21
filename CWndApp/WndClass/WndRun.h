#pragma once

#include "WndBase.h"

typedef enum _RUN_TYPE
{
	RUN_SHELL = 0,
	RUN_PROCESS,

}RUN_TYPE, *PRUN_TYPE;

class CWndRun : public CWndBase
{
public:
	CWndRun(void);
	~CWndRun(void);

	void Reset();
	bool Run(TCHAR* szPath, TCHAR* szCommand, RUN_TYPE nType);
	bool Destroy();
	bool IsRunning();

	HANDLE* GetProcess();

private:
	static BOOL	CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam);
	HWND RunByProcess(CString sPath, CString sCommand);
	HANDLE RunByShell(CString sPath, CString sCommand);

	STARTUPINFO m_si;
	PROCESS_INFORMATION m_pi;
	SHELLEXECUTEINFO m_stShExecInfo;
	CString m_sCurDirectory;
};
