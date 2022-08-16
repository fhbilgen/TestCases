// ExpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "ExpDlg.h"
#include "afxdialogex.h"


extern AccessViolateProc			g_fnAccessViolate;
extern AccessViolateAndHandleProc	g_fnAccessViolateAndHandle;
extern DivisionByZeroProc			g_fnDivisionByZero;

// ExpDlg dialog

IMPLEMENT_DYNAMIC(ExpDlg, CDialogEx)

ExpDlg::ExpDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ExpDlg::IDD, pParent)
{

}

ExpDlg::~ExpDlg()
{
}

void ExpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ExpDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_EXP_AV, &ExpDlg::OnBnClickedButtonExpAv)
	ON_BN_CLICKED(IDC_BUTTON_AV_WITH_HANDLER, &ExpDlg::OnBnClickedButtonAvWithHandler)
	ON_BN_CLICKED(IDC_BUTTON_EXP_DIV_BY_ZERO, &ExpDlg::OnBnClickedButtonExpDivByZero)
END_MESSAGE_MAP()


// ExpDlg message handlers


void ExpDlg::OnBnClickedButtonExpAv()
{
	(g_fnAccessViolate)();
}


void ExpDlg::OnBnClickedButtonAvWithHandler()
{
	(g_fnAccessViolateAndHandle)();
}


void ExpDlg::OnBnClickedButtonExpDivByZero()
{
	(g_fnDivisionByZero)();
}
