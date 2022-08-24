#include "stdafx.h"
#include "Utilities.h"

DWORD* GetAllProcesses(int* iProcCount)
{
    DWORD* pProcessIDs = NULL;
    DWORD dwArraySize = 0;
    DWORD dwReqSize = 0;
    int i = 1;


    while (dwReqSize >= dwArraySize && dwArraySize < MAX_PROCESS_LIMIT * sizeof(DWORD))
    {

        dwArraySize = sizeof(DWORD) * MAX_PROCESSES * i;
        dwReqSize = dwArraySize;

        if (NULL != pProcessIDs)
            free(pProcessIDs);

        pProcessIDs = (DWORD*)malloc(dwArraySize);
        if (NULL == pProcessIDs)
            return NULL;

        if (!EnumProcesses(pProcessIDs, dwArraySize, &dwReqSize))
            return NULL;

        i++;
    }

    *iProcCount = dwReqSize / sizeof(DWORD);

    return pProcessIDs;
}

BOOL GetInstanceCount(DWORD* pProcesses, int processCount, int* pInstanceCount)
{
    DWORD dwCurrentProcID = 0;
    DWORD dwProcNameLen = MAX_PATH;
    _TCHAR szCurProcName[MAX_PATH] = _T("");
    HANDLE hCurProc = NULL;

    HANDLE hProcess = NULL;
    _TCHAR szProcName[MAX_PATH] = _T("");


    dwCurrentProcID = GetCurrentProcessId();
    hCurProc = GetCurrentProcess();
    *pInstanceCount = 0;

    if (!QueryFullProcessImageName(hCurProc, 0, szCurProcName, &dwProcNameLen))
        return FALSE;


    for (int i = 0; i != processCount; i++)
    {
        if (pProcesses[i] == dwCurrentProcID)
            continue;

        hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pProcesses[i]);
        if (NULL != hProcess)
        {
            dwProcNameLen = MAX_PATH;
            if (!QueryFullProcessImageName(hProcess, 0, szProcName, &dwProcNameLen))
            {
                return FALSE;
            }

            if (0 == _tcscmp(szCurProcName, szProcName))
                (*pInstanceCount)++;

            CloseHandle(hProcess);
        }
    }

    return TRUE;
}

_TCHAR* GetInstanceCountText()
{
    DWORD* pdwProcList = NULL;
    int iProcCount;
    int iInstanceCount;
    _TCHAR szCount[4] = _T("");  
    _TCHAR* szCnt = NULL;

    pdwProcList = GetAllProcesses(&iProcCount);

    if (NULL != pdwProcList)
    {
        if (GetInstanceCount(pdwProcList, iProcCount, &iInstanceCount))
            if (iInstanceCount > 0)
            {
                _itot(iInstanceCount, szCount, 10);

                szCnt = (_TCHAR*)malloc(sizeof(_TCHAR) * (_tcslen(szCount) + 1));
                if (NULL != szCnt)
                    _tcscpy(szCnt, szCount);

            }
        free(pdwProcList);
    }
        
    return szCnt;
    
}
