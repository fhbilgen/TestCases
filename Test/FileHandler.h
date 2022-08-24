#pragma once
class FileHandler
{
private:
	DWORD m_dwLastError = S_OK;
	HANDLE m_hFile = NULL;	
	_TCHAR* m_szPath = NULL;
	_TCHAR m_szFileName[20] = _T("FileHandleTest.txt");
	_TCHAR m_szFirstLine[30] = _T("This is the first line.");

public:
	BOOL InitiateFile(BOOL fOverWrite);
	void CloseFile();
	HANDLE GetFileHandle();
	_TCHAR* GetFilePath();
	DWORD GetError();
};

