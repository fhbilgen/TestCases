#pragma once

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the CASES_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// CASES_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef CASES_EXPORTS
#define CASES_API __declspec(dllexport)
#else
#define CASES_API __declspec(dllimport)
#endif


#define NO_NAME_MANGLING extern "C"
// Exported Functions
// For hang / wait cases
NO_NAME_MANGLING CASES_API void CreateDeadlock(void);
NO_NAME_MANGLING CASES_API void WaitOnOrphantCS(void);
NO_NAME_MANGLING CASES_API void  HiCPUUtilization(int iNumOfCores, HANDLE hStopEvent);
NO_NAME_MANGLING CASES_API BOOL GetResource();
NO_NAME_MANGLING CASES_API BOOL ReleaseResource();
// For crash cases
NO_NAME_MANGLING CASES_API void AccessViolate();
NO_NAME_MANGLING CASES_API void AccessViolateHeapCorrupt();
NO_NAME_MANGLING CASES_API void AccessViolateVAReserve();
NO_NAME_MANGLING CASES_API void AccessViolateAndHandle();
NO_NAME_MANGLING CASES_API void DivisionByZero();
NO_NAME_MANGLING CASES_API void StackOverflow(int iFact);

class CASES_API Sync
{
public:
	Sync(void);
	~Sync(void);

	void AccessFirstResource(void);
	void AccessSecondResource(void);
	void ReleaseFirstResource(void);
	void ReleaseSecondResource(void);

private:
	CRITICAL_SECTION m_csA;
	CRITICAL_SECTION m_csB;
};

