// CritSecDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "CritSecDlg.h"
#include "afxdialogex.h"


extern CreateDeadlockProc	g_fnCreateDeadlock;
extern WaitOnOrphantCSProc	g_fnWaitOnOrphantCS;

// CritSecDlg dialog

IMPLEMENT_DYNAMIC(CritSecDlg, CDialogEx)

CritSecDlg::CritSecDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CritSecDlg::IDD, pParent)
{

}

CritSecDlg::~CritSecDlg()
{
}

void CritSecDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CritSecDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CS_DEADLOCK, &CritSecDlg::OnBnClickedButtonCsDeadlock)
	ON_BN_CLICKED(IDC_BUTTON_CS_ORPHANT, &CritSecDlg::OnBnClickedButtonCsOrphant)
END_MESSAGE_MAP()


// CritSecDlg message handlers


void CritSecDlg::OnBnClickedButtonCsDeadlock()
{
	(g_fnCreateDeadlock)();
}


void CritSecDlg::OnBnClickedButtonCsOrphant()
{
	(g_fnWaitOnOrphantCS)();
}


BOOL CritSecDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitializeCaseFunctions();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
