#pragma once
class MutexHandler
{
private:
	DWORD dwLastError = S_OK;
	HANDLE hMutex = NULL;
	_TCHAR szMutexName[20] = _T("MUTEXTest");

public:
	BOOL InitiateMutex(BOOL fCreate);
	void CloseMutex();
	HANDLE GetMutexHandle();
	DWORD GetError();
	_TCHAR* GetMutexName();
};

