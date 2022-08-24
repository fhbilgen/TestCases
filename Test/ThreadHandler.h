#pragma once

#include <Windows.h>
#include "wchar.h"

typedef struct _countingBoundary {
    ULONGLONG begin;
    ULONGLONG end;
} CountingBoundary, * PCountingBoundary;

DWORD WINAPI CountingFunction(LPVOID lpParam);

class ThreadHandler
{
private:
	int		  m_iCounters = 1;
	ULONGLONG m_ullLimit = 0;
	ULONGLONG m_ullSlice = 0;
	ULONGLONG m_ullDuration = 0;
	DWORD m_dwLastError = S_OK;

public:
	
	void SetThreadingInfo(int nThreads, ULONGLONG ulLimit);
	ULONGLONG GetExecutionDuration();
	ULONGLONG GetLimit();
	int GetThreadCount();
	BOOL StartCounting();
	DWORD GetError();
};