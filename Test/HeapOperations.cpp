// HeapOperations.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "HeapOperations.h"
#include "afxdialogex.h"


// HeapOperations dialog

IMPLEMENT_DYNAMIC(HeapOperations, CDialogEx)

HeapOperations::HeapOperations(CWnd* pParent /*=NULL*/)
	: CDialogEx(HeapOperations::IDD, pParent)
	, m_InitHeapSize(0)
	, m_iCount(0)
	, m_iSize(0)
{	
	m_hHeap = NULL;
}

HeapOperations::~HeapOperations()
{
}

void HeapOperations::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_HEAP_OPS_INI_SIZE, m_edtInitHeapSize);
	DDX_Text(pDX, IDC_EDIT_HEAP_OPS_INI_SIZE, m_InitHeapSize);
	DDX_Control(pDX, IDC_STATIC_HEAP_OPS_NEW_HEAP, m_statNewHeap);
	DDX_Control(pDX, IDC_EDIT_HEAP_OPS_COUNT, m_edtCount);
	DDX_Text(pDX, IDC_EDIT_HEAP_OPS_COUNT, m_iCount);
	DDX_Text(pDX, IDC_EDIT_HEAP_OPS_SIZE, m_iSize);
	DDX_Control(pDX, IDC_LIST_HEAP_OPS_ENTRIES, m_lvHeapEntries);
	DDX_Control(pDX, IDC_EDIT_HEAP_OPS_SIZE, m_edtSize);
	DDX_Control(pDX, IDC_BUTTON_HEAP_OPS_NEW_HEAP, m_btnNewHeap);
}


BEGIN_MESSAGE_MAP(HeapOperations, CDialogEx)
	
	ON_BN_CLICKED(IDC_BUTTON_HEAP_OPS_NEW_HEAP, &HeapOperations::OnBnClickedButtonHeapOpsNewHeap)
	ON_EN_CHANGE(IDC_EDIT_HEAP_OPS_INI_SIZE, &HeapOperations::OnEnChangeEditHeapOpsIniSize)
	ON_BN_CLICKED(IDC_BUTTON_HEAP_OPS_ALLOC, &HeapOperations::OnBnClickedButtonHeapOpsAlloc)
	ON_EN_CHANGE(IDC_EDIT_HEAP_OPS_SIZE, &HeapOperations::OnEnChangeEditHeapOpsSize)
	ON_EN_CHANGE(IDC_EDIT_HEAP_OPS_COUNT, &HeapOperations::OnEnChangeEditHeapOpsCount)
	ON_BN_CLICKED(IDC_BUTTON_HEAP_OPS_FREE, &HeapOperations::OnBnClickedButtonHeapOpsFree)
END_MESSAGE_MAP()


// HeapOperations message handlers



void HeapOperations::OnBnClickedButtonHeapOpsNewHeap()
{
	//HANDLE hNewHeap = NULL;
	_TCHAR  wszDescription[100];

	m_hHeap = HeapCreate(HEAP_GENERATE_EXCEPTIONS, m_InitHeapSize * 1024 * 1024, 0);

	if (NULL != m_hHeap)
	{
		_stprintf_s(wszDescription, 100, _T("A new heap with handle 0x%llX is created"), (LONGLONG)m_hHeap);
		m_statNewHeap.SetWindowTextW(wszDescription);
		m_btnNewHeap.EnableWindow(FALSE);
	}
	else
		AfxMessageBox(_T("Error Happened"), MB_OK | MB_ICONERROR, 0);
		
}

BOOL HeapOperations::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	SetControls();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void HeapOperations::OnBnClickedButtonHeapOpsAlloc()
{
	char *cp = NULL;
	LVITEM *plv = NULL;
	_TCHAR	*wszAddress = NULL;
	_TCHAR	*wszSize = NULL;

	UpdateData(FALSE);

	BeginWaitCursor();
	for (int i = 0; i != m_iCount; i++)
	{
		cp = (char*)HeapAlloc(m_hHeap, HEAP_ZERO_MEMORY | HEAP_GENERATE_EXCEPTIONS, sizeof(char) * m_iSize);
		
		if (NULL == cp)
		{
			AfxMessageBox(_T("Could not allocate memory"), MB_OK|MB_ICONERROR, 0);
			return;
		}
		else
		{
			// We need to fill the allocated location			
			// col 0

			plv = (LVITEM*)malloc(sizeof(LVITEM));
			plv->iItem = m_lvHeapEntries.GetItemCount();
			plv->iSubItem = 0;
			wszAddress = (_TCHAR*)malloc(sizeof(_TCHAR) * 20);
			_stprintf_s(wszAddress, 18, _T("%p"), cp);
			plv->pszText = wszAddress;
			plv->mask = LVIF_TEXT;						
			m_lvHeapEntries.InsertItem(plv);

			// col 1
			plv->iSubItem = 1;
			wszSize = (TCHAR*)malloc(sizeof(_TCHAR) * 20);
			_stprintf_s(wszSize, 18, _T("%d"), m_iSize);
			plv->pszText = wszSize;
			plv->mask = LVIF_TEXT;
			m_lvHeapEntries.SetItem(plv);

			free(plv);
			free(wszAddress);
			free(wszSize);
			cp = NULL;
		}
	}
	EndWaitCursor();
	m_edtCount.SetWindowText(_T("0"));
	m_edtSize.SetWindowText(_T("0"));
	
}


void HeapOperations::SetControls()
{
	m_statNewHeap.SetWindowText(_T(""));
	m_edtCount.SetWindowText(_T("0"));
	m_edtSize.SetWindowText(_T("0"));
	m_edtInitHeapSize.SetWindowText(_T("0"));
	m_lvHeapEntries.InsertColumn(0, _T("Address"), LVCFMT_RIGHT, 150);
	m_lvHeapEntries.InsertColumn(1, _T("Size (bytes)"), LVCFMT_RIGHT, 150);
	m_lvHeapEntries.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT);
	
	UpdateData(TRUE);
}



void HeapOperations::OnEnChangeEditHeapOpsSize()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData(TRUE);
}


void HeapOperations::OnEnChangeEditHeapOpsCount()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData(TRUE);
}

void HeapOperations::OnEnChangeEditHeapOpsIniSize()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData(TRUE);
}

void HeapOperations::OnBnClickedButtonHeapOpsFree()
{
	int			iRow = 0;
	int			iSelectedCount = 0;
	__int64		charAddress = 0;
	char*		pch = NULL;
	POSITION	pos;
	_TCHAR		wszMessage[100];

	iRow = m_lvHeapEntries.GetSelectionMark();

	BeginWaitCursor();
	pos = m_lvHeapEntries.GetFirstSelectedItemPosition();
	if (NULL == pos)
	{
		return;
	}
	else
	{
		while (pos)
		{
			iRow = m_lvHeapEntries.GetNextSelectedItem(pos);
			charAddress = wcstol(m_lvHeapEntries.GetItemText(iRow, 0), NULL, 0);
			pch = (char*)charAddress;
			if ( !HeapFree(m_hHeap, HEAP_ZERO_MEMORY, pch ) )
			{
				_stprintf_s(wszMessage, 100, _T("Memory could not be freed. Error : 0x%x "), GetLastError());
				AfxMessageBox(wszMessage, MB_ICONERROR, 0);				
				return;
			}
			
			m_lvHeapEntries.DeleteItem(iRow);
			pos = m_lvHeapEntries.GetFirstSelectedItemPosition();
		}
	}

	EndWaitCursor();
}
