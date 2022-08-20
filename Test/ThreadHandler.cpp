
#include "stdafx.h"
#include "ThreadHandler.h"

DWORD WINAPI CountingFunction(LPVOID lpParam)
{
    PCountingBoundary pBoundary;

    pBoundary = (PCountingBoundary)lpParam;

    // dummy loop that just counts
    for (ULONGLONG i = pBoundary->begin; i != pBoundary->end; i++);


    return 0;
}

void ThreadHandler::SetThreadingInfo(int nThreads, ULONGLONG ullimit)
{
    iCounters = nThreads;
    ullLimit = ullimit;
    ullSlice = ullLimit / (ULONGLONG)nThreads;
}

ULONGLONG ThreadHandler::GetExecutionDuration()
{
    return ullDuration;
}

ULONGLONG ThreadHandler::GetLimit()
{
    return ullLimit;
}

int ThreadHandler::GetThreadCount()
{
    return iCounters;
}

BOOL ThreadHandler::StartCounting()
{
    HANDLE* handles = NULL;
    DWORD* threads = NULL;

    PCountingBoundary boundaries = (PCountingBoundary)malloc(sizeof(CountingBoundary) * iCounters);
    if (boundaries == NULL)
    {    
        dwLastError = GetLastError();
        return FALSE;
    }

    handles = (HANDLE*)malloc(sizeof(HANDLE) * iCounters);
    if (handles == NULL)
    {
        dwLastError = GetLastError();
        return FALSE;
    }

    threads = (DWORD*)malloc(sizeof(DWORD) * iCounters);
    if (threads == NULL)
    {
        dwLastError = GetLastError();
        return FALSE;
    }

    ULONGLONG start = GetTickCount64();

    for (int i = 0; i != iCounters; i++)
    {
        boundaries[i].begin = ullSlice * (ULONGLONG)i;
        boundaries[i].end = ullSlice * ULONGLONG(i + 1);
       
        handles[i] = CreateThread(NULL, 0, CountingFunction, (LPVOID)&boundaries[i], 0, &threads[i]);

        if (handles[i] == NULL)
        {
            dwLastError = GetLastError();
            return FALSE;
        }
    }

    WaitForMultipleObjects(iCounters, handles, TRUE, INFINITE);

    ULONGLONG end = GetTickCount64();
    ullDuration = end - start;

    for (int i = 0; i != iCounters; i++)
        CloseHandle(handles[i]);
    
    free(handles);
    free(threads);
    free(boundaries);

    return TRUE;
}