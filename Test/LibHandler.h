#pragma once

typedef int(__cdecl* OpAdd)(int, int);
typedef int(__cdecl* OpSub)(int, int);
typedef int(__cdecl* OpMul)(int, int);
typedef int(__cdecl* OpDiv)(int, int);

class LibHandler
{
private:
	DWORD m_dwLastError = S_OK;
	BOOL m_fLoaded = FALSE;
	HMODULE m_hLib = NULL;
	_TCHAR m_szLibName[20] = _T("Cases.dll");
	OpAdd m_fnAdd = NULL;
	OpSub m_fnSub = NULL;
	OpMul m_fnMul = NULL;
	OpDiv m_fnDiv = NULL;

public:
	BOOL LoadLib();
	BOOL LoadFnAddr();
	BOOL UnloadLib();
	void ZeroFnAddr();
	int Calculate(int a, int b, int op);
	BOOL GetLoadState();
	const _TCHAR* GetLoadStateMessage();
	DWORD GetError();
	
};

