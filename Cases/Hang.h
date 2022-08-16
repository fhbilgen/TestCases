#pragma once

#include "stdafx.h"

#define RESOURCE_MUTEX_NAME L"Cases_Mutex"
// Helper Functions
DWORD WINAPI Thread1(LPVOID pParam);
DWORD WINAPI Thread2(LPVOID pParam);

DWORD WINAPI LeaveCSOrphant(LPVOID pParam);

UINT FuncA(UINT ui);
UINT FuncB(UINT ui);
UINT FuncC(UINT ui);
UINT FuncD(UINT ui);
UINT FuncE(UINT ui);

DWORD WINAPI HiCpuInternal(LPVOID pParam);
DWORD WINAPI Controller(LPVOID pParam);
