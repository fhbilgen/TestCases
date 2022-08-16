#pragma once

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the TESTHELPERS_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// TESTHELPERS_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef TESTHELPERS_EXPORTS
#define TESTHELPERS_API  __declspec(dllexport) 
#else
#define TESTHELPERS_API  __declspec(dllimport)
#endif

// This class is exported from the TestHelpers.dll
class TESTHELPERS_API CTestHelpers {
public:
	CTestHelpers(void);
	// TODO: add your methods here.
};

extern TESTHELPERS_API int nTestHelpers;

TESTHELPERS_API int fnTestHelpers(void);



typedef struct {
	_TCHAR wszAddress[30];
	_TCHAR wszTotalSize[30];
	_TCHAR wszReservedSize[30];
	_TCHAR wszCommitSize[30];
	_TCHAR wszAllocType[20];
	_TCHAR wszProtection[20];
} VAENTRYITEM, *PVAENTRYITEM;


typedef struct {
	_TCHAR	*pAddress;
	long	lTotalSize;	
	long	lReservedSize;	
	long	lCommitSize;
	DWORD	dwAllocType;
	DWORD	dwProtection;
	DWORD	dwGLE;
} VAENTRY, *PVAENTRY;

typedef struct{
	_TCHAR	wszFileName[MAX_PATH];
	long	lFileSize;
	BOOL	fFlushBuffer;
	DWORD	dwFlags;
}FILEPROPS, *PFILEPROPS;

typedef struct{
	_TCHAR	wszPath[MAX_PATH];
	long	lFileSize;
	long	lBufferSize;
	long	lNumOfFiles;
	BOOL	fFlushBuffer;
	DWORD	dwFlags;	// New added be careful !!!
} IOOPENTRY, *PIOOPENTRY;

typedef struct{
	_TCHAR	wszPath[MAX_PATH];
	_TCHAR	wszFileSize[20];
	_TCHAR	wszBufferSize[20];
	_TCHAR	wszNumOfFiles[20];
	_TCHAR	wszFlushBuffer[10];
	_TCHAR	wszFlags;	// New added be careful !!!
} IOOPENTRYITEM, *PIOOPENTRYITEM;


#define NO_NAME_MANGLING extern "C"

NO_NAME_MANGLING TESTHELPERS_API VAENTRYITEM* ConvertVaEntryToItem(VAENTRY* pVaEntry);
NO_NAME_MANGLING TESTHELPERS_API VAENTRY* ConvertVaEntryItemToEntry(VAENTRYITEM* pVaEntryItem);

NO_NAME_MANGLING TESTHELPERS_API IOOPENTRYITEM* ConvertIOOPEntryToItem(IOOPENTRY* pIOOPEntry);
NO_NAME_MANGLING TESTHELPERS_API IOOPENTRY* ConvertIOOPEntryItemToIOOPEntry(IOOPENTRYITEM* pIOOPEntryItem);

NO_NAME_MANGLING TESTHELPERS_API void InitializeAndFillTheBuffer(int BufferSize);

NO_NAME_MANGLING TESTHELPERS_API DWORD WINAPI CreateWriteCloseFile(LPVOID lpParam);
NO_NAME_MANGLING TESTHELPERS_API DWORD WINAPI CreateWriteCloseFileSlow(LPVOID lpParam);
