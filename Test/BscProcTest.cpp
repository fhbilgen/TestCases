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
	wchar_t wszProcHandle[16];
	wchar_t wszProcID[16];
	wchar_t wszThreadHandle[16];
	wchar_t wszThreadID[16];

	_ultow_s(phCurrent.GetProcID(), wszProcID, 10);
	_ultow_s(phCurrent.GetThreadID(), wszThreadID, 10);

	_itow_s((int)(phCurrent.GetProcHandle()), wszProcHandle, 10);
	_itow_s((int)(phCurrent.GetThreadHandle()), wszThreadHandle, 10);

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
	wchar_t* path = NULL;	
	CFileDialog dlgFile(TRUE);
	

	dlgFile.DoModal();
	pathName = dlgFile.GetPathName();

	
	path = (wchar_t*)malloc(sizeof(wchar_t) * (pathName.GetLength() + 2));
	if ( path != NULL )
		wcscpy(path,(const wchar_t*)pathName);


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

	wchar_t wszErrMsg[100] = _T("Process creation failed with error ");
	wchar_t wszErrNo[16] = _T("");

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
			_ultow_s(phCurrent.dwLastError, wszErrNo, 10);
			wcscat_s(wszErrMsg, wszErrNo);
			AfxMessageBox(wszErrMsg, MB_ICONERROR | MB_OK, 0);
		}
	}
	else
	{
		AfxMessageBox(_T("Please select an application"), MB_ICONERROR | MB_OK, 0);
	}
}


void BscProcTest::OnClickedButtonProckill()
{
	wchar_t wszErrMsg[100] = _T("Process termination failed with error ");
	wchar_t wszErrNo[16] = _T("");

	if (phCurrent.KillCurrentProcess())
	{
		ClearProcessInfo();
		m_btnproc.EnableWindow(TRUE);
		m_btnProcExit.EnableWindow(FALSE);
		m_btnProcKill.EnableWindow(FALSE);
	}
	else
	{
		_ultow_s(phCurrent.dwLastError, wszErrNo, 10);
		wcscat_s(wszErrMsg, wszErrNo);
		AfxMessageBox(wszErrMsg, MB_ICONERROR | MB_OK, 0);
	}

}


void BscProcTest::OnClickedButtonProcexit()
{
	phCurrent.WaitProcessExit();
	ClearProcessInfo();
	m_btnproc.EnableWindow(TRUE);
	m_btnProcExit.EnableWindow(FALSE);
	m_btnProcKill.EnableWindow(FALSE);
}



