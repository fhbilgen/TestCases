#include "stdafx.h"
#include "MutexHandler.h"

BOOL MutexHandler::InitiateMutex(BOOL fCreate)
{
    if (fCreate)
    {
        hMutex = CreateMutex(NULL, TRUE, szMutexName);
    }
    else
    {
        hMutex = OpenMutex(SYNCHRONIZE, FALSE, szMutexName);
    }

    if (NULL == hMutex)
    {
        dwLastError = GetLastError();
        return FALSE;
    }

    return TRUE;
}

void MutexHandler::CloseMutex()
{
    CloseHandle(hMutex);
}

HANDLE MutexHandler::GetMutexHandle()
{
    return hMutex;
}

DWORD MutexHandler::GetError()
{
    return dwLastError;
}

_TCHAR* MutexHandler::GetMutexName()
{
    return szMutexName;
}