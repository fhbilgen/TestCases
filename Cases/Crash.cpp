
#include "stdafx.h"

CASES_API void DivisionByZero()
{
	int a = 0;
	int b = 0;
	int c = 0;

	c = a / b;
}

CASES_API void AccessViolate()
{
	int *pi = NULL;
	*pi = 5;
}

CASES_API void AccessViolateVAReserve()
{
	int *pi = NULL;

	pi = (int*)VirtualAlloc(NULL, sizeof(int) * 1000, MEM_RESERVE, PAGE_READWRITE);

	if (NULL != pi)
		pi[0] = 10;

}

CASES_API void AccessViolateHeapCorrupt()
{
	char	*cp = NULL;
	cp = (char*)malloc(sizeof(char) * 10);

	strncpy_s(cp, sizeof(char) * 10, "string", 10);
	
	free(cp);

	free(cp);
}


int filterFunc(unsigned int code, struct _EXCEPTION_POINTERS *ep)
{

	if (code == EXCEPTION_ACCESS_VIOLATION)
		return EXCEPTION_EXECUTE_HANDLER;
	else
		return EXCEPTION_CONTINUE_SEARCH;

}

LONG64 Factorial(int i)
{
	BYTE *pb;

	pb = (BYTE*)_alloca(100000 * sizeof(BYTE));

	if (i <= 1)
		return 1;
	else
		return i * Factorial(i - 1);
}

CASES_API void AccessViolateAndHandle()
{
	int *pi = NULL;

	__try
	{
		*pi = 5;
	}
	__except (filterFunc(GetExceptionCode(), GetExceptionInformation()))
	{
		LogAnEvent(L"ACCESS VIOLATION EXCEPTION HAPPENED!!!");
	}

}


CASES_API void StackOverflow(int iFact)
{
	INT64 iRes = 0;

	iRes = Factorial(iFact);
	wchar_t buffer[100];

	_i64tow_s(iRes, buffer, 10, 10);

	LogAnEvent(buffer);

}


void LogAnEvent(LPCWSTR szLogDescription)
{
	wchar_t *sourceName = L"TestCases";  // The event source name.
	DWORD dwEventID = 1001;               // The event identifier.

	HANDLE h;

	// Get a handle to the event log.
	h = RegisterEventSource(NULL,  // Use local computer. 
		sourceName);           // Event source name. 

	// Report the event.
	ReportEvent(h,           // Event log handle. 
		EVENTLOG_ERROR_TYPE,  // Event type. 
		NULL,                 // Event category.  
		dwEventID,            // Event identifier. 
		NULL,                 // No user security identifier. 
		1,             // Number of substitution strings. 
		0,                    // No data. 
		&szLogDescription,               // Pointer to strings. 
		NULL);                // No data. 

	DeregisterEventSource(h);

}