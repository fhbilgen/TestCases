// HandleCreateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "HandleCreateDlg.h"
#include "afxdialogex.h"


// HandleCreateDlg dialog

IMPLEMENT_DYNAMIC(HandleCreateDlg, CDialogEx)

HandleCreateDlg::HandleCreateDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(HandleCreateDlg::IDD, pParent)
{

}

HandleCreateDlg::~HandleCreateDlg()
{
}

void HandleCreateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(HandleCreateDlg, CDialogEx)
END_MESSAGE_MAP()


// HandleCreateDlg message handlers
