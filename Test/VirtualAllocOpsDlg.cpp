// VirtualAllocOpsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "VirtualAllocOpsDlg.h"
#include "afxdialogex.h"
#include "VirtualAllocOpsNew.h"
#include "VirtualAllocOpsCommit.h"


// VirtualAllocOpsDlg dialog

IMPLEMENT_DYNAMIC(VirtualAllocOpsDlg, CDialogEx)

VirtualAllocOpsDlg::VirtualAllocOpsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(VirtualAllocOpsDlg::IDD, pParent)	
{
	ResetVAEntry();
}

VirtualAllocOpsDlg::~VirtualAllocOpsDlg()
{
}

void VirtualAllocOpsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_VA_ENTRIES, m_lvEntries);
}


BEGIN_MESSAGE_MAP(VirtualAllocOpsDlg, CDialogEx)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_VA_ENTRIES, &VirtualAllocOpsDlg::OnNMRClickListVaEntries)
	ON_COMMAND(ID_NEW_NEW, &VirtualAllocOpsDlg::OnNewNew)
	ON_COMMAND(ID_NEW_COMMIT, &VirtualAllocOpsDlg::OnNewCommit)
	ON_COMMAND(ID_NEW_FREE, &VirtualAllocOpsDlg::OnNewFree)
	ON_COMMAND(ID__NEW_FILL, &VirtualAllocOpsDlg::OnNewFill )
END_MESSAGE_MAP()


// VirtualAllocOpsDlg message handlers


void VirtualAllocOpsDlg::SetControls()
{
	m_lvEntries.InsertColumn(0, _T("Address"), LVCFMT_RIGHT, 100);
	m_lvEntries.InsertColumn(1, _T("Size (MB)"), LVCFMT_RIGHT, 60);
	m_lvEntries.InsertColumn(2, _T("Reserved (MB)"), LVCFMT_RIGHT, 100);
	m_lvEntries.InsertColumn(3, _T("Committed (MB)"), LVCFMT_RIGHT, 100);
	m_lvEntries.InsertColumn(4, _T("Protection"), LVCFMT_RIGHT, 130);
	m_lvEntries.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT);

}


BOOL VirtualAllocOpsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	SetControls();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void VirtualAllocOpsDlg::ResetVAEntry()
{
	m_VAEntry.dwAllocType = 0;
	m_VAEntry.dwGLE = S_OK;
	m_VAEntry.dwProtection = 0;
	m_VAEntry.lCommitSize = 0;
	m_VAEntry.lReservedSize = 0;
	m_VAEntry.lTotalSize = 0;
	m_VAEntry.pAddress = NULL;
}

void VirtualAllocOpsDlg::OnNMRClickListVaEntries(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	CMenu      mnContext;

	if (!mnContext.LoadMenu(IDR_MENU_VA_OPS_CX_MN))
	{
		*pResult = 0;
		return;
	}

	CMenu      *pSubMenu = mnContext.GetSubMenu(0);
	POINT      oPoint;

	GetCursorPos(&oPoint);

	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
		oPoint.x,
		oPoint.y,
		this);

	pSubMenu->DestroyMenu();
	mnContext.DestroyMenu();

	*pResult = 0;
}

void VirtualAllocOpsDlg::LVAddData(CListCtrl &ctrl, int row, int col, const _TCHAR *str)
{
	LVITEM lv;

	lv.iItem = row;
	lv.iSubItem = col;
	lv.pszText = (_TCHAR*)str;
	lv.mask = LVIF_TEXT;

	if (col == 0)
		ctrl.InsertItem(&lv);
	else
		ctrl.SetItem(&lv);

}

void VirtualAllocOpsDlg::LVUpdateData(CListCtrl &ctrl, int row, int col, const _TCHAR *str)
{
	LVITEM lv;

	lv.iItem = row;
	lv.iSubItem = col;
	lv.pszText = (_TCHAR*)str;
	lv.mask = LVIF_TEXT;

	ctrl.SetItem(&lv);
}

void VirtualAllocOpsDlg::InsertAllocation()
{
	int			i = 0;
	VAENTRYITEM	*pVAEntryItem = NULL;

	pVAEntryItem = ConvertVaEntryToItem(&m_VAEntry);

	i = m_lvEntries.GetItemCount();

	LVAddData(m_lvEntries, i, 0, pVAEntryItem->szAddress);
	LVAddData(m_lvEntries, i, 1, pVAEntryItem->szTotalSize);
	LVAddData(m_lvEntries, i, 2, pVAEntryItem->szReservedSize);
	LVAddData(m_lvEntries, i, 3, pVAEntryItem->szCommitSize);
	LVAddData(m_lvEntries, i, 4, pVAEntryItem->szProtection);

	//free(pVAEntryItem);
}

void VirtualAllocOpsDlg::UpdateAllocation(int iRow)
{
	VAENTRYITEM *pvaei = NULL;
		
	iRow = m_lvEntries.GetSelectionMark();

	
	pvaei = ConvertVaEntryToItem(&m_VAEntry);

	LVUpdateData(m_lvEntries, iRow, 2, pvaei->szReservedSize);
	LVUpdateData(m_lvEntries, iRow, 3, pvaei->szCommitSize);
	free(pvaei);
}

void VirtualAllocOpsDlg::DeleteAllocation(int iRow)
{
	m_lvEntries.DeleteItem(iRow);
}

VAENTRY* VirtualAllocOpsDlg::GetVAEntryFromLV(int iRow)
{
	VAENTRYITEM* vaei = (VAENTRYITEM*)malloc(sizeof(VAENTRYITEM));
	VAENTRY		*pvae = NULL;

	_stprintf_s(vaei->szAddress, 30, m_lvEntries.GetItemText(iRow, 0));		// start address
	_stprintf_s(vaei->szTotalSize, 30, m_lvEntries.GetItemText(iRow, 1));		// total size
	_stprintf_s(vaei->szReservedSize, 30, m_lvEntries.GetItemText(iRow, 2));	// reserved size
	_stprintf_s(vaei->szCommitSize, 30, m_lvEntries.GetItemText(iRow, 3));		// committed size
	_stprintf_s(vaei->szProtection, 20, m_lvEntries.GetItemText(iRow, 4));		// allocation protection

	pvae = ConvertVaEntryItemToEntry(vaei);
	return pvae;
}

int VirtualAllocOpsDlg::filterFunc(unsigned int code, struct _EXCEPTION_POINTERS *ep)
{

	if (code == EXCEPTION_ACCESS_VIOLATION)
		return EXCEPTION_EXECUTE_HANDLER;
	else
		return EXCEPTION_CONTINUE_SEARCH;

}

void VirtualAllocOpsDlg::BlockFill(_TCHAR* pStartAddress, int iSize)
{
	_TCHAR	szMessage[100];
	size_t sizeSet = (int64_t)iSize * (int64_t) 1024 * (int64_t)1024 / sizeof(_TCHAR);
	__try
	{
		wmemset(pStartAddress, 'A', sizeSet);		
	}
	__except (filterFunc(GetExceptionCode(), GetExceptionInformation()))
	{
		_stprintf_s(szMessage, 100, _T("Exception happened. Code : 0x%x "), GetExceptionCode());
		AfxMessageBox(szMessage, MB_ICONERROR, 0);
	}
}

void VirtualAllocOpsDlg::OnNewNew()
{
	VirtualAllocOpsNew vaOpsNew;
	_TCHAR	szMessage[100];

	ResetVAEntry();
	vaOpsNew.SetParentDialog(this);


	if (IDOK == vaOpsNew.DoModal())
	{
		if (NULL == this->m_VAEntry.pAddress)
		{
			_stprintf_s(szMessage, 100, _T("Memory allocation failed with error 0x%x"), this->m_VAEntry.dwGLE);
			AfxMessageBox(szMessage, MB_ICONERROR, 0);
		}
		else
		{
			// Calculate the reserved and committed area sizes
			if (m_VAEntry.dwAllocType == MEM_RESERVE)
			{
				m_VAEntry.lReservedSize = m_VAEntry.lTotalSize;
				m_VAEntry.lCommitSize = 0;
			}
			else
			{
				m_VAEntry.lReservedSize = 0;
				m_VAEntry.lCommitSize = m_VAEntry.lTotalSize;
			}

			InsertAllocation();
		}

	}
}

void VirtualAllocOpsDlg::OnNewCommit()
{
	int			iRow = 0;
	_TCHAR		szMessage[100];
	VAENTRY		*pvae = NULL;

	iRow = m_lvEntries.GetSelectionMark();

	if (-1 == iRow)
		return;


	pvae = GetVAEntryFromLV(iRow);

	// check validity conditions for commit operations return if nothing to commit

	if (pvae->lCommitSize == pvae->lTotalSize)
	{
		free(pvae);
		return;
	}

	ResetVAEntry();
	m_VAEntry.pAddress = pvae->pAddress;
	m_VAEntry.dwAllocType = pvae->dwAllocType;
	m_VAEntry.dwGLE = pvae->dwGLE;
	m_VAEntry.dwProtection = pvae->dwProtection;
	m_VAEntry.lCommitSize = pvae->lCommitSize;
	m_VAEntry.lReservedSize = pvae->lReservedSize;
	m_VAEntry.lTotalSize = pvae->lTotalSize;

	pvae->pAddress = pvae->pAddress + (pvae->lCommitSize * 1024 * 1024 / sizeof(_TCHAR));


	// calculate the correct start address for commitment
	// call the commit dialog and functions before hand
	VirtualAllocOpsCommit vaOpsCommit;

	vaOpsCommit.SetParentDialog(this);
	vaOpsCommit.SetCommitParams(pvae->pAddress, pvae->lReservedSize, pvae->dwProtection);

	if (IDOK == vaOpsCommit.DoModal())
	{
		if (NULL == this->m_VAEntry.pAddress)
		{
			_stprintf_s(szMessage, 100, _T("Memory commitment failed with error 0x%x"), this->m_VAEntry.dwGLE);
			AfxMessageBox(szMessage, MB_ICONERROR, 0);
		}
		else
		{
			UpdateAllocation(iRow);
		}
	}

	//free(pvae);
}

void VirtualAllocOpsDlg::OnNewFill()
{
	int			iRow = 0;
	VAENTRY		*pvae = NULL;
		
	iRow = m_lvEntries.GetSelectionMark();

	if (-1 == iRow)
		return;
	
	ResetVAEntry();
	pvae = GetVAEntryFromLV(iRow);

	// check validity conditions for commit operations return if nothing to commit

	if (pvae->lCommitSize == 0)
	{
		free(pvae);
		return;
	}

	VirtualAllocOpsDlg::BlockFill(pvae->pAddress, pvae->lCommitSize);

	//free(pvae);

}

void VirtualAllocOpsDlg::OnNewFree()
{
	int			iRow = 0;
	int			iSelectedCount = 0;
	VAENTRY		*pvae = NULL;
	POSITION	pos;
	_TCHAR		szMessage[100];

	iRow = m_lvEntries.GetSelectionMark();

			
	pos = m_lvEntries.GetFirstSelectedItemPosition();
	if (NULL == pos)
	{
		return;
	}
	else
	{
		while (pos)
		{
			iRow = m_lvEntries.GetNextSelectedItem(pos);
			pvae = GetVAEntryFromLV(iRow);

			if (!::VirtualFree(pvae->pAddress, 0, MEM_RELEASE))
			{
				_stprintf_s(szMessage, 100, _T("Memory could not be freed. Error : 0x%x "), GetLastError());
				AfxMessageBox(szMessage, MB_ICONERROR, 0);
				free(pvae);
				return;
			}
			
			free(pvae);
			pvae = NULL;
			m_lvEntries.DeleteItem(iRow);			
			pos = m_lvEntries.GetFirstSelectedItemPosition();
		}
	}
	
}

