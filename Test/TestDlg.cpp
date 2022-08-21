
// TestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "TestDlg.h"
#include "afxdialogex.h"
#include "CritSecDlg.h"
#include "InterProcWaitDlg.h"
#include "HiCPUDlg.h"
#include "HiCPUHiIODlg.h"
#include "ExpDlg.h"
#include "VirtualAllocDlg.h"
#include "VirtualAllocOpsDlg.h"
#include "FGIOCreateAndWriteDlg.h"
#include "HeapOperations.h"
#include "VirtualAllocIncrease.h"
#include "BscProcTest.h"
#include "BscThreadTestDlg.h"
#include "BscHandleTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/*
1 32-bit
2 32-bit LARGEADDRESSAWARE
3 64-bit
*/
#define BITNESS 2

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTestDlg dialog



CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_HANG_CRITICALSECTION, &CTestDlg::OnHangCriticalsection)
	ON_COMMAND(ID_HANG_WAITANOTHERPROCESS, &CTestDlg::OnHangWaitanotherprocess)
	ON_COMMAND(ID_CPU_HIGHUTILIZATION, &CTestDlg::OnCpuHighutilization)
	ON_COMMAND(ID_EXCEPTIONS_AV_DIVBYZERO, &CTestDlg::OnExceptionsAvDivbyzero)
	ON_COMMAND(ID_MEMORY_VIRTUALALLOC, &CTestDlg::OnMemoryVirtualalloc)
	ON_COMMAND(ID_MEMORY_VIRTUALALLOCATIONOPERATIONS, &CTestDlg::OnMemoryVirtualallocationoperations)
	ON_COMMAND(ID_IO_FILECREATE, &CTestDlg::OnIoFilecreate)
	ON_COMMAND(ID_MEMORY_HEAPOPERATIONS, &CTestDlg::OnMemoryHeapoperations)
	ON_COMMAND(ID_MEMORY_VIRTUALMEMINCREASEOVERTIME, &CTestDlg::OnMemoryVirtualmemincreaseovertime)
	ON_COMMAND(ID_CPU_HIGHUTILIZATIONHIGHFILEI, &CTestDlg::OnCpuHighutilizationhighfilei)
	ON_COMMAND(ID_BASICS_PROCESS, &CTestDlg::OnBasicsProcess)
	ON_COMMAND(ID_BASICS_THREAD, &CTestDlg::OnBasicsThread)
	ON_COMMAND(ID_BASICS_HANDLE, &CTestDlg::OnBasicsHandle)
END_MESSAGE_MAP()


// CTestDlg message handlers

BOOL CTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon


	//if ( BITNESS == 1 )
	//{
	//	SetWindowText(_T("Test - 32 bit"));
	//}
	//else
	//{
	//	if ( BITNESS == 2 )
	//	{
	//		SetWindowText(_T("Test - 32 bit LARGEADDRESSAWARE"));
	//	}
	//	else
	//	{
	//		// BITNESS == 3
	//		SetWindowText(_T("Test - 64 bit"));
	//	}
	//}

#if defined(_M_X64) || defined(__amd64__) || defined(_M_ARM64) || defined(_M_ARM64EC)
// Building for 64bit target ARM, AMD or INTEL
	SetWindowText(_T("Test - 64 bit"));
#elif defined(_M_IX86)
	SetWindowText(_T("Test - 32 bit"));
#endif


	// TODO: Add extra initialization here
	if (!InitializeCaseFunctions())
		AfxMessageBox(_T("Cases library is not loaded"), MB_OK, 0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTestDlg::OnHangCriticalsection()
{
	CritSecDlg critsecDialog;

	critsecDialog.DoModal();
}


void CTestDlg::OnHangWaitanotherprocess()
{
	InterProcWaitDlg interprocwaitDlg;

	interprocwaitDlg.DoModal();
}


void CTestDlg::OnCpuHighutilization()
{
	HiCPUDlg hicpuDlg;
	hicpuDlg.DoModal();
}


void CTestDlg::OnExceptionsAvDivbyzero()
{
	ExpDlg	exceptionsDlg;

	exceptionsDlg.DoModal();
}


void CTestDlg::OnMemoryVirtualalloc()
{
	VirtualAllocDlg virtualAllocDlg;

	virtualAllocDlg.DoModal();
}


void CTestDlg::OnMemoryVirtualallocationoperations()
{
	VirtualAllocOpsDlg vaOpsDlg;
	vaOpsDlg.DoModal();
}

void CTestDlg::OnMemoryVirtualmemincreaseovertime()
{
	VirtualAllocIncrease vaIncDlg;
	vaIncDlg.DoModal();
}

void CTestDlg::OnIoFilecreate()
{
	FGIOCreateAndWriteDlg fgio;
	fgio.DoModal();
}


void CTestDlg::OnMemoryHeapoperations()
{
	HeapOperations heapOperationsDlg;
	heapOperationsDlg.DoModal();
}


void CTestDlg::OnCpuHighutilizationhighfilei()
{
	HiCPUHiIODlg	hchio;
	hchio.DoModal();
}


void CTestDlg::OnBasicsProcess()
{
	BscProcTest basicProcDlg;
	basicProcDlg.DoModal();	
}


void CTestDlg::OnBasicsThread()
{
	BscThreadTestDlg basicThreadDialog;
	basicThreadDialog.DoModal();
}


void CTestDlg::OnBasicsHandle()
{
	BscHandleTestDlg basicHandleDialog;
	basicHandleDialog.DoModal();
}
