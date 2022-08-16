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
	, m_lCommitSize(0)
	, m_dlgParent(NULL)
{

}

VirtualAllocOpsCommit::~VirtualAllocOpsCommit()
{
	m_dlgParent = NULL;
}

void VirtualAllocOpsCommit::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_VA_OPS_COMMIT_SIZE, m_edtCommitSize);
	DDX_Text(pDX, IDC_EDIT_VA_OPS_COMMIT_SIZE, m_lCommitSize);
}


BEGIN_MESSAGE_MAP(VirtualAllocOpsCommit, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_VA_OPS_COMMIT_COMMIT, &VirtualAllocOpsCommit::OnBnClickedButtonVaOpsCommitCommit)
	ON_EN_CHANGE(IDC_EDIT_VA_OPS_COMMIT_SIZE, &VirtualAllocOpsCommit::OnEnChangeEditVaOpsCommitSize)
END_MESSAGE_MAP()


// VirtualAllocOpsCommit message handlers


void VirtualAllocOpsCommit::SetControls()
{
	m_lCommitSize = m_dlgParent->m_iCurrentReservedSize;
	UpdateData(FALSE);
}


void VirtualAllocOpsCommit::OnBnClickedButtonVaOpsCommitCommit()
{
	_TCHAR* pStartAddress = NULL;
	pStartAddress = (_TCHAR*)::VirtualAlloc(m_dlgParent->m_pCurrentStartAddress, m_lCommitSize, MEM_COMMIT, m_dlgParent->m_dwCurrentProtect);

	if (NULL != pStartAddress)
	{
		m_dlgParent->m_iCurrentReservedSize -= m_lCommitSize;
		m_dlgParent->m_iCurrentCommitSize += m_lCommitSize;
	}

	m_dlgParent->m_dwGLE = ::GetLastError();

	this->EndDialog(IDOK);
}


void VirtualAllocOpsCommit::SetParentDialog(VirtualAllocOpsDlg* dlgParent)
{
	m_dlgParent = dlgParent;
}


BOOL VirtualAllocOpsCommit::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	SetControls(); 
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void VirtualAllocOpsCommit::OnEnChangeEditVaOpsCommitSize()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData(TRUE);
}
