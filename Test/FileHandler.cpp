#include "stdafx.h"
#include "FileHandler.h"

BOOL FileHandler::InitiateFile(BOOL fOverWrite)
{
	TCHAR** lppPart = { NULL };
	DWORD dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
	DWORD dwShareMode = FILE_SHARE_READ;
	DWORD dwCreationDisposition = 0;
	DWORD dwFlagsAndAttributes = FILE_ATTRIBUTE_NORMAL;
	DWORD dwBytesOut = 0;

	if (fOverWrite)
		dwCreationDisposition = CREATE_ALWAYS;
	else
		dwCreationDisposition = OPEN_ALWAYS;

	// Open the file
	hFile = CreateFile(szFileName, dwDesiredAccess, dwShareMode, NULL, dwCreationDisposition, dwFlagsAndAttributes, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		dwLastError = GetLastError();		
		return FALSE;
	}

	// Write a simple line into the file. If it fails then close the file handle
	if (! WriteFile(hFile, (VOID*)szFirstLine, _tcslen(szFirstLine) + 1, &dwBytesOut, NULL))
	{
		dwLastError = GetLastError();
		CloseHandle(hFile);
		return FALSE;
	}
	
	// Get the full path length
	dwBytesOut = GetFullPathName(szFileName, 0, szPath, lppPart);

	if (0 == dwBytesOut)
	{
		dwLastError = GetLastError();
		CloseHandle(hFile);
		return FALSE;
	}

	// Allocate memory for the path
	szPath = (_TCHAR*)malloc(sizeof(_TCHAR) * dwBytesOut);
	if (szPath == NULL)
	{
		dwLastError = GetLastError();
		CloseHandle(hFile);
		return FALSE;
	}
	
	// Set the full path
	dwBytesOut = GetFullPathName(szFileName, dwBytesOut, szPath, lppPart);
	if (0 == dwBytesOut)
	{
		dwLastError = GetLastError();
		CloseHandle(hFile);
		free(szPath);
		szPath = NULL;
		return FALSE;
	}

	return TRUE;
}

void FileHandler::CloseFile()
{
	if (INVALID_HANDLE_VALUE != hFile)
	{
		CloseHandle(hFile);
		hFile = NULL;
		free(szPath);
		szPath = NULL;
	}
}

HANDLE FileHandler::GetFileHandle()
{

	return hFile;
}

_TCHAR* FileHandler::GetFilePath()
{
	return szPath;
}

DWORD FileHandler::GetError()
{
	return dwLastError;
}