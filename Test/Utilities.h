#pragma once
//#include "stdafx.h"
#include <Windows.h>
#include <psapi.h>
#include <tchar.h>

#define MAX_PROCESSES 100
#define MAX_PROCESS_LIMIT 10240

DWORD* GetAllProcesses(int* iProcCount);
BOOL GetInstanceCount(DWORD* pProcesses, int processCount, int* pInstanceCount);
_TCHAR* GetInstanceCountText();