#include "stdafx.h"
#include "ProcHandler.h"


void ProcHandler::SetAppPath(_TCHAR* szappPath)
{
	if (m_szAppPath != NULL)
	{
		free(m_szAppPath);
		m_szAppPath = NULL;
	}

	int strlen = (int)_tcslen(szappPath) + 1;
	m_szAppPath = (_TCHAR*)malloc( strlen * sizeof(_TCHAR) );

	if ( m_szAppPath != NULL )
		_tcscpy_s(m_szAppPath, strlen, szappPath);
}

void ProcHandler::SetProcID(DWORD dwprocId)
{
	m_dwProcID = dwprocId;
}

void ProcHandler::SetThreadID(DWORD dwthreadID)
{
	m_dwThreadID = dwthreadID;
}

void ProcHandler::SetProcHandle(HANDLE hproc)
{
	m_hProc = hproc;
}

void ProcHandler::SetThreadHandle(HANDLE hthread)
{
	m_hThread = hthread;
}

_TCHAR* ProcHandler::GetAppPath()
{
	return m_szAppPath;
}

DWORD ProcHandler::GetProcID()
{
	return m_dwProcID;
}

HANDLE ProcHandler::GetProcHandle()
{
	return m_hProc;
}

HANDLE ProcHandler::GetThreadHandle()
{
	return m_hThread;
}

DWORD ProcHandler::GetThreadID()
{
	return m_dwThreadID;
}

BOOL ProcHandler::IsAppPathEmpty()
{
	if (wcsnlen_s(m_szAppPath, MAX_PATH) == 0)
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
	CloseHandle(m_hProc);
	CloseHandle(m_hThread);
}

BOOL ProcHandler::CreateNewProcess()
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	if (CreateProcess(NULL, m_szAppPath, NULL, NULL, false, 0, NULL, NULL, &si, &pi))
	{
		m_dwLastError = S_OK;
		SetProcHandle(pi.hProcess);
		SetProcID(pi.dwProcessId);
		SetThreadHandle(pi.hThread);
		SetThreadID(pi.dwThreadId);		
		return TRUE;
	}
	else
	{
		m_dwLastError = GetLastError();
		return FALSE;
	}
}

BOOL ProcHandler::KillCurrentProcess()
{
	if (TerminateProcess(m_hProc, 0))
	{
		ClearProcessResidue();
		ClearData();		
		return TRUE;
	}
	else
	{
		m_dwLastError = GetLastError();
		return FALSE;
	}
}

void ProcHandler::WaitProcessExit()
{
	WaitForSingleObject(m_hProc, INFINITE);		
	ClearProcessResidue();
	ClearData();
}

DWORD ProcHandler::GetError()
{
	return m_dwLastError;
}