#include "stdafx.h"
#include "ProcHandler.h"


void ProcHandler::SetAppPath(wchar_t* wszappPath)
{
	if (m_wszAppPath != NULL)
	{
		free(m_wszAppPath);
		m_wszAppPath = NULL;
	}

	int strlen = wcslen(wszappPath) + 1;
	m_wszAppPath = (wchar_t*)malloc( size_t(strlen) * sizeof(wchar_t) );	

	if ( m_wszAppPath != NULL )
		wcscpy(m_wszAppPath, wszappPath);
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

wchar_t* ProcHandler::GetAppPath()
{
	return m_wszAppPath;
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
	if (wcsnlen_s(m_wszAppPath, MAX_PATH) == 0)
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

	if (CreateProcess(NULL, m_wszAppPath, NULL, NULL, false, 0, NULL, NULL, &si, &pi))
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