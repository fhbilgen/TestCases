#include "stdafx.h"

char	*g_chBuffer = NULL;
long	g_lBufferSize = 0;


void InitializeAndFillTheBuffer(int BufferSize)
{
	int	delta = 0;
	if (NULL != g_chBuffer)
	{
		free(g_chBuffer);
		g_chBuffer = NULL;
	}

	g_chBuffer = (char*)malloc(sizeof(char)*BufferSize);
	if (NULL == g_chBuffer)
		return;

	g_lBufferSize = BufferSize;
	for (int i = 0; i != BufferSize; i++)
	{
		g_chBuffer[i] = 65 + (i % 26);
	};
}

DWORD WINAPI CreateWriteCloseFile(LPVOID lpParam)
{
	FILEPROPS	*fp = NULL;
	HANDLE		hFile = NULL;
	int			CounterUpperLimit = 0;	
	DWORD		dwNumberOfBytesWritten = 0;
	DWORD		dwError = S_OK;

	fp = (FILEPROPS*)lpParam;
	
	hFile = CreateFile(fp->szFileName, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, fp->dwFlags, NULL);	
	
	if (hFile == INVALID_HANDLE_VALUE)
	{				
		dwError = GetLastError();
		return dwError;
	}

	CounterUpperLimit = (int)(fp->lFileSize / g_lBufferSize);

	for (int i = 0; i != CounterUpperLimit; i++)
	{
		if (!WriteFile(hFile, (void*)g_chBuffer, g_lBufferSize, &dwNumberOfBytesWritten, NULL))
		{
			CloseHandle(hFile);
			return GetLastError();
		}
		if (fp->fFlushBuffer)
			FlushFileBuffers(hFile);
	}

	if (fp->fFlushBuffer)
		FlushFileBuffers(hFile);
	
	CloseHandle(hFile);

	return 0;
}

DWORD WINAPI CreateWriteCloseFileSlow(LPVOID lpParam)
{
	FILEPROPS	*fp = NULL;
	HANDLE		hFile = NULL;
	int			CounterUpperLimit = 0;
	DWORD		dwNumberOfBytesWritten = 0;
	DWORD		dwError = S_OK;

	fp = (FILEPROPS*)lpParam;

	hFile = CreateFile(fp->szFileName, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, fp->dwFlags, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		dwError = GetLastError();
		return dwError;
	}

	CounterUpperLimit = (int)(fp->lFileSize / g_lBufferSize);

	for (int i = 0; i != CounterUpperLimit; i++)
	{
		for (int j=0; j!= g_lBufferSize; j++)
			if (!WriteFile(hFile, &(g_chBuffer[j]), 1, &dwNumberOfBytesWritten, NULL))
			{
				CloseHandle(hFile);
				return GetLastError();
			}

		/*if (!WriteFile(hFile, (void*)g_chBuffer, g_lBufferSize, &dwNumberOfBytesWritten, NULL))
		{
			CloseHandle(hFile);
			return GetLastError();
		}*/

		if (fp->fFlushBuffer)
			FlushFileBuffers(hFile);
	}

	if (fp->fFlushBuffer)
		FlushFileBuffers(hFile);

	CloseHandle(hFile);

	return 0;
}

IOOPENTRYITEM* ConvertIOOPEntryToItem(IOOPENTRY* pIOOPEntry)
{
	IOOPENTRYITEM *pIOOPEntryItem = NULL;

	pIOOPEntryItem = (IOOPENTRYITEM*)malloc(sizeof(IOOPENTRYITEM));

	if (NULL == pIOOPEntryItem)
		return pIOOPEntryItem;
	
	_stprintf_s(pIOOPEntryItem->szBufferSize, 20, _T("%d"), pIOOPEntry->lBufferSize   );
	_stprintf_s(pIOOPEntryItem->szFileSize, 20, _T("%d"), pIOOPEntry->lFileSize);
	_stprintf_s(pIOOPEntryItem->szNumOfFiles, 20, _T("%d"), pIOOPEntry->lNumOfFiles);
	
	if (pIOOPEntry->fFlushBuffer)
	{
		_stprintf_s(pIOOPEntryItem->szFlushBuffer, 20, _T("TRUE"));
	}
	else
	{
		_stprintf_s(pIOOPEntryItem->szFlushBuffer, 20, _T("FALSE"));
	}
	
	return pIOOPEntryItem;
}

IOOPENTRY* ConvertIOOPEntryItemToIOOPEntry(IOOPENTRYITEM* pIOOPEntryItem)
{
	IOOPENTRY*	pIOOPEntry = NULL;

	pIOOPEntry = (IOOPENTRY*)malloc(sizeof(IOOPENTRY));
	if (NULL == pIOOPEntry)
		return pIOOPEntry;

	
	if ( 0 == _tcscmp(pIOOPEntryItem->szFlushBuffer, _T("TRUE")))
		pIOOPEntry->fFlushBuffer = TRUE;
	else
		pIOOPEntry->fFlushBuffer = FALSE;

	pIOOPEntry->lBufferSize = _wtol( pIOOPEntryItem->szBufferSize );
	pIOOPEntry->lFileSize = _wtol( pIOOPEntryItem->szFileSize );
	pIOOPEntry->lNumOfFiles = _wtol( pIOOPEntryItem->szNumOfFiles );
	
	return pIOOPEntry;
}


