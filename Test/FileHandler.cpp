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
	m_hFile = CreateFile(m_szFileName, dwDesiredAccess, dwShareMode, NULL, dwCreationDisposition, dwFlagsAndAttributes, NULL);

	if (INVALID_HANDLE_VALUE == m_hFile)
	{
		m_dwLastError = GetLastError();
		return FALSE;
	}

	// Write a simple line into the file. If it fails then close the file handle
	if (! WriteFile(m_hFile, (VOID*)m_szFirstLine, sizeof(_TCHAR)*(_tcslen(m_szFirstLine) + 1), &dwBytesOut, NULL))
	{
		m_dwLastError = GetLastError();
		CloseHandle(m_hFile);
		return FALSE;
	}
	
	// Get the full path length
	dwBytesOut = GetFullPathName(m_szFileName, 0, m_szPath, lppPart);

	if (0 == dwBytesOut)
	{
		m_dwLastError = GetLastError();
		CloseHandle(m_hFile);
		return FALSE;
	}

	// Allocate memory for the path
	m_szPath = (_TCHAR*)malloc(sizeof(_TCHAR) * dwBytesOut);
	if (m_szPath == NULL)
	{
		m_dwLastError = GetLastError();
		CloseHandle(m_hFile);
		return FALSE;
	}
	
	// Set the full path
	dwBytesOut = GetFullPathName(m_szFileName, dwBytesOut, m_szPath, lppPart);
	if (0 == dwBytesOut)
	{
		m_dwLastError = GetLastError();
		CloseHandle(m_hFile);
		free(m_szPath);
		m_szPath = NULL;
		return FALSE;
	}

	return TRUE;
}

void FileHandler::CloseFile()
{
	if (INVALID_HANDLE_VALUE != m_hFile)
	{
		CloseHandle(m_hFile);
		m_hFile = NULL;
		free(m_szPath);
		m_szPath = NULL;
	}
}

HANDLE FileHandler::GetFileHandle()
{
	return m_hFile;
}

_TCHAR* FileHandler::GetFilePath()
{
	return m_szPath;
}

DWORD FileHandler::GetError()
{
	return m_dwLastError;
}