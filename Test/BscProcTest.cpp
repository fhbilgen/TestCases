// BscProcTest.cpp : implementation file
//

#include "stdafx.h"
#include"afxdlgs.h"
#include "Test.h"
#include "afxdialogex.h"
#include "BscProcTest.h"


// BscProcTest dialog

IMPLEMENT_DYNAMIC(BscProcTest, CDialogEx)

BscProcTest::BscProcTest(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_BSC_PROC, pParent)
{

}

BscProcTest::~BscProcTest()
{
}

void BscProcTest::DoDataExchange(CDataExchange* pDX)
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


BEGIN_MESSAGE_MAP(BscProcTest, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_PROC_APPNAME, &BscProcTest::OnBnClickedButtonProcAppname)
	ON_BN_CLICKED(IDC_BUTTON_PROCCREATE, &BscProcTest::OnClickedButtonProccreate)
	ON_BN_CLICKED(IDC_BUTTON_PROCKILL, &BscProcTest::OnClickedButtonProckill)
	ON_BN_CLICKED(IDC_BUTTON_PROCEXIT, &BscProcTest::OnClickedButtonProcexit)
END_MESSAGE_MAP()

void BscProcTest::SetProcessInfo()
{
	_TCHAR wszProcHandle[16];
	_TCHAR wszProcID[16];
	_TCHAR wszThreadHandle[16];
	_TCHAR wszThreadID[16];

	_ultot_s(phCurrent.GetProcID(), wszProcID, 10);
	_ultot_s(phCurrent.GetThreadID(), wszThreadID, 10);

	// in 64 bit this might create a problem therefore LONGLONG is good
	_i64tot_s(  (LONGLONG)(phCurrent.GetProcHandle()), wszProcHandle, _countof(wszProcHandle), 10);
	_i64tot_s(  (LONGLONG)(phCurrent.GetThreadHandle()), wszThreadHandle, _countof(wszThreadID), 10);

	m_edtProcID.SetWindowTextW(wszProcID);
	m_edtProcHandle.SetWindowTextW(wszProcHandle);
	m_edtThreadHandle.SetWindowTextW(wszThreadHandle);
	m_edtThreadID.SetWindowTextW(wszThreadID);
}

void BscProcTest::ClearProcessInfo()
{	
	m_edtProcID.SetWindowTextW(_T(""));
	m_edtProcHandle.SetWindowTextW(_T(""));
	m_edtThreadHandle.SetWindowTextW(_T(""));
	m_edtThreadID.SetWindowTextW(_T(""));
	UpdateData(TRUE);
}

// BscProcTest message handlers

void BscProcTest::OnBnClickedButtonProcAppname()
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


BOOL BscProcTest::OnInitDialog()
{
	CDialogEx::OnInitDialog();
		
	m_btnproc.EnableWindow(TRUE);
	m_btnProcExit.EnableWindow(FALSE);
	m_btnProcKill.EnableWindow(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	
}

void BscProcTest::OnClickedButtonProccreate()
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


void BscProcTest::OnClickedButtonProckill()
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


void BscProcTest::OnClickedButtonProcexit()
{
	phCurrent.WaitProcessExit();
	ClearProcessInfo();
	m_btnproc.EnableWindow(TRUE);
	m_btnProcExit.EnableWindow(FALSE);
	m_btnProcKill.EnableWindow(FALSE);
}



