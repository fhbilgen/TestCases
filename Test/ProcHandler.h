#pragma once

#include <Windows.h>
#include "wchar.h"

class ProcHandler
{
private:
	_TCHAR* m_szAppPath = NULL;
	DWORD m_dwLastError = S_OK;
	DWORD m_dwProcID = 0;
	DWORD m_dwThreadID = 0;
	HANDLE m_hProc = NULL;
	HANDLE m_hThread = NULL;

public:	
	void SetAppPath(_TCHAR* szappPath);
	void SetProcID(DWORD dwprocId);
	void SetThreadID(DWORD dwthreadID);
	void SetProcHandle(HANDLE hproc);
	void SetThreadHandle(HANDLE hthread);
	DWORD GetProcID();
	HANDLE GetProcHandle();
	HANDLE GetThreadHandle();
	DWORD GetThreadID();
	_TCHAR* ProcHandler::GetAppPath();

	BOOL IsAppPathEmpty();
	BOOL CreateNewProcess();
	BOOL KillCurrentProcess();
	void WaitProcessExit();
	DWORD GetError();

private:
	void ClearData();
	void ClearProcessResidue();
};

