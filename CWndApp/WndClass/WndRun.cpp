#include "StdAfx.h"
#include "WndRun.h"

typedef struct _PROCESSWINDOW  
{  
	DWORD dwProcessId;  
	HWND hwndWindow;

}PROCESSWINDOW, *PPROCESSWINDOW;  

CWndRun::CWndRun(void)
{
}

CWndRun::~CWndRun(void)
{
}

void CWndRun::Reset()
{
	CWndBase::Reset();
	memset(&m_si, 0, sizeof(STARTUPINFO));  
	memset(&m_pi, 0, sizeof(PROCESS_INFORMATION));  
	memset(&m_stShExecInfo, 0, sizeof(m_stShExecInfo));
	m_sCurDirectory = CWndTool::GetCurDirectory();
}

bool CWndRun::Run(TCHAR* szPath, TCHAR* szCommand, RUN_TYPE nType)
{
	switch(nType)
	{
	case RUN_SHELL: return NULL != RunByShell(CString(szPath), CString(szCommand));
	case RUN_PROCESS: return NULL != RunByProcess(CString(szPath), CString(szCommand));
	}
}

bool CWndRun::Destroy()
{
	HANDLE* pProcess = GetProcess();

	if(NULL != pProcess && NULL != *pProcess)
	{
		DWORD dwReturn = WaitForSingleObject(*pProcess, 0);
		switch(dwReturn)
		{
		case WAIT_OBJECT_0:
			CloseHandle(*pProcess);
			m_pi.hProcess = NULL;
			return true;

		case WAIT_TIMEOUT:
			TerminateProcess(*pProcess, 2);
			CloseHandle(*pProcess);
			*pProcess = NULL;
			return true;

		case WAIT_FAILED: // error occur.
			CloseHandle(*pProcess);
			*pProcess = NULL;
			return false;
		}
	}

	return true;
}

bool CWndRun::IsRunning()
{
	HANDLE *pProcess = GetProcess();

	if(NULL != pProcess && NULL != *pProcess)
	{
		if(WAIT_TIMEOUT == WaitForSingleObject(*pProcess, 0))
		{
			return true;
		}
	}

	return false;
}



BOOL CALLBACK CWndRun::EnumWindowsProc(HWND hWnd, LPARAM lParam)
{
	PROCESSWINDOW *pProcessWindow = (PROCESSWINDOW*)lParam;  

	DWORD dwProcessId;  
	GetWindowThreadProcessId(hWnd, &dwProcessId);  

	if (pProcessWindow->dwProcessId == dwProcessId 
	&& CWnd::FromHandle(hWnd)->IsWindowVisible() 
	&& CWnd::FromHandle(hWnd)->GetParent() == NULL)  
	{  
		pProcessWindow->hwndWindow = hWnd;  

		return FALSE;  
	}  

	return TRUE;  
}

HWND CWndRun::RunByProcess(CString sPath, CString sCommand)
{
	memset(&m_si, 0, sizeof(STARTUPINFO));  
	memset(&m_pi, 0, sizeof(PROCESS_INFORMATION));  

	m_si.cb = sizeof(STARTUPINFO);  
	m_si.dwFlags = STARTF_USESHOWWINDOW;  
	m_si.wShowWindow = SW_SHOW; 

	m_hWnd = NULL;

	CString sNewDirectory = sPath.Left(sPath.ReverseFind(_T('\\')) + 1);
	SetCurrentDirectory(sNewDirectory);

	if (CreateProcess((LPWSTR)(LPCTSTR)sPath, (LPWSTR)(LPCTSTR)sCommand, NULL, NULL, false, CREATE_NEW_CONSOLE, NULL, NULL, &m_si, &m_pi))  
	{  
		PROCESSWINDOW procwin;  
		procwin.dwProcessId = m_pi.dwProcessId;  
		procwin.hwndWindow = NULL;  

		DWORD dwReturn = WaitForInputIdle(m_pi.hProcess, INFINITE);  

		int nTime = 10;
		while(0 == dwReturn && NULL == m_hWnd && 0 < nTime--)
		{
			Sleep(1000);
			EnumWindows(EnumWindowsProc, (LPARAM)&procwin);  
			Sleep(10);

			m_hWnd = procwin.hwndWindow;
			if(m_hWnd != NULL) break;
		}
	}  

	SetCurrentDirectory(m_sCurDirectory);

	return m_hWnd;
}

HANDLE CWndRun::RunByShell(CString sPath, CString sCommand)
{
	CString sNewDirectory = sPath.Left(sPath.ReverseFind(_T('\\')) + 1);
	SetCurrentDirectory(sNewDirectory);

	memset(&m_stShExecInfo, 0, sizeof(m_stShExecInfo));

	m_stShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	m_stShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	m_stShExecInfo.hwnd = NULL;
	m_stShExecInfo.lpVerb = _T("open");
	m_stShExecInfo.lpFile = (LPTSTR)(LPCTSTR)sPath; 
	m_stShExecInfo.lpParameters = (LPTSTR)(LPCTSTR)sCommand; 
	m_stShExecInfo.lpDirectory = NULL;
	m_stShExecInfo.nShow = SW_SHOWNORMAL;
	m_stShExecInfo.hInstApp = NULL; 

	ShellExecuteEx(&m_stShExecInfo);
	SetCurrentDirectory(m_sCurDirectory);

	return m_stShExecInfo.hProcess;
}

HANDLE* CWndRun::GetProcess()
{
	if(NULL != m_pi.hProcess)
	{
		return &m_pi.hProcess;
	}
	else if (NULL != m_stShExecInfo.hProcess)
	{
		return &m_stShExecInfo.hProcess;
	}

	return NULL;
}
