#include "stdafx.h"


VAENTRYITEM* ConvertVaEntryToItem(VAENTRY* pVaEntry)
{
	VAENTRYITEM	*pvaei = NULL;
	_TCHAR wsAddr[30];

	pvaei = (VAENTRYITEM*)malloc(sizeof(VAENTRYITEM));

	if (NULL == pvaei)
		return pvaei;
	
	_stprintf_s(pvaei->szAddress, 30, _T("0x%I64x"), pVaEntry->pAddress);	
	_stprintf_s(wsAddr, 30, _T("0x%I64x"), pVaEntry->pAddress);

	_stprintf_s(pvaei->szTotalSize, 30, _T("%d"), pVaEntry->lTotalSize);
	_stprintf_s(pvaei->szReservedSize, 30, _T("%d"), pVaEntry->lReservedSize);
	_stprintf_s(pvaei->szCommitSize, 30, _T("%d"), pVaEntry->lCommitSize);

	switch (pVaEntry->dwAllocType)
	{
	case MEM_RESERVE:
		_stprintf_s(pvaei->szAllocType, 20, _T("%s"), _T("RESERVED"));
		break;
	case MEM_COMMIT:
		_stprintf_s(pvaei->szAllocType, 20, _T("%s"), _T("COMMITTED"));
		break;
	case MEM_RESERVE | MEM_COMMIT:
		_stprintf_s(pvaei->szAllocType, 20, _T("%s"), _T("COMMITTED"));
		break;
	default:
		break;
	}

	switch (pVaEntry->dwProtection)
	{
	case PAGE_EXECUTE:
		_stprintf_s(pvaei->szProtection, 20, _T("%s"), _T("EXECUTE"));
		break;

	case PAGE_EXECUTE_READ:
		_stprintf_s(pvaei->szProtection, 20, _T("%s"), _T("EXECUTE READ"));
		break;

	case PAGE_EXECUTE_READWRITE:
		_stprintf_s(pvaei->szProtection, 20, _T("%s"), _T("EXECUTE READ/WRITE"));
		break;

	case PAGE_NOACCESS:
		_stprintf_s(pvaei->szProtection, 20, _T("%s"), _T("NO ACCESS"));
		break;

	case PAGE_READONLY:
		_stprintf_s(pvaei->szProtection, 20, _T("%s"), _T("READ ONLY"));
		break;

	case PAGE_READWRITE:
		_stprintf_s(pvaei->szProtection, 20, _T("%s"), _T("READ/WRITE"));
		break;

	default:
		_stprintf_s(pvaei->szProtection, 20, _T("%s"), _T(""));
		break;
	}

	return pvaei;
}

VAENTRY* ConvertVaEntryItemToEntry(VAENTRYITEM* pVaEntryItem)
{
	VAENTRY* pvae = NULL;
	//_TCHAR	*pszStop;

	//INT64 x;

	pvae = (VAENTRY*)malloc(sizeof(VAENTRY));

	if (NULL == pvae)
		return pvae;

	//pvae->pAddress = reinterpret_cast<_TCHAR*> (_tcstol(pVaEntryItem->szAddress, &pszStop, 16));
	//x = _tcstoull(pVaEntryItem->szAddress, NULL, 16);
	

	pvae->pAddress = reinterpret_cast<_TCHAR*> (_tcstoull(pVaEntryItem->szAddress, NULL, 16));
	
	pvae->lTotalSize = _wtol(pVaEntryItem->szTotalSize);
	pvae->lCommitSize = _wtol(pVaEntryItem->szCommitSize);
	pvae->lReservedSize = _wtol(pVaEntryItem->szReservedSize);	
	pvae->dwAllocType = 0;
	pvae->dwProtection = 0;
	pvae->dwGLE = S_OK;
	
	if (0 == _tcscmp(pVaEntryItem->szAllocType, _T("RESERVED")))
	{
		pvae->dwAllocType = MEM_RESERVE;
	}
	else
	{
		if (0 == _tcscmp(pVaEntryItem->szAllocType, _T("COMMITTED")))
		{
			pvae->dwAllocType = MEM_COMMIT;
		}
	}
	
	if (0 == _tcscmp(pVaEntryItem->szProtection, _T("EXECUTE")))
	{
		pvae->dwProtection = PAGE_EXECUTE;
	}

	if (0 == _tcscmp(pVaEntryItem->szProtection, _T("EXECUTE READ")))
	{
		pvae->dwProtection = PAGE_EXECUTE_READ;
	}

	if (0 == _tcscmp(pVaEntryItem->szProtection, _T("EXECUTE READ/WRITE")))
	{
		pvae->dwProtection = PAGE_EXECUTE_READWRITE;
	}
	
	if (0 == _tcscmp(pVaEntryItem->szProtection, _T("NO ACCESS")))
	{
		pvae->dwProtection = PAGE_NOACCESS;
	}
	
	if (0 == _tcscmp(pVaEntryItem->szProtection, _T("READ ONLY")))
	{
		pvae->dwProtection = PAGE_READONLY;
	}
	
	if (0 == _tcscmp(pVaEntryItem->szProtection, _T("READ/WRITE")))
	{
		pvae->dwProtection = PAGE_READWRITE;
	}

	return pvae;
}