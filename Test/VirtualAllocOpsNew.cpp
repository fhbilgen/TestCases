// VirtualAllocOpsNew.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "VirtualAllocOpsNew.h"
#include "afxdialogex.h"


// VirtualAllocOpsNew dialog

IMPLEMENT_DYNAMIC(VirtualAllocOpsNew, CDialogEx)

VirtualAllocOpsNew::VirtualAllocOpsNew(CWnd* pParent /*=NULL*/)
	: CDialogEx(VirtualAllocOpsNew::IDD, pParent)
	, m_lSize(0)
	, m_fReserve(false)
	, m_fCommit(false)
{

}

VirtualAllocOpsNew::~VirtualAllocOpsNew()
{
	m_dlgParent = NULL;
}

void VirtualAllocOpsNew::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_VA_OPS_NEW_SIZE, m_vaNewSize);
	DDX_Control(pDX, IDC_CHECK_VA_OPS_NEW_RESERVED, m_chkvaNewReserve);
	DDX_Control(pDX, IDC_CHECK_VA_OPS_NEW_COMMIT, m_chkvaNewCommit);
	DDX_Control(pDX, IDC_COMBO_VA_OPS_NEW_PROTECT, m_cmbvaNewProtection);
	DDX_Control(pDX, IDC_BUTTON_VA_OPS_NEW_ALLOCATE, m_btnvaNewAllocate);
	DDX_Text(pDX, IDC_EDIT_VA_OPS_NEW_SIZE, m_lSize);
}


BEGIN_MESSAGE_MAP(VirtualAllocOpsNew, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_VA_OPS_NEW_ALLOCATE, &VirtualAllocOpsNew::OnBnClickedButtonVaOpsNewAllocate)
	ON_EN_CHANGE(IDC_EDIT_VA_OPS_NEW_SIZE, &VirtualAllocOpsNew::OnEnChangeEditVaOpsNewSize)	
END_MESSAGE_MAP()


// VirtualAllocOpsNew message handlers


void VirtualAllocOpsNew::SetControls()
{
	m_vaNewSize.Clear();
	m_chkvaNewReserve.SetState(FALSE);
	m_chkvaNewCommit.SetState(FALSE);
	m_cmbvaNewProtection.AddString(_T("EXECUTE"));					//	0
	m_cmbvaNewProtection.AddString(_T("EXECUTE READ"));				//  1
	m_cmbvaNewProtection.AddString(_T("EXECUTE READ/WRITE"));		//	2
	m_cmbvaNewProtection.AddString(_T("NO ACCESS"));				//	3
	m_cmbvaNewProtection.AddString(_T("READ ONLY"));				//	4
	m_cmbvaNewProtection.AddString(_T("READ/WRITE"));				//	5
	
	m_cmbvaNewProtection.SetCurSel(0);
	
}

BOOL VirtualAllocOpsNew::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	SetControls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void VirtualAllocOpsNew::OnBnClickedButtonVaOpsNewAllocate()
{
	UpdateData(FALSE);
	DWORD	dwAllocationType = 0;
	DWORD	dwAllocationProtection = 0;
	_TCHAR	*pStartAddress = NULL;
	BYTE* bp = NULL;
	
	
	if (BST_CHECKED == m_chkvaNewReserve.GetCheck())
		dwAllocationType = MEM_RESERVE;
	
	if (BST_CHECKED == m_chkvaNewCommit.GetCheck())
		dwAllocationType |= MEM_COMMIT;
	

	// set the protection type
	switch (m_cmbvaNewProtection.GetCurSel())
	{
	case 0:
		dwAllocationProtection = PAGE_EXECUTE;
		break;
	case 1:
		dwAllocationProtection = PAGE_EXECUTE_READ;
		break;
	case 2:
		dwAllocationProtection = PAGE_EXECUTE_READWRITE;
		break;
	case 3:
		dwAllocationProtection = PAGE_NOACCESS;
		break;
	case 4:
		dwAllocationProtection = PAGE_READONLY;
		break;
	case 5:
		dwAllocationProtection = PAGE_READWRITE;
		break;
	

	default:
		break;
	}

	
	m_dlgParent->m_VAEntry.lTotalSize = m_lSize;
	m_dlgParent->m_VAEntry.dwProtection = dwAllocationProtection;
	m_dlgParent->m_VAEntry.dwAllocType = dwAllocationType;
	size_t st = m_lSize / sizeof(_TCHAR);
	m_dlgParent->m_VAEntry.pAddress = (_TCHAR*)VirtualAlloc(NULL, sizeof(_TCHAR)* st * 1024 * 1024, dwAllocationType, dwAllocationProtection);
	/*pStartAddress = (_TCHAR*)VirtualAlloc(NULL, sizeof(_TCHAR)* 1000 * 1024 * 1024, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	bp = (BYTE*)VirtualAlloc(NULL, sizeof(BYTE) * 4000 * 1024 * 1024, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);	*/
	m_dlgParent->m_VAEntry.dwGLE = ::GetLastError();

	
	this->EndDialog(IDOK);
}


void VirtualAllocOpsNew::SetParentDialog(VirtualAllocOpsDlg* dlgParent)
{
	m_dlgParent = dlgParent;
}


void VirtualAllocOpsNew::OnEnChangeEditVaOpsNewSize()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData(TRUE);
}

