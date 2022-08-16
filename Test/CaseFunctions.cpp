#include "stdafx.h"
#include "CaseFunctions.h"


CreateDeadlockProc			g_fnCreateDeadlock			= NULL;
WaitOnOrphantCSProc			g_fnWaitOnOrphantCS			= NULL;
HiCPUUtilizationProc		g_fnHiCPUUtilization		= NULL;
AccessViolateProc			g_fnAccessViolate			= NULL;
AccessViolateAndHandleProc	g_fnAccessViolateAndHandle	= NULL;
StackOverflowProc			g_fnStackOverflow			= NULL;
DivisionByZeroProc			g_fnDivisionByZero			= NULL;
GetResourceProc				g_fnGetResource				= NULL;
ReleaseResourceProc			g_fnReleaseResource			= NULL;

HINSTANCE g_hinstCases = NULL;

BOOL InitializeCaseFunctions()
{
	BOOL result = FALSE;
	
	g_hinstCases = LoadLibrary(_TEXT("Cases.dll"));

	if (NULL == g_hinstCases)
		return FALSE;

	g_fnCreateDeadlock = (CreateDeadlockProc)GetProcAddress(g_hinstCases, "CreateDeadlock");
	g_fnWaitOnOrphantCS = (WaitOnOrphantCSProc)GetProcAddress(g_hinstCases, "WaitOnOrphantCS");
	g_fnHiCPUUtilization = (HiCPUUtilizationProc)GetProcAddress(g_hinstCases, "HiCPUUtilization");
	g_fnAccessViolate = (AccessViolateProc)GetProcAddress(g_hinstCases, "AccessViolate");
	g_fnAccessViolateAndHandle = (AccessViolateAndHandleProc)GetProcAddress(g_hinstCases, "AccessViolateAndHandle");
	g_fnStackOverflow = (StackOverflowProc)GetProcAddress(g_hinstCases, "StackOverflow");
	g_fnDivisionByZero = (DivisionByZeroProc)GetProcAddress(g_hinstCases, "DivisionByZero");	
	g_fnGetResource = (GetResourceProc)GetProcAddress(g_hinstCases, "GetResource");
	g_fnReleaseResource = (ReleaseResourceProc)GetProcAddress(g_hinstCases, "ReleaseResource");

	return TRUE;

}