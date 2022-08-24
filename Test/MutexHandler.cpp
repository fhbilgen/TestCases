#include "stdafx.h"
#include "MutexHandler.h"

BOOL MutexHandler::InitiateMutex(BOOL fCreate)
{
    if (fCreate)
    {
        m_hMutex = CreateMutex(NULL, TRUE, m_szMutexName);
    }
    else
    {
        m_hMutex = OpenMutex(SYNCHRONIZE, FALSE, m_szMutexName);
    }

    if (NULL == m_hMutex)
    {
        m_dwLastError = GetLastError();
        return FALSE;
    }

    return TRUE;
}

void MutexHandler::CloseMutex()
{
    CloseHandle(m_hMutex);
}

HANDLE MutexHandler::GetMutexHandle()
{
    return m_hMutex;
}

DWORD MutexHandler::GetError()
{
    return m_dwLastError;
}

_TCHAR* MutexHandler::GetMutexName()
{
    return m_szMutexName;
}