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
	_TCHAR szAddress[30];
	_TCHAR szTotalSize[30];
	_TCHAR szReservedSize[30];
	_TCHAR szCommitSize[30];
	_TCHAR szAllocType[20];
	_TCHAR szProtection[20];
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
	_TCHAR	szFileName[MAX_PATH];
	long	lFileSize;
	BOOL	fFlushBuffer;
	DWORD	dwFlags;
}FILEPROPS, *PFILEPROPS;

typedef struct{
	_TCHAR	szPath[MAX_PATH];
	long	lFileSize;
	long	lBufferSize;
	long	lNumOfFiles;
	BOOL	fFlushBuffer;
	DWORD	dwFlags;	// New added be careful !!!
} IOOPENTRY, *PIOOPENTRY;

typedef struct{
	_TCHAR	szPath[MAX_PATH];
	_TCHAR	szFileSize[20];
	_TCHAR	szBufferSize[20];
	_TCHAR	szNumOfFiles[20];
	_TCHAR	szFlushBuffer[10];
	_TCHAR	szFlags;	// New added be careful !!!
} IOOPENTRYITEM, *PIOOPENTRYITEM;


#define NO_NAME_MANGLING extern "C"

NO_NAME_MANGLING TESTHELPERS_API VAENTRYITEM* ConvertVaEntryToItem(VAENTRY* pVaEntry);
NO_NAME_MANGLING TESTHELPERS_API VAENTRY* ConvertVaEntryItemToEntry(VAENTRYITEM* pVaEntryItem);

NO_NAME_MANGLING TESTHELPERS_API IOOPENTRYITEM* ConvertIOOPEntryToItem(IOOPENTRY* pIOOPEntry);
NO_NAME_MANGLING TESTHELPERS_API IOOPENTRY* ConvertIOOPEntryItemToIOOPEntry(IOOPENTRYITEM* pIOOPEntryItem);

NO_NAME_MANGLING TESTHELPERS_API void InitializeAndFillTheBuffer(int BufferSize);

NO_NAME_MANGLING TESTHELPERS_API DWORD WINAPI CreateWriteCloseFile(LPVOID lpParam);
NO_NAME_MANGLING TESTHELPERS_API DWORD WINAPI CreateWriteCloseFileSlow(LPVOID lpParam);
