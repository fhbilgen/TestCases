// BscProcTest.cpp : implementation file
//

#include "stdafx.h"
#include"afxdlgs.h"
#include "Test.h"
#include "afxdialogex.h"
#include "BscProcTest.h"


// BscProcTest dialog

IMPLEMENT_DYNAMIC(BscProcTestDlg, CDialogEx)

BscProcTestDlg::BscProcTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_BSC_PROC, pParent)
{

}

BscProcTestDlg::~BscProcTestDlg()
{
}

void BscProcTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_PROC_APPNAME, m_edtAppPath);
	DDX_Control(pDX, IDC_EDIT_PROC_HANDLE, m_edtProcHandle);
	DDX_Control(pDX, IDC_EDIT_PROC_ID, m_edtProcID);
	DDX_Control(pDX, IDC_EDIT_PROC_THREAD_HANDLE, m_edtThreadHandle);
	DDX_Control(pDX, IDC_EDIT_PROC_THREADID, m_edtThreadID);
	DDX_Control(pDX, IDC_BUTTON_PROCCREATE, m_btnproc);
	DDX_Control(pDX, IDC_BUTTON_PROCKILL, m_btnProcKill);
	DDX_Control(pDX, IDC_BUTTON_PROCEXIT, m_btnProcExit);
}


BEGIN_MESSAGE_MAP(BscProcTestDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_PROC_APPNAME, &BscProcTestDlg::OnBnClickedButtonProcAppname)
	ON_BN_CLICKED(IDC_BUTTON_PROCCREATE, &BscProcTestDlg::OnClickedButtonProccreate)
	ON_BN_CLICKED(IDC_BUTTON_PROCKILL, &BscProcTestDlg::OnClickedButtonProckill)
	ON_BN_CLICKED(IDC_BUTTON_PROCEXIT, &BscProcTestDlg::OnClickedButtonProcexit)
END_MESSAGE_MAP()

void BscProcTestDlg::SetProcessInfo()
{
	_TCHAR szProcHandle[16];
	_TCHAR szProcID[16];
	_TCHAR szThreadHandle[16];
	_TCHAR szThreadID[16];

	_ultot_s(phCurrent.GetProcID(), szProcID, 10);
	_ultot_s(phCurrent.GetThreadID(), szThreadID, 10);

	// in 64 bit this might create a problem therefore LONGLONG is good
	_i64tot_s(  (LONGLONG)(phCurrent.GetProcHandle()), szProcHandle, _countof(szProcHandle), 10);
	_i64tot_s(  (LONGLONG)(phCurrent.GetThreadHandle()), szThreadHandle, _countof(szThreadID), 10);

	m_edtProcID.SetWindowTextW(szProcID);
	m_edtProcHandle.SetWindowTextW(szProcHandle);
	m_edtThreadHandle.SetWindowTextW(szThreadHandle);
	m_edtThreadID.SetWindowTextW(szThreadID);
}

void BscProcTestDlg::ClearProcessInfo()
{	
	m_edtProcID.SetWindowTextW(_T(""));
	m_edtProcHandle.SetWindowTextW(_T(""));
	m_edtThreadHandle.SetWindowTextW(_T(""));
	m_edtThreadID.SetWindowTextW(_T(""));
	UpdateData(TRUE);
}

// BscProcTest message handlers

void BscProcTestDlg::OnBnClickedButtonProcAppname()
{
	CString pathName;
	_TCHAR* path = NULL;
	CFileDialog dlgFile(TRUE);
	

	dlgFile.DoModal();
	pathName = dlgFile.GetPathName();

	int ln = pathName.GetLength()+1;
	path = (_TCHAR*)malloc(sizeof(_TCHAR) * ln );

	if ( path != NULL )
		_tcscpy_s(path, ln, (const _TCHAR*)pathName);


	if (path != nullptr && *path != '\0')
	{
		phCurrent.SetAppPath(path);
		m_edtAppPath.SetWindowTextW(phCurrent.GetAppPath());

		free(path);
	}

}


BOOL BscProcTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
		
	m_btnproc.EnableWindow(TRUE);
	m_btnProcExit.EnableWindow(FALSE);
	m_btnProcKill.EnableWindow(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	
}

void BscProcTestDlg::OnClickedButtonProccreate()
{

	_TCHAR szErrMsg[100] = _T("Process creation failed with error ");
	_TCHAR szErrNo[16] = _T("");

	if (!phCurrent.IsAppPathEmpty())
	{
		if (phCurrent.CreateNewProcess())
		{
			SetProcessInfo();
			m_btnproc.EnableWindow(FALSE);
			m_btnProcExit.EnableWindow(TRUE);
			m_btnProcKill.EnableWindow(TRUE);
		}
		else
		{
			_ultot_s(phCurrent.GetError(), szErrNo, 10);
			_tcscat_s(szErrMsg, szErrNo);
			AfxMessageBox(szErrMsg, MB_ICONERROR | MB_OK, 0);
		}
	}
	else
	{
		AfxMessageBox(_T("Please select an application"), MB_ICONERROR | MB_OK, 0);
	}
}


void BscProcTestDlg::OnClickedButtonProckill()
{
	_TCHAR szErrMsg[100] = _T("Process termination failed with error ");
	_TCHAR szErrNo[16] = _T("");

	if (!phCurrent.KillCurrentProcess())
	{
		_ultot_s(phCurrent.GetError(), szErrNo, 10);
		_tcscat_s(szErrMsg, szErrNo);
		AfxMessageBox(szErrMsg, MB_ICONERROR | MB_OK, 0);
	}

	ClearProcessInfo();
	m_btnproc.EnableWindow(TRUE);
	m_btnProcExit.EnableWindow(FALSE);
	m_btnProcKill.EnableWindow(FALSE);
}


void BscProcTestDlg::OnClickedButtonProcexit()
{
	phCurrent.WaitProcessExit();
	ClearProcessInfo();
	m_btnproc.EnableWindow(TRUE);
	m_btnProcExit.EnableWindow(FALSE);
	m_btnProcKill.EnableWindow(FALSE);
}



