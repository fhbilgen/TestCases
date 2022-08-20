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
	int		  iCounters = 1;
	ULONGLONG ullLimit = 0;
	ULONGLONG ullSlice = 0;
	ULONGLONG ullDuration = 0;

public:
	DWORD dwLastError = S_OK;
	void SetThreadingInfo(int nThreads, ULONGLONG ulLimit);
	ULONGLONG GetExecutionDuration();
	ULONGLONG GetLimit();
	int GetThreadCount();
	BOOL StartCounting();
};