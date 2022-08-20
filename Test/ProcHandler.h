#pragma once

#include <Windows.h>
#include "wchar.h"

class ProcHandler
{
	wchar_t* wszAppPath = NULL;
	DWORD dwProcID = 0;
	DWORD dwThreadID = 0;
	HANDLE hProc = NULL;
	HANDLE hThread = NULL;

public:
	DWORD dwLastError = S_OK;
	void SetAppPath(wchar_t* wszappPath);
	void SetProcID(DWORD dwprocId);
	void SetThreadID(DWORD dwthreadID);
	void SetProcHandle(HANDLE hproc);
	void SetThreadHandle(HANDLE hthread);
	DWORD GetProcID();
	HANDLE GetProcHandle();
	HANDLE GetThreadHandle();
	DWORD GetThreadID();
	wchar_t* ProcHandler::GetAppPath();

	BOOL IsAppPathEmpty();
	BOOL CreateNewProcess();
	BOOL KillCurrentProcess();
	void WaitProcessExit();

private:
	void ClearData();
	void ClearProcessResidue();
};

