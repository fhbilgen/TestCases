
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
    m_iCounters = nThreads;
    m_ullLimit = ullimit;
    m_ullSlice = m_ullLimit / (ULONGLONG)nThreads;
}

ULONGLONG ThreadHandler::GetExecutionDuration()
{
    return m_ullDuration;
}

ULONGLONG ThreadHandler::GetLimit()
{
    return m_ullLimit;
}

int ThreadHandler::GetThreadCount()
{
    return m_iCounters;
}

BOOL ThreadHandler::StartCounting()
{
    HANDLE* handles = NULL;
    DWORD* threads = NULL;

	
    size_t x = sizeof(CountingBoundary);
	
    PCountingBoundary boundaries = (PCountingBoundary)malloc(sizeof(CountingBoundary) * m_iCounters);
    if ( NULL == boundaries )
    {    
        m_dwLastError = GetLastError();
        return FALSE;
    }

    handles = (HANDLE*)malloc(sizeof(HANDLE) * m_iCounters);
    if ( NULL == handles )
    {
        m_dwLastError = GetLastError();
        return FALSE;
    }

    threads = (DWORD*)malloc(sizeof(DWORD) * m_iCounters);
    if ( NULL == threads )
    {
        m_dwLastError = GetLastError();
        return FALSE;
    }

    ULONGLONG start = GetTickCount64();

    for (UINT i = 0; i != m_iCounters; i++)
    {
        boundaries[i].begin = m_ullSlice * i;
        boundaries[i].end = m_ullSlice * (i + 1);
       
        handles[i] = CreateThread(NULL, 0, CountingFunction, (LPVOID)&(boundaries[i]), 0, &(threads[i]));

        if (handles[i] == NULL)
        {
            m_dwLastError = GetLastError();
            return FALSE;
        }
    }

    WaitForMultipleObjects(m_iCounters, handles, TRUE, INFINITE);

    ULONGLONG end = GetTickCount64();
    m_ullDuration = end - start;

    for (int i = 0; i != m_iCounters; i++)
        CloseHandle(handles[i]);
    
    free(handles);
    free(threads);
    free(boundaries);

    return TRUE;
}

DWORD ThreadHandler::GetError()
{
    return m_dwLastError;
}