#pragma once

#include "stdafx.h"

typedef void(*CreateDeadlockProc)();
typedef void(*WaitOnOrphantCSProc)();
typedef void(*HiCPUUtilizationProc)(int, HANDLE);
typedef void(*AccessViolateProc)();
typedef void(*AccessViolateAndHandleProc)();
typedef void(*StackOverflowProc)(int);
typedef void(*DivisionByZeroProc)();
typedef BOOL(*GetResourceProc)();
typedef BOOL(*ReleaseResourceProc)();
BOOL InitializeCaseFunctions();