// BscHandleTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "afxdialogex.h"
#include "BscHandleTestDlg.h"


// BscHandleTestDlg dialog

IMPLEMENT_DYNAMIC(BscHandleTestDlg, CDialogEx)

BscHandleTestDlg::BscHandleTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_BSC_HANDLE, pParent), m_nFileMode(0), m_nMutexMode(0)
{

}

BscHandleTestDlg::~BscHandleTestDlg()
{
}

void BscHandleTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_BSCHNDL_FLNEW, m_nFileMode);
	DDX_Radio(pDX, IDC_RADIO_BSCHNDL_MTXNEW, m_nMutexMode);
	DDX_Control(pDX, IDC_BUTTON_BSCHNDL_FILE, m_btnOpenFile);
	DDX_Control(pDX, IDC_BUTTON_BSCHNDL_FILE_CLOSE, m_btnCloseFile);
	DDX_Control(pDX, IDC_BUTTON_BSCHNDL_MUTEX, m_btnOpenMutex);
	DDX_Control(pDX, IDC_BUTTON_BSCHNDL_MUTEX_CLOSE, m_btnCloseMutex);
	DDX_Control(pDX, IDC_EDIT_BSCHNDL_FILE, m_edtFilePath);
	DDX_Control(pDX, IDC_EDIT_BSCHNDL_FILENO, m_edtFileHandle);
	DDX_Control(pDX, IDC_EDIT_BSCHNDL_MUTEX, m_edtMutexName);
	DDX_Control(pDX, IDC_EDIT_BSCHNDL_MUTEXNO, m_edtMutexHandle);
}


BEGIN_MESSAGE_MAP(BscHandleTestDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_BSCHNDL_FILE, &BscHandleTestDlg::OnBnClickedButtonBschndlFile)
	ON_BN_CLICKED(IDC_BUTTON_BSCHNDL_FILE_CLOSE, &BscHandleTestDlg::OnBnClickedButtonBschndlFileClose)
	ON_BN_CLICKED(IDC_BUTTON_BSCHNDL_MUTEX, &BscHandleTestDlg::OnBnClickedButtonBschndlMutex)
	ON_BN_CLICKED(IDC_BUTTON_BSCHNDL_MUTEX_CLOSE, &BscHandleTestDlg::OnBnClickedButtonBschndlMutexClose)
END_MESSAGE_MAP()


// BscHandleTestDlg message handlers


BOOL BscHandleTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_btnCloseFile.EnableWindow(FALSE);
	m_btnCloseMutex.EnableWindow(FALSE);
	UpdateData(TRUE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void BscHandleTestDlg::OnBnClickedButtonBschndlFile()
{
	UpdateData(TRUE);
	BOOL fResult = TRUE;
	_TCHAR szMessage[100];
	_TCHAR szHandle[10];

	switch (m_nFileMode)
	{
	case 0:
		fResult = m_fhCurrent.InitiateFile(TRUE);
		break;
	case 1:
		fResult = m_fhCurrent.InitiateFile(FALSE);
		break;
	default:
		break;
	}

	// If there was a problem while initiating the file then display an error message and leave the controls as is
	if (!fResult)
	{
		_stprintf_s(szMessage, 100, _T("File creation failed with error %d"), m_fhCurrent.GetError());
		AfxMessageBox(szMessage, MB_ICONERROR | MB_OK, 0);
		return;
	}

	m_edtFilePath.SetWindowTextW(m_fhCurrent.GetFilePath());
	
	_i64tot_s((LONGLONG)m_fhCurrent.GetFileHandle(), szHandle, _countof(szHandle), 10);
	
	m_edtFileHandle.SetWindowTextW(szHandle);

	m_btnCloseFile.EnableWindow(TRUE);
	m_btnOpenFile.EnableWindow(FALSE);
	UpdateData(FALSE);
}


void BscHandleTestDlg::OnBnClickedButtonBschndlFileClose()
{	
	m_fhCurrent.CloseFile();

	m_edtFilePath.SetWindowTextW(_T(""));
	m_edtFileHandle.SetWindowTextW(_T(""));

	m_btnCloseFile.EnableWindow(FALSE);
	m_btnOpenFile.EnableWindow(TRUE);
	UpdateData(FALSE);
}


void BscHandleTestDlg::OnBnClickedButtonBschndlMutex()
{
	UpdateData(TRUE);
	BOOL fResult = TRUE;
	_TCHAR szMessage[100];
	_TCHAR szHandle[10];

	switch (m_nMutexMode)
	{
	case 0:
		fResult = m_mhCurrent.InitiateMutex(TRUE);
		break;
	case 1:
		fResult = m_mhCurrent.InitiateMutex(FALSE);
		break;
	default:
		break;
	}

	// If there was a problem while initiating the file then display an error message and leave the controls as is
	if (!fResult)
	{
		_stprintf_s(szMessage, 100, _T("Mutex creation failed with error %d"), m_mhCurrent.GetError());
		AfxMessageBox(szMessage, MB_ICONERROR | MB_OK, 0);
		return;
	}
	
	m_edtMutexName.SetWindowTextW(m_mhCurrent.GetMutexName());
	_i64tot_s((LONGLONG)m_mhCurrent.GetMutexHandle(), szHandle, 10, 10);
	m_edtMutexHandle.SetWindowTextW(szHandle);
	

	m_btnOpenMutex.EnableWindow(FALSE);
	m_btnCloseMutex.EnableWindow(TRUE);
	UpdateData(FALSE);
}


void BscHandleTestDlg::OnBnClickedButtonBschndlMutexClose()
{
	m_mhCurrent.CloseMutex();

	m_edtMutexHandle.SetWindowTextW(_T(""));
	m_edtMutexName.SetWindowTextW(_T(""));
	
	m_btnOpenMutex.EnableWindow(TRUE);
	m_btnCloseMutex.EnableWindow(FALSE);
	UpdateData(FALSE);
}
