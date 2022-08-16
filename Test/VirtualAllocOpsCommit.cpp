// VirtualAllocOpsCommit.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "VirtualAllocOpsCommit.h"
#include "afxdialogex.h"


// VirtualAllocOpsCommit dialog

IMPLEMENT_DYNAMIC(VirtualAllocOpsCommit, CDialogEx)

VirtualAllocOpsCommit::VirtualAllocOpsCommit(CWnd* pParent /*=NULL*/)
	: CDialogEx(VirtualAllocOpsCommit::IDD, pParent)
	, m_CommitSize(0)
{
	m_lCommitSize = 0;
	m_pStartAddress = NULL;
	m_dwProtection = 0;
}

VirtualAllocOpsCommit::~VirtualAllocOpsCommit()
{
	m_dlgParent = NULL;
}

void VirtualAllocOpsCommit::SetParentDialog(VirtualAllocOpsDlg* dlgParent)
{
	m_dlgParent = dlgParent;
}

void VirtualAllocOpsCommit::SetCommitParams(_TCHAR* pStartAdress, int iCommitSize, DWORD	dwProtection)
{
	m_pStartAddress = pStartAdress;
	m_lCommitSize = iCommitSize;
	m_dwProtection = dwProtection;
}

void VirtualAllocOpsCommit::SetControls()
{
	m_CommitSize = m_lCommitSize;
	UpdateData(FALSE);
}

void VirtualAllocOpsCommit::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_VA_OPS_COMMIT_SIZE, m_edtCommitSize);
	DDX_Control(pDX, IDC_BUTTON_VA_OPS_COMMIT_ALLOCATE, m_btnCommit);
	DDX_Text(pDX, IDC_EDIT_VA_OPS_COMMIT_SIZE, m_CommitSize);
}


BEGIN_MESSAGE_MAP(VirtualAllocOpsCommit, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_VA_OPS_COMMIT_SIZE, &VirtualAllocOpsCommit::OnEnChangeEditVaOpsCommitSize)
	ON_BN_CLICKED(IDC_BUTTON_VA_OPS_COMMIT_ALLOCATE, &VirtualAllocOpsCommit::OnBnClickedButtonVaOpsCommitAllocate)
END_MESSAGE_MAP()


// VirtualAllocOpsCommit message handlers


void VirtualAllocOpsCommit::OnEnChangeEditVaOpsCommitSize()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData(TRUE);
}


BOOL VirtualAllocOpsCommit::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	SetControls();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void VirtualAllocOpsCommit::OnBnClickedButtonVaOpsCommitAllocate()
{
	_TCHAR* pStartAddress = NULL;
		
	pStartAddress = (_TCHAR*)::VirtualAlloc(m_pStartAddress, m_CommitSize * 1024 * 1024, MEM_COMMIT, m_dwProtection);

	if (NULL != pStartAddress)
	{
		m_dlgParent->m_VAEntry.lCommitSize += m_CommitSize;
		m_dlgParent->m_VAEntry.lReservedSize -= m_CommitSize;
	}
	else
		m_dlgParent->m_VAEntry.pAddress = NULL;

	m_dlgParent->m_VAEntry.dwGLE = ::GetLastError();

	this->EndDialog(IDOK);
}
