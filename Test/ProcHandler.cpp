#include "stdafx.h"
#include "ProcHandler.h"


void ProcHandler::SetAppPath(wchar_t* wszappPath)
{
	if (wszAppPath != NULL)
	{
		free(wszAppPath);
		wszAppPath = NULL;
	}

	int strlen = wcslen(wszappPath) + 1;
	wszAppPath = (wchar_t*)malloc( size_t(strlen) * sizeof(wchar_t) );	

	if ( wszAppPath != NULL )
		wcscpy(wszAppPath, wszappPath);
}

void ProcHandler::SetProcID(DWORD dwprocId)
{
	dwProcID = dwprocId;
}

void ProcHandler::SetThreadID(DWORD dwthreadID)
{
	dwThreadID = dwthreadID;
}

void ProcHandler::SetProcHandle(HANDLE hproc)
{
	hProc = hproc;
}

void ProcHandler::SetThreadHandle(HANDLE hthread)
{
	hThread = hthread;
}

wchar_t* ProcHandler::GetAppPath()
{
	return wszAppPath;
}

DWORD ProcHandler::GetProcID()
{
	return dwProcID;
}

HANDLE ProcHandler::GetProcHandle()
{
	return hProc;
}

HANDLE ProcHandler::GetThreadHandle()
{
	return hThread;
}

DWORD ProcHandler::GetThreadID()
{
	return dwThreadID;
}

BOOL ProcHandler::IsAppPathEmpty()
{
	if (wcsnlen_s(wszAppPath, MAX_PATH) == 0)
		return TRUE;
	else
		return FALSE;
}


void ProcHandler::ClearData()
{
	SetProcHandle(NULL);
	SetThreadHandle(NULL);
	SetProcID(0);
	SetThreadID(0);
}

void ProcHandler::ClearProcessResidue()
{
	CloseHandle(hProc);
	CloseHandle(hThread);
}

BOOL ProcHandler::CreateNewProcess()
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	if (CreateProcess(NULL, wszAppPath, NULL, NULL, false, 0, NULL, NULL, &si, &pi))
	{
		dwLastError = S_OK;
		SetProcHandle(pi.hProcess);
		SetProcID(pi.dwProcessId);
		SetThreadHandle(pi.hThread);
		SetThreadID(pi.dwThreadId);		
		return TRUE;
	}
	else
	{
		dwLastError = GetLastError();
		return FALSE;
	}
}

BOOL ProcHandler::KillCurrentProcess()
{
	if (TerminateProcess(hProc, 0))
	{
		ClearProcessResidue();
		ClearData();		
		return TRUE;
	}
	else
	{
		dwLastError = GetLastError();
		return FALSE;
	}
}

void ProcHandler::WaitProcessExit()
{
	WaitForSingleObject(hProc, INFINITE);		
	ClearProcessResidue();
	ClearData();
}