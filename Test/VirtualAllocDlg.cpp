// VirtualAllocDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "VirtualAllocDlg.h"
#include "afxdialogex.h"


// VirtualAllocDlg dialog

IMPLEMENT_DYNAMIC(VirtualAllocDlg, CDialogEx)

VirtualAllocDlg::VirtualAllocDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(VirtualAllocDlg::IDD, pParent)
	, m_iSize(0)
	, m_wszMemoryBlock(NULL)
	, m_iCommitSize(0)
{

}

VirtualAllocDlg::~VirtualAllocDlg()
{
}

void VirtualAllocDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_VA_SIZE, m_edtSize);
	DDX_Control(pDX, IDC_BUTTON_VA_FILL, m_btnFill);
	DDX_Control(pDX, IDC_BUTTON_VA_FREE, m_btnFree);
	DDX_Text(pDX, IDC_EDIT_VA_SIZE, m_iSize);
	DDX_Control(pDX, IDC_BUTTON_VA_RESERVE, m_btnReserve);
	DDX_Control(pDX, IDC_BUTTON_VA_COMMIT, m_btnCommit);
	DDX_Control(pDX, IDC_STATIC_VA_START_ADDRESS, m_statReserve);
	DDX_Control(pDX, IDC_STATIC_VA_COMMIT, m_statCommit);
	DDX_Control(pDX, IDC_STATIC_VA_FILL, m_statFill);
	DDX_Control(pDX, IDC_STATIC_VA_FREE, m_statFree);
	DDX_Control(pDX, IDC_PROGRESS_WS, m_progWS);
	DDX_Control(pDX, IDC_PROGRESS_VB, m_progVB);
	DDX_Control(pDX, IDC_PROGRESS_PB, m_progPB);
	DDX_Control(pDX, IDC_EDIT_VA_COMMIT_SIZE, m_edtCommitSize);
	DDX_Text(pDX, IDC_EDIT_VA_COMMIT_SIZE, m_iCommitSize);
}


BEGIN_MESSAGE_MAP(VirtualAllocDlg, CDialogEx)	
	ON_BN_CLICKED(IDC_BUTTON_VA_FREE, &VirtualAllocDlg::OnBnClickedButtonVaFree)
	ON_BN_CLICKED(IDC_BUTTON_VA_RESERVE, &VirtualAllocDlg::OnBnClickedButtonVaReserve)
	ON_EN_CHANGE(IDC_EDIT_VA_SIZE, &VirtualAllocDlg::OnEnChangeEditVaSize)
	ON_BN_CLICKED(IDC_BUTTON_VA_COMMIT, &VirtualAllocDlg::OnBnClickedButtonVaCommit)
	ON_BN_CLICKED(IDC_BUTTON_VA_FILL, &VirtualAllocDlg::OnBnClickedButtonVaFill)
	ON_EN_CHANGE(IDC_EDIT_VA_COMMIT_SIZE, &VirtualAllocDlg::OnEnChangeEditVaCommitSize)
	ON_BN_CLICKED(IDC_BUTTON_VA_FRAGMENT, &VirtualAllocDlg::OnBnClickedButtonVaFragment)
END_MESSAGE_MAP()


// VirtualAllocDlg message handlers


BOOL VirtualAllocDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	SetControls();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void VirtualAllocDlg::SetControls()
{

	m_edtSize.Clear();
	m_edtCommitSize.Clear();

	m_statReserve.SetWindowTextW(_T(""));
	m_statCommit.SetWindowTextW(_T(""));
	m_statFill.SetWindowTextW(_T(""));
	m_statFree.SetWindowTextW(_T(""));

	m_btnReserve.EnableWindow(TRUE);
	m_btnCommit.EnableWindow(FALSE);
	m_btnFill.EnableWindow(FALSE);
	m_btnFree.EnableWindow(FALSE);

	m_progWS.SetRange(0, 100);
	m_progPB.SetRange(0, 100);
	m_progVB.SetRange(0, 100);
	UpdateData(TRUE);
}

void VirtualAllocDlg::OnEnChangeEditVaSize()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData(TRUE);
}

void VirtualAllocDlg::OnBnClickedButtonVaReserve()
{
	SIZE_T	dwNumOfChars = 0;
	_TCHAR	wszErrorMessage[100];
	_TCHAR  wszDescription[100];

	dwNumOfChars = (SIZE_T)(m_iSize)*(1024 * 1024) / sizeof(_TCHAR);
	m_wszMemoryBlock = (_TCHAR*)VirtualAlloc(NULL, sizeof(_TCHAR)* dwNumOfChars, MEM_RESERVE, PAGE_READWRITE);

	if (m_wszMemoryBlock == NULL)
	{
		_stprintf_s(wszErrorMessage, 100, _T("The memory block is not reserved. Error = 0x%X"), GetLastError());
		AfxMessageBox(wszErrorMessage, MB_ICONERROR | MB_OK, 0);
		return;
	}

	_stprintf_s(wszDescription, 100,  _T("A memory block is reserved starting from address 0x%p"), m_wszMemoryBlock);
	m_statReserve.SetWindowTextW(wszDescription);
	m_statFree.SetWindowTextW(_T(""));

	m_edtSize.EnableWindow(FALSE);
	m_btnReserve.EnableWindow(FALSE);
	m_btnCommit.EnableWindow(TRUE);
	m_btnFill.EnableWindow(FALSE);
	m_btnFree.EnableWindow(FALSE);

	// progress
	m_progVB.SetPos(100);

}


void VirtualAllocDlg::OnBnClickedButtonVaCommit()
{
	SIZE_T	dwNumOfChars = 0;
	_TCHAR	wszErrorMessage[100];
	_TCHAR  wszDescription[100];
	int		iProgBarCommitPos = 0;
		
	dwNumOfChars = (SIZE_T)(m_iCommitSize)* (1024 * 1024) / sizeof(_TCHAR);
	m_wszMemoryBlock = (_TCHAR*)VirtualAlloc(m_wszMemoryBlock, sizeof(_TCHAR)* dwNumOfChars, MEM_COMMIT, PAGE_READWRITE);

	if (m_wszMemoryBlock == NULL)
	{
		_stprintf_s(wszErrorMessage, 100, _T("The memory block is not committed. Error = 0x%X"), GetLastError());
		AfxMessageBox(wszErrorMessage, MB_ICONERROR | MB_OK, 0);
		return;
	}

	_stprintf_s(wszDescription, 100, _T("%d MB of space is committed starting from address 0x%p"), m_iCommitSize, m_wszMemoryBlock);
	m_statCommit.SetWindowTextW(wszDescription);

	m_edtCommitSize.EnableWindow(FALSE);
	m_btnReserve.EnableWindow(FALSE);
	m_btnCommit.EnableWindow(FALSE);
	m_btnFill.EnableWindow(TRUE);
	m_btnFree.EnableWindow(FALSE);

	// progress
	iProgBarCommitPos = int((double)m_iCommitSize / (double)m_iSize * 100.0);
	m_progPB.SetPos(iProgBarCommitPos);
}


void VirtualAllocDlg::OnBnClickedButtonVaFill()
{
	size_t	dwNumOfChars = 0;	
	_TCHAR  wszDescription[100];
	int iProgBarCommitPos = 0;

	BeginWaitCursor();
	dwNumOfChars = (size_t)(m_iCommitSize) * (1024 * 1024) / sizeof(_TCHAR);
	
	wmemset(m_wszMemoryBlock, 'A', dwNumOfChars);

	_stprintf_s(wszDescription, 100, _T("The memory block is filled with A's"));
	m_statFill.SetWindowTextW(wszDescription);
	
	m_btnReserve.EnableWindow(FALSE);
	m_btnCommit.EnableWindow(FALSE);
	m_btnFill.EnableWindow(FALSE);
	m_btnFree.EnableWindow(TRUE);

	// progress
	iProgBarCommitPos = int((double)m_iCommitSize / (double)m_iSize * 100.0);
	m_progWS.SetPos(iProgBarCommitPos);
	EndWaitCursor();
}

void VirtualAllocDlg::OnBnClickedButtonVaFree()
{
	_TCHAR	wszErrorMessage[100];
	_TCHAR  wszDescription[100];

	if (!VirtualFree((void*)m_wszMemoryBlock, 0, MEM_RELEASE))
	{
		_stprintf_s(wszErrorMessage, 100, _T("The memory block is not freed. Error = 0x%X"), GetLastError());
		AfxMessageBox(wszErrorMessage, MB_ICONERROR | MB_OK, 0);
		return;
	}

	_stprintf_s(wszDescription, 100, _T("The memory block is released"));
	m_statFree.SetWindowTextW(wszDescription);

	m_edtSize.SetWindowTextW(_T("0"));
	m_edtSize.EnableWindow(TRUE);
	m_edtCommitSize.SetWindowTextW(_T("0"));
	m_edtCommitSize.EnableWindow(TRUE);
	m_btnReserve.EnableWindow(TRUE);
	m_btnCommit.EnableWindow(FALSE);
	m_btnFill.EnableWindow(FALSE);
	m_btnFree.EnableWindow(FALSE);

	m_statReserve.SetWindowTextW(_T(""));
	m_statCommit.SetWindowTextW(_T(""));
	m_statFill.SetWindowTextW(_T(""));

	// progress

	m_progWS.SetPos(0);
	m_progPB.SetPos(0);
	m_progVB.SetPos(0);

}

void VirtualAllocDlg::OnEnChangeEditVaCommitSize()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData(TRUE);
}


void VirtualAllocDlg::OnBnClickedButtonVaFragment()
{
	
}
