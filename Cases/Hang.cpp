
#include "stdafx.h"


HANDLE g_HiCpuHandle = NULL;
HANDLE g_hThreadController = NULL;
HANDLE g_mtxResource = NULL;

DWORD WINAPI Thread1(LPVOID pParam)
{
	Sync *snk;
	snk = (Sync*)pParam;
	snk->AccessFirstResource();
	Sleep(2000);
	snk->AccessSecondResource();

	return 0;
}

DWORD WINAPI Thread2(LPVOID pParam)
{
	Sync *snk;
	snk = (Sync*)pParam;
	snk->AccessSecondResource();
	Sleep(2000);
	snk->AccessFirstResource();

	return 0;

}

// Assumption is that 2 seconds will be enough to put the threads into deadlock
// This just simplifies the logic. Correct approach should be using event, mutex, etc.
CASES_API void  CreateDeadlock(void)
{
	HANDLE	hThread[2];
	DWORD	dwThreadID[2];
	Sync *snk;

	snk = new Sync();

	hThread[0] = CreateThread(NULL, 0, Thread1, snk, 0, &dwThreadID[0]);
	hThread[1] = CreateThread(NULL, 0, Thread2, snk, 0, &dwThreadID[1]);

	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);
	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);
	delete snk;

}


DWORD WINAPI LeaveCSOrphant(LPVOID pParam)
{
	Sync *snk;
	snk = (Sync*)pParam;
	snk->AccessFirstResource();

	return 0;
}

CASES_API void WaitOnOrphantCS(void)
{
	HANDLE hThread;
	DWORD  dwThreadID;

	Sync *snk;

	snk = new Sync();

	hThread = CreateThread(NULL, 0, LeaveCSOrphant, snk, 0, &dwThreadID);

	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);

	hThread = CreateThread(NULL, 0, Thread1, snk, 0, &dwThreadID);
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
	delete snk;

}

UINT FuncA(UINT ui)
{
	return FuncB(ui * 2);
}

UINT FuncB(UINT ui)
{
	return FuncC(ui * 3);
}

UINT FuncC(UINT ui)
{
	return FuncD(ui * 4);
}

UINT FuncD(UINT ui)
{
	return FuncE(ui * 5);
}

UINT FuncE(UINT ui)
{
	return ui * 6;
}

DWORD WINAPI HiCpuInternal(LPVOID pParam)
{
	UINT ui = 1;

	while (WAIT_TIMEOUT == WaitForSingleObject(g_HiCpuHandle, 0))
	//while (TRUE)
	{
		if (ui > 100000000)
			ui = ui % 100000000;

		ui = FuncA(ui);

	}

	return 0;
}


//DWORD CountSetBits(ULONG_PTR bitMask)
//{
//	DWORD LSHIFT = sizeof(ULONG_PTR)* 8 - 1;
//	DWORD bitSetCount = 0;
//	ULONG_PTR bitTest = (ULONG_PTR)1 << LSHIFT;
//	DWORD i;
//
//	for (i = 0; i <= LSHIFT; ++i)
//	{
//		bitSetCount += ((bitMask & bitTest) ? 1 : 0);
//		bitTest /= 2;
//	}
//
//	return bitSetCount;
//}
//
//UINT NumberOfCores(void)
//{
//	LPFN_GLPI glpi;
//	BOOL done = FALSE;
//	PSYSTEM_LOGICAL_PROCESSOR_INFORMATION buffer = NULL;
//	PSYSTEM_LOGICAL_PROCESSOR_INFORMATION ptr = NULL;
//	DWORD returnLength = 0;
//	DWORD logicalProcessorCount = 0;
//	DWORD byteOffset = 0;
//
//	glpi = (LPFN_GLPI)GetProcAddress(GetModuleHandle(TEXT("kernel32")), "GetLogicalProcessorInformation");
//	if (NULL == glpi)
//		return logicalProcessorCount;
//
//	while (!done)
//	{
//		DWORD rc = glpi(buffer, &returnLength);
//
//		if (FALSE == rc)
//		{
//			if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
//			{
//				if (buffer)
//					free(buffer);
//
//				buffer = (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION)malloc(
//					returnLength);
//
//				if (NULL == buffer)
//					return logicalProcessorCount;
//			}
//			else
//				return logicalProcessorCount;
//		}
//		else
//			done = TRUE;
//	}
//
//	ptr = buffer;
//
//	while (byteOffset + sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION) <= returnLength)
//	{
//		if (ptr->Relationship == RelationProcessorCore)
//			logicalProcessorCount += CountSetBits(ptr->ProcessorMask);
//
//		byteOffset += sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
//		ptr++;
//	}
//
//	free(buffer);
//
//	return logicalProcessorCount;
//
//}

DWORD WINAPI Controller(LPVOID pParam)
{
	HANDLE  *pThreadHandles;
	DWORD   *pThreadIDs;
	int		iNumOfCores;


	iNumOfCores = *((int*)pParam);

	if (iNumOfCores == 0)
		iNumOfCores = 1;
		
	pThreadHandles = (HANDLE*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(HANDLE)* iNumOfCores);
	pThreadIDs = (DWORD*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(DWORD)* iNumOfCores);

	for (int i = 0; i != iNumOfCores; i++)
	{
		pThreadHandles[i] = CreateThread(NULL, 0, HiCpuInternal, NULL, 0, &pThreadIDs[i]);
		if (pThreadHandles[i] == NULL)
			return 1; // ExitProcess(3);
	}

	// Assuming there are less than 65 cores
	WaitForMultipleObjects(iNumOfCores, pThreadHandles, TRUE, INFINITE);

	for (int i = 0; i != iNumOfCores; i++)
	{
		CloseHandle(pThreadHandles[i]);
	}

	pThreadHandles = NULL;
	pThreadIDs = NULL;
	HeapFree(GetProcessHeap(), HEAP_ZERO_MEMORY, pThreadHandles);
	HeapFree(GetProcessHeap(), HEAP_ZERO_MEMORY, pThreadIDs);
	free(pParam);
	return 0;
}

CASES_API void  HiCPUUtilization(int iNumOfCores, HANDLE hStopEvent)
{
	DWORD   dwThreadID;
	int		*pInt = NULL;

	// There are better ways to close this handle. This is the easiest though.
	if (g_hThreadController != NULL)
	{
		CloseHandle(g_hThreadController);
		g_hThreadController = NULL;
	}
	
	g_HiCpuHandle = hStopEvent;	

	pInt = (int*)malloc(sizeof(int));
	*pInt = iNumOfCores;
	g_hThreadController = CreateThread(NULL, 0, Controller, pInt, 0, &dwThreadID);

}



CASES_API BOOL GetResource()
{
	g_mtxResource = OpenMutex(SYNCHRONIZE, FALSE, RESOURCE_MUTEX_NAME);

	if (NULL == g_mtxResource)
	{
		g_mtxResource = CreateMutex(NULL, FALSE, RESOURCE_MUTEX_NAME);
		
		if (NULL == g_mtxResource)
			return FALSE;
	}

	WaitForSingleObject(g_mtxResource, INFINITE);
	return TRUE;
}

CASES_API BOOL ReleaseResource()
{
	if (g_mtxResource != NULL)
	{
		if (!ReleaseMutex(g_mtxResource))
			return FALSE;
		else
			return TRUE;
	}
	return TRUE;
}
