#include "stdafx.h"
#include "LibHandler.h"

const _TCHAR szLoadMessage[30] = _T("Cases.dll is loaded");
const _TCHAR szUnloadMessage[30] = _T("Cases.dll is unloaded");

BOOL LibHandler::LoadLib()
{
    m_hLib = LoadLibrary(m_szLibName);

    if (NULL == m_hLib)
    {
        m_dwLastError = GetLastError();
        m_fLoaded = FALSE;
        return FALSE;
    }

    m_fLoaded = TRUE;
    return TRUE;
}

BOOL LibHandler::LoadFnAddr()
{
    m_fnAdd = (OpAdd)GetProcAddress(m_hLib, "Add");

    if (NULL == m_fnAdd)
    {
        m_dwLastError = GetLastError();
        return FALSE;
    }

    m_fnSub = (OpSub)GetProcAddress(m_hLib, "Subtract");

    if (NULL == m_fnSub)
    {
        m_dwLastError = GetLastError();
        return FALSE;
    }

    m_fnMul = (OpMul)GetProcAddress(m_hLib, "Multiply");

    if (NULL == m_fnMul)
    {
        m_dwLastError = GetLastError();
        return FALSE;
    }

    m_fnDiv = (OpDiv)GetProcAddress(m_hLib, "Divide");

    if (NULL == m_fnDiv)
    {
        m_dwLastError = GetLastError();
        return FALSE;
    }

    return TRUE;
}

void LibHandler::ZeroFnAddr()
{
    m_fnAdd = NULL;
    m_fnSub = NULL;
    m_fnMul = NULL;
    m_fnDiv = NULL;
}

int LibHandler::Calculate(int a, int b, int op)
{
    int result = 0;

    switch (op)
    {
    case 0:
        result = (m_fnAdd)(a, b);
        break;
    
    case 1:
        result = (m_fnSub)(a, b);
        break;
    
    case 2:
        result = (m_fnMul)(a, b);
        break;
    
    case 3:
        result = (m_fnDiv)(a, b);
        break;

    default:
        break;
    }

    return result;
}

BOOL LibHandler::UnloadLib()
{
    if (!FreeLibrary(m_hLib))
    {       
        m_dwLastError = GetLastError();
        return FALSE;
    }

    m_fLoaded = FALSE;
    return TRUE;
}

BOOL LibHandler::GetLoadState()
{
    return m_fLoaded;
}

const _TCHAR* LibHandler::GetLoadStateMessage()
{
    if (m_fLoaded)
        return szLoadMessage;
    else
        return szUnloadMessage;

}

DWORD LibHandler::GetError()
{
    return m_dwLastError;
}
