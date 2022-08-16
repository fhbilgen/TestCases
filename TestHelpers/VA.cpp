#include "stdafx.h"


VAENTRYITEM* ConvertVaEntryToItem(VAENTRY* pVaEntry)
{
	VAENTRYITEM	*pvaei = NULL;
	_TCHAR wsAddr[30];

	pvaei = (VAENTRYITEM*)malloc(sizeof(VAENTRYITEM));

	if (NULL == pvaei)
		return pvaei;
	
	_stprintf_s(pvaei->wszAddress, 30, _T("0x%I64x"), pVaEntry->pAddress);	
	_stprintf_s(wsAddr, 30, _T("0x%I64x"), pVaEntry->pAddress);

	_stprintf_s(pvaei->wszTotalSize, 30, _T("%d"), pVaEntry->lTotalSize);
	_stprintf_s(pvaei->wszReservedSize, 30, _T("%d"), pVaEntry->lReservedSize);
	_stprintf_s(pvaei->wszCommitSize, 30, _T("%d"), pVaEntry->lCommitSize);

	switch (pVaEntry->dwAllocType)
	{
	case MEM_RESERVE:
		_stprintf_s(pvaei->wszAllocType, 20, _T("%s"), _T("RESERVED"));
		break;
	case MEM_COMMIT:
		_stprintf_s(pvaei->wszAllocType, 20, _T("%s"), _T("COMMITTED"));
		break;
	case MEM_RESERVE | MEM_COMMIT:
		_stprintf_s(pvaei->wszAllocType, 20, _T("%s"), _T("COMMITTED"));
		break;
	default:
		break;
	}

	switch (pVaEntry->dwProtection)
	{
	case PAGE_EXECUTE:
		_stprintf_s(pvaei->wszProtection, 20, _T("%s"), _T("EXECUTE"));
		break;

	case PAGE_EXECUTE_READ:
		_stprintf_s(pvaei->wszProtection, 20, _T("%s"), _T("EXECUTE READ"));
		break;

	case PAGE_EXECUTE_READWRITE:
		_stprintf_s(pvaei->wszProtection, 20, _T("%s"), _T("EXECUTE READ/WRITE"));
		break;

	case PAGE_NOACCESS:
		_stprintf_s(pvaei->wszProtection, 20, _T("%s"), _T("NO ACCESS"));
		break;

	case PAGE_READONLY:
		_stprintf_s(pvaei->wszProtection, 20, _T("%s"), _T("READ ONLY"));
		break;

	case PAGE_READWRITE:
		_stprintf_s(pvaei->wszProtection, 20, _T("%s"), _T("READ/WRITE"));
		break;

	default:
		_stprintf_s(pvaei->wszProtection, 20, _T("%s"), _T(""));
		break;
	}

	return pvaei;
}

VAENTRY* ConvertVaEntryItemToEntry(VAENTRYITEM* pVaEntryItem)
{
	VAENTRY* pvae = NULL;
	//_TCHAR	*pwszStop;

	//INT64 x;

	pvae = (VAENTRY*)malloc(sizeof(VAENTRY));

	if (NULL == pvae)
		return pvae;

	//pvae->pAddress = reinterpret_cast<_TCHAR*> (_tcstol(pVaEntryItem->wszAddress, &pwszStop, 16));
	//x = _tcstoull(pVaEntryItem->wszAddress, NULL, 16);
	

	pvae->pAddress = reinterpret_cast<_TCHAR*> (_tcstoull(pVaEntryItem->wszAddress, NULL, 16));
	
	pvae->lTotalSize = _wtol(pVaEntryItem->wszTotalSize);
	pvae->lCommitSize = _wtol(pVaEntryItem->wszCommitSize);
	pvae->lReservedSize = _wtol(pVaEntryItem->wszReservedSize);	
	pvae->dwAllocType = 0;
	pvae->dwProtection = 0;
	pvae->dwGLE = S_OK;
	
	if (0 == _tcscmp(pVaEntryItem->wszAllocType, _T("RESERVED")))
	{
		pvae->dwAllocType = MEM_RESERVE;
	}
	else
	{
		if (0 == _tcscmp(pVaEntryItem->wszAllocType, _T("COMMITTED")))
		{
			pvae->dwAllocType = MEM_COMMIT;
		}
	}
	
	if (0 == _tcscmp(pVaEntryItem->wszProtection, _T("EXECUTE")))
	{
		pvae->dwProtection = PAGE_EXECUTE;
	}

	if (0 == _tcscmp(pVaEntryItem->wszProtection, _T("EXECUTE READ")))
	{
		pvae->dwProtection = PAGE_EXECUTE_READ;
	}

	if (0 == _tcscmp(pVaEntryItem->wszProtection, _T("EXECUTE READ/WRITE")))
	{
		pvae->dwProtection = PAGE_EXECUTE_READWRITE;
	}
	
	if (0 == _tcscmp(pVaEntryItem->wszProtection, _T("NO ACCESS")))
	{
		pvae->dwProtection = PAGE_NOACCESS;
	}
	
	if (0 == _tcscmp(pVaEntryItem->wszProtection, _T("READ ONLY")))
	{
		pvae->dwProtection = PAGE_READONLY;
	}
	
	if (0 == _tcscmp(pVaEntryItem->wszProtection, _T("READ/WRITE")))
	{
		pvae->dwProtection = PAGE_READWRITE;
	}

	return pvae;
}