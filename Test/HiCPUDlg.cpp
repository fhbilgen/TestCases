// HiCPUDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "HiCPUDlg.h"
#include "afxdialogex.h"


extern HiCPUUtilizationProc	g_fnHiCPUUtilization;

// HiCPUDlg dialog

IMPLEMENT_DYNAMIC(HiCPUDlg, CDialogEx)

HiCPUDlg::HiCPUDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(HiCPUDlg::IDD, pParent)
	, m_iNumOfThreads(0)
{
	hHiCpu = CreateEvent(NULL, TRUE, FALSE, NULL);
}

HiCPUDlg::~HiCPUDlg()
{
	CloseHandle(hHiCpu);
}

void HiCPUDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_HICPU_NUMOFCORES, m_statCores);
	DDX_Control(pDX, IDC_EDIT_HICPU_NUMOFTHREADS, m_edtNumOfThreads);
	DDX_Text(pDX, IDC_EDIT_HICPU_NUMOFTHREADS, m_iNumOfThreads);

	DDX_Control(pDX, IDC_BUTTON_HICPU_START_THREADS, m_btnStartThreads);
	DDX_Control(pDX, IDC_BUTTON_HICPU_STOP_THREADS, m_btnStopThreads);
	DDX_Control(pDX, IDC_SPIN_NUM_OF_THREAD, m_spinNumOfThread);
}

// http://msdn.microsoft.com/en-us/library/ms683194(VS.85).aspx
// Helper function to count set bits in the processor mask.
DWORD HiCPUDlg::CountSetBits(ULONG_PTR bitMask)
{
	DWORD LSHIFT = sizeof(ULONG_PTR)* 8 - 1;
	DWORD bitSetCount = 0;
	ULONG_PTR bitTest = (ULONG_PTR)1 << LSHIFT;
	DWORD i;

	for (i = 0; i <= LSHIFT; ++i)
	{
		bitSetCount += ((bitMask & bitTest) ? 1 : 0);
		bitTest /= 2;
	}

	return bitSetCount;
}

UINT HiCPUDlg::NumberOfCores(void)
{
	LPFN_GLPI glpi;
	BOOL done = FALSE;
	PSYSTEM_LOGICAL_PROCESSOR_INFORMATION buffer = NULL;
	PSYSTEM_LOGICAL_PROCESSOR_INFORMATION ptr = NULL;
	DWORD returnLength = 0;
	DWORD logicalProcessorCount = 0;
	DWORD byteOffset = 0;

	glpi = (LPFN_GLPI)GetProcAddress(GetModuleHandle(TEXT("kernel32")), "GetLogicalProcessorInformation");
	if (NULL == glpi)
		return logicalProcessorCount;

	while (!done)
	{
		DWORD rc = glpi(buffer, &returnLength);

		if (FALSE == rc)
		{
			if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
			{
				if (buffer)
					free(buffer);

				buffer = (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION)malloc(
					returnLength);

				if (NULL == buffer)
					return logicalProcessorCount;
			}
			else
				return logicalProcessorCount;
		}
		else
			done = TRUE;
	}

	ptr = buffer;

	while (byteOffset + sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION) <= returnLength)
	{
		if (ptr->Relationship == RelationProcessorCore)
			logicalProcessorCount += CountSetBits(ptr->ProcessorMask);

		byteOffset += sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
		ptr++;
	}

	free(buffer);

	return logicalProcessorCount;
}

BEGIN_MESSAGE_MAP(HiCPUDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_HICPU_START_THREADS, &HiCPUDlg::OnBnClickedButtonHicpuStartThreads)
	ON_BN_CLICKED(IDC_BUTTON_HICPU_STOP_THREADS, &HiCPUDlg::OnBnClickedButtonHicpuStopThreads)
//	ON_EN_CHANGE(IDC_EDIT_HICPU_NUMOFTHREADS, &HiCPUDlg::OnEnChangeEditHicpuNumofthreads)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_NUM_OF_THREAD, &HiCPUDlg::OnDeltaposSpinNumOfThread)
END_MESSAGE_MAP()


// HiCPUDlg message handlers


void HiCPUDlg::OnBnClickedButtonHicpuStartThreads()
{
	
	UpdateData(TRUE);
		
	if (m_iNumOfThreads <= 0)	
	{
		AfxMessageBox(_T("You need to enter number greater than zero"), MB_OK, 0);
		return;
	}	
	
	ResetEvent(hHiCpu);
	(g_fnHiCPUUtilization)(m_iNumOfThreads, hHiCpu);

	m_btnStopThreads.EnableWindow(TRUE);
	m_btnStartThreads.EnableWindow(FALSE);

}


void HiCPUDlg::OnBnClickedButtonHicpuStopThreads()
{
	SetEvent(hHiCpu);

	m_btnStopThreads.EnableWindow(FALSE);
	m_btnStartThreads.EnableWindow(TRUE);
}


void HiCPUDlg::SetControls()
{
	int iCores = 0;
	int iSuggestedNumOfThreads = 0;
	_TCHAR	szNumOfCores[5];
	_TCHAR szSuggestedNumOfThreads[5];
	_TCHAR szCoreMessage[100];
	
	iCores = NumberOfCores();

	_itot_s(iCores, szNumOfCores, 5, 10);
	
	_stprintf_s(szCoreMessage, 100, _T("This computer has %s cores"), szNumOfCores);
	m_statCores.SetWindowTextW(szCoreMessage);

	if ( iCores < 4 )
		iSuggestedNumOfThreads = iCores;
	
	if (iCores >= 4 )
		iSuggestedNumOfThreads = iCores - 2;

	m_iNumOfThreads = iSuggestedNumOfThreads;

	_itot_s(iSuggestedNumOfThreads, szSuggestedNumOfThreads, 5, 10);
	m_edtNumOfThreads.SetWindowTextW(szSuggestedNumOfThreads);


	m_btnStopThreads.EnableWindow(FALSE);
	m_btnStartThreads.EnableWindow(TRUE);
	m_spinNumOfThread.SetRange(0, 100);

	UpdateData(TRUE);

}


BOOL HiCPUDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitializeCaseFunctions();
	SetControls();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}




//void HiCPUDlg::OnEnChangeEditHicpuNumofthreads()
//{
//	// TODO:  If this is a RICHEDIT control, the control will not
//	// send this notification unless you override the CDialogEx::OnInitDialog()
//	// function and call CRichEditCtrl().SetEventMask()
//	// with the ENM_CHANGE flag ORed into the mask.
//
//	// TODO:  Add your control notification handler code here
//	UpdateData(TRUE);
//}


void HiCPUDlg::OnDeltaposSpinNumOfThread(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	UpdateData(TRUE);
}
