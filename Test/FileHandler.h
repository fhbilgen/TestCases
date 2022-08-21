#pragma once
class FileHandler
{
private:
	DWORD dwLastError = S_OK;
	HANDLE hFile = NULL;	
	_TCHAR* szPath = NULL;
	_TCHAR szFileName[20] = _T("FileHandleTest.txt");
	_TCHAR szFirstLine[30] = _T("This is the first line.");

public:
	BOOL InitiateFile(BOOL fOverWrite);
	void CloseFile();
	HANDLE GetFileHandle();
	_TCHAR* GetFilePath();
	DWORD GetError();
};

