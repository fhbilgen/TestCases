// InterProcWaitDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "InterProcWaitDlg.h"
#include "afxdialogex.h"

extern GetResourceProc		g_fnGetResource;
extern ReleaseResourceProc	g_fnReleaseResource;

// InterProcWaitDlg dialog

IMPLEMENT_DYNAMIC(InterProcWaitDlg, CDialogEx)

InterProcWaitDlg::InterProcWaitDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(InterProcWaitDlg::IDD, pParent)
	, m_strResourceWait(_T(""))
	, m_strResourceAcquired(_T(""))
	, m_strResourceReleased(_T(""))
{

}

InterProcWaitDlg::~InterProcWaitDlg()
{
	imgRedLight.Destroy();
	imgGreenLight.Destroy();
}

void InterProcWaitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_IP_GET_RESOURCE, m_btnGetResource);
	DDX_Control(pDX, IDC_BUTTON_IP_RELEASE_RESOURCE, m_btnReleaseResource);
	DDX_Control(pDX, IDC_STATIC_IP_TRAFFIC_LIGHT, m_picTrafficLight);
	DDX_Control(pDX, IDC_STATIC_IP_STATUS, m_statStatus);
}


BEGIN_MESSAGE_MAP(InterProcWaitDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_IP_GET_RESOURCE, &InterProcWaitDlg::OnBnClickedButtonIpGetResource)
	ON_BN_CLICKED(IDC_BUTTON_IP_RELEASE_RESOURCE, &InterProcWaitDlg::OnBnClickedButtonIpReleaseResource)
END_MESSAGE_MAP()


// InterProcWaitDlg message handlers


BOOL InterProcWaitDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitializeCaseFunctions();
	SetControls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void InterProcWaitDlg::OnBnClickedButtonIpGetResource()
{
	_TCHAR	szErrorMessage[100];

	m_picTrafficLight.SetBitmap(HBITMAP(imgRedLight));	
	m_statStatus.SetWindowTextW( m_strResourceWait );
	BeginWaitCursor();
	if (!(g_fnGetResource)())
	{
		_stprintf_s(szErrorMessage, 100, _T("Getting the resource failed. Error = 0x%x"), GetLastError());
		AfxMessageBox(szErrorMessage, MB_ICONERROR | MB_OK, 0);
		return;
	}
	
	EndWaitCursor();
	m_statStatus.SetWindowTextW(m_strResourceAcquired);
	m_picTrafficLight.SetBitmap(HBITMAP(imgGreenLight));
		
	m_btnGetResource.EnableWindow(FALSE);
	m_btnReleaseResource.EnableWindow(TRUE);
}


void InterProcWaitDlg::OnBnClickedButtonIpReleaseResource()
{
	_TCHAR	szErrorMessage[100];

	if (!(g_fnReleaseResource)())
	{
		_stprintf_s(szErrorMessage, 100, _T("releasing the resource failed. Error = 0x%x"), GetLastError());
		AfxMessageBox(szErrorMessage, MB_ICONERROR | MB_OK, 0);
		return;
	}

	m_picTrafficLight.SetBitmap(NULL);	
	m_statStatus.SetWindowTextW(m_strResourceReleased);
	
	m_btnGetResource.EnableWindow(TRUE);
	m_btnReleaseResource.EnableWindow(FALSE);
}


void InterProcWaitDlg::SetControls()
{
	
	HRESULT hResult = imgRedLight.Load(_T("RedSmall.jpg"));
	HRESULT hResult2 = imgGreenLight.Load(_T("GreenSmall.jpg"));
	

	m_strResourceWait.LoadStringW(IDS_IP_RESOURCE_WAIT);
	m_strResourceAcquired.LoadStringW(IDS_IP_RESOURCE_ACQUIRED);
	m_strResourceReleased.LoadStringW(IDS_IP_RESOURCE_RELEASED);

	m_picTrafficLight.SetBitmap(NULL);
	m_btnGetResource.EnableWindow(TRUE);
	m_btnReleaseResource.EnableWindow(FALSE);
}
