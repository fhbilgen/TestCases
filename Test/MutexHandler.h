#pragma once
class MutexHandler
{
private:
	DWORD m_dwLastError = S_OK;
	HANDLE m_hMutex = NULL;
	_TCHAR m_szMutexName[20] = _T("MUTEXTest");

public:
	BOOL InitiateMutex(BOOL fCreate);
	void CloseMutex();
	HANDLE GetMutexHandle();
	DWORD GetError();
	_TCHAR* GetMutexName();
};

