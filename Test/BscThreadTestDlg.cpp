// BscThreadTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "afxdialogex.h"
#include "BscThreadTestDlg.h"


// BscThreadTestDlg dialog

IMPLEMENT_DYNAMIC(BscThreadTestDlg, CDialogEx)

BscThreadTestDlg::BscThreadTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_BSC_THREAD, pParent)
{

}

BscThreadTestDlg::~BscThreadTestDlg()
{
}

void BscThreadTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_BSCTHREAD_COUNT, m_btnBscThreadCount);
	DDX_Control(pDX, IDC_EDIT_BSCTHREAD_COUNT, m_edtThreadCount);
	DDX_Control(pDX, IDC_EDIT_BSCTHREAD_LIMIT, m_edtThreadCountLimit);
}


BEGIN_MESSAGE_MAP(BscThreadTestDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_BSCTHREAD_COUNT, &BscThreadTestDlg::OnBnClickedButtonThreadCount)
END_MESSAGE_MAP()

void BscThreadTestDlg::OnBnClickedButtonThreadCount()
{
	size_t strlen = 0;
	CString szThreadCount = NULL;
	CString szCountLimit = NULL;
	int iThreadCount = 0;
	ULONGLONG ullCountLimit = 0;
	_TCHAR	szMessage[100];
	
	UpdateData(TRUE);

	m_edtThreadCount.GetWindowTextW(szThreadCount);
	iThreadCount = _wtoi(szThreadCount);
	
	m_edtThreadCountLimit.GetWindowTextW(szCountLimit);
	ullCountLimit = _wtoll(szCountLimit);

	thCurrent.SetThreadingInfo(iThreadCount, ullCountLimit);

	BeginWaitCursor();
	if (thCurrent.StartCounting())
	{	
		EndWaitCursor();
		_stprintf_s(szMessage, 100, _T("Counting until %lld is completed in %lld msec with with %d threads"), thCurrent.GetLimit(), thCurrent.GetExecutionDuration(), thCurrent.GetThreadCount());
		AfxMessageBox(szMessage, MB_ICONINFORMATION | MB_OK, 0);		
	}
	else
	{
		EndWaitCursor();
		_stprintf_s(szMessage, 100, _T("Counting job failed with error %d"), thCurrent.GetError());
		AfxMessageBox(szMessage, MB_ICONERROR | MB_OK, 0);
	}	
}