// BscLibTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "afxdialogex.h"
#include "BscLibTestDlg.h"



// BscLibTestDlg dialog

IMPLEMENT_DYNAMIC(BscLibTestDlg, CDialogEx)

BscLibTestDlg::BscLibTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_BSC_LIB, pParent), m_nOperation(0)
{

}

BscLibTestDlg::~BscLibTestDlg()
{
}

void BscLibTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_BSCLIBPLUS, m_nOperation);	
	DDX_Control(pDX, IDC_EDIT_BSCLIBSTATUS, m_edtLibStat);
	DDX_Control(pDX, IDC_BUTTON_BSCLIB_LOAD, m_btnLibLoad);
	DDX_Control(pDX, IDC_BUTTON_BSCLIB_UNLOAD, m_btnLibUnload);
	DDX_Control(pDX, IDC_STATIC_BSCLIBOPS, m_gbOperations);
	DDX_Control(pDX, IDC_BUTTON_BSCLIB_CALCULATE, m_btnLibCalc);
	DDX_Control(pDX, IDC_EDIT_BSCLIB_PARAM1, m_edtParam1);
	DDX_Control(pDX, IDC_EDITBSCLIB_PARAM2, m_edtParam2);
	DDX_Control(pDX, IDC_EDIT_BSCLIB_RESULT, m_edtResult);
}


BEGIN_MESSAGE_MAP(BscLibTestDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_BSCLIB_LOAD, &BscLibTestDlg::OnClickedButtonBsclibLoad)
	ON_BN_CLICKED(IDC_BUTTON_BSCLIB_UNLOAD, &BscLibTestDlg::OnClickedButtonBsclibUnload)
	ON_BN_CLICKED(IDC_BUTTON_BSCLIB_CALCULATE, &BscLibTestDlg::OnClickedButtonBsclibCalculate)
END_MESSAGE_MAP()


// BscLibTestDlg message handlers
BOOL BscLibTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_btnLibLoad.EnableWindow(TRUE);
	m_btnLibUnload.EnableWindow(FALSE);	
	m_edtLibStat.SetWindowTextW(_T(""));
	UpdateData(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void BscLibTestDlg::OnClickedButtonBsclibLoad()
{
	_TCHAR szMessage[100];

	if (m_lhCurrent.LoadLib())
	{
		m_btnLibLoad.EnableWindow(FALSE);
		m_btnLibUnload.EnableWindow(TRUE);
		m_btnLibCalc.EnableWindow(TRUE);
		m_edtLibStat.SetWindowTextW(m_lhCurrent.GetLoadStateMessage());
	}
	else
	{
		_stprintf_s(szMessage, 100, _T("Cases.dll library load failed with error %d"), m_lhCurrent.GetError());
		AfxMessageBox(szMessage, MB_ICONERROR | MB_OK, 0);		
	}

	if (!m_lhCurrent.LoadFnAddr())
	{
		_stprintf_s(szMessage, 100, _T("Function addresses in Cases.dll could not be fetched. Error %d"), m_lhCurrent.GetError());
		AfxMessageBox(szMessage, MB_ICONERROR | MB_OK, 0);
	}
}


void BscLibTestDlg::OnClickedButtonBsclibUnload()
{
	_TCHAR szMessage[100];

	if (m_lhCurrent.UnloadLib())
	{
		m_lhCurrent.ZeroFnAddr();
		m_btnLibLoad.EnableWindow(TRUE);
		m_btnLibUnload.EnableWindow(FALSE);		
		m_btnLibCalc.EnableWindow(FALSE);
		m_edtLibStat.SetWindowTextW(m_lhCurrent.GetLoadStateMessage());
		m_edtResult.SetWindowTextW(_T(""));
		m_edtParam1.SetWindowTextW(_T(""));
		m_edtParam2.SetWindowTextW(_T(""));
	}
	else
	{
		_stprintf_s(szMessage, 100, _T("Cases.dll library unload failed with error %d"), m_lhCurrent.GetError());
		AfxMessageBox(szMessage, MB_ICONERROR | MB_OK, 0);
	}
}


void BscLibTestDlg::OnClickedButtonBsclibCalculate()
{
	CString csParam1, csParam2;
	_TCHAR szResult[20] = _T("");
	int result = 0;

	UpdateData(TRUE);
	m_edtParam1.GetWindowTextW(csParam1);
	m_edtParam2.GetWindowTextW(csParam2);
		
	result = m_lhCurrent.Calculate(_wtoi(csParam1), _wtoi(csParam2), m_nOperation);

	_stprintf_s(szResult, 20, _T("%d"), result);
	m_edtResult.SetWindowTextW(szResult);

	UpdateData(FALSE);
}
