// VirtualAllocIncrease.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "VirtualAllocIncrease.h"
#include "afxdialogex.h"

#define MAX_TOTAL_DIGITS 15

// VirtualAllocIncrease dialog

IMPLEMENT_DYNAMIC(VirtualAllocIncrease, CDialogEx)

VirtualAllocIncrease::VirtualAllocIncrease(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_VA_INCREASE, pParent)
	, m_allocSize(0)
	, m_allocFrequency(0)
	, m_allocCommit(0)
	, m_allocDuration(0)	
	, m_Commit(0)
	, m_TimerFired(0)
	, m_totalReserv(0)
	, m_totalCommit(0)
	, m_totalUsage(0)
	, m_allocUsed(0)
{

}

VirtualAllocIncrease::~VirtualAllocIncrease()
{
}

void VirtualAllocIncrease::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_VA_INC_SIZE, m_allocSize);
	DDX_Text(pDX, IDC_EDIT_VA_INC_INTERVAL, m_allocFrequency);
	DDX_Text(pDX, IDC_EDIT_VA_INC_CMT_SIZE, m_allocCommit);
	DDX_Text(pDX, IDC_EDIT_VA_INC_DURATION, m_allocDuration);


	DDX_Control(pDX, IDC_EDIT_VA_INC_SIZE, m_edtAllocSize);
	DDX_Control(pDX, IDC_EDIT_VA_INC_CMT_SIZE, m_edtCommitSize);
	DDX_Control(pDX, IDC_EDIT_VA_INC_INTERVAL, m_edtAllocFrequency);
	DDX_Control(pDX, IDC_EDIT_VA_INC_DURATION, m_edtAllocDuration);
	DDX_Control(pDX, IDC_BUTTON_VA_INCREASE_START, m_btnStart);
	DDX_Control(pDX, IDC_BUTTON_VA_INCREASE_STOP, m_btnStop);

	DDX_Control(pDX, IDC_EDIT_VA_INC_INTERVAL3, m_edtStatus);
	DDX_Control(pDX, IDC_BUTTON_VA_INCREASE_FREE, m_btnFreeMemory);
	DDX_Control(pDX, IDC_EDT_VA_INC_TOTRESERVE, m_edtReservation);
	DDX_Control(pDX, IDC_EDT_VA_INC_TOTCOMMIT, m_edtCommitment);
	DDX_Text(pDX, IDC_EDIT_VA_INC_USAGE_SIZE, m_allocUsed);
	DDX_Control(pDX, IDC_EDIT_VA_INC_USAGE_SIZE, m_edtUseSize);
	DDX_Control(pDX, IDC_EDT_VA_INC_TOTUSED, m_edtUsage);
}




void VirtualAllocIncrease::SetControls()
{
	m_edtAllocDuration.Clear();
	m_edtAllocFrequency.Clear();
	m_edtAllocSize.Clear();
	m_edtCommitSize.Clear();
	m_edtUseSize.Clear();
	m_edtStatus.Clear();

	m_btnStop.EnableWindow(FALSE);
	m_btnStart.EnableWindow(TRUE);
	
	m_edtReservation.SetWindowTextW(_T("0"));
	m_edtCommitment.SetWindowTextW(_T("0"));
	m_edtUsage.SetWindowTextW(_T("0"));

	UpdateData(TRUE);
}
BEGIN_MESSAGE_MAP(VirtualAllocIncrease, CDialogEx)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_VA_INCREASE_START, &VirtualAllocIncrease::OnBnClickedButtonVaIncreaseStart)
	ON_BN_CLICKED(IDC_BUTTON_VA_INCREASE_FREE, &VirtualAllocIncrease::OnBnClickedButtonVaIncreaseFree)
	ON_BN_CLICKED(IDC_BUTTON_VA_INCREASE_STOP, &VirtualAllocIncrease::OnBnClickedButtonVaIncreaseStop)
	ON_EN_CHANGE(IDC_EDIT_VA_INC_SIZE, &VirtualAllocIncrease::OnEnChangeEditVaIncSize)
	ON_EN_CHANGE(IDC_EDIT_VA_INC_CMT_SIZE, &VirtualAllocIncrease::OnEnChangeEditVaIncCmtSize)
	ON_EN_CHANGE(IDC_EDIT_VA_INC_INTERVAL, &VirtualAllocIncrease::OnEnChangeEditVaIncInterval)
	ON_EN_CHANGE(IDC_EDIT_VA_INC_DURATION, &VirtualAllocIncrease::OnEnChangeEditVaIncDuration)
END_MESSAGE_MAP()


void VirtualAllocIncrease::OnTimer(UINT_PTR nIDEvent)
{

	BYTE* newAllocation = NULL;
	BYTE* newCommit = NULL;
	size_t regionSize = 0;

	DWORD dwError = S_OK;
	_TCHAR szTotalCommit[MAX_TOTAL_DIGITS];
	_TCHAR szTotalReserve[MAX_TOTAL_DIGITS];
	_TCHAR szTotalUsage[MAX_TOTAL_DIGITS];

	if (m_TimerFired < (m_allocDuration / m_allocFrequency))
	{		
		m_TimerFired++;
		regionSize = (size_t(m_allocSize) * size_t(1024));
		newAllocation = (BYTE*)VirtualAlloc(NULL, regionSize, MEM_RESERVE, PAGE_READWRITE);
		
		if (newAllocation == NULL)
		{
			dwError = GetLastError();
			m_edtStatus.SetWindowTextW(_T("VirtualAlloc for memory reservation failed"));
			return;
		}
		if (m_allocCommit != 0)
		{
			regionSize = (size_t(m_allocCommit) * size_t(1024));
			newCommit = (BYTE*)VirtualAlloc(newAllocation, regionSize, MEM_COMMIT, PAGE_READWRITE);

			if (newAllocation == NULL)
			{
				m_edtStatus.SetWindowTextW(_T("VirtualAlloc for memory commit failed"));
				return;
			}

			newAllocation += ((m_allocCommit) * 1024)-1;

			if (m_allocUsed != 0)
			{
				size_t regionSize = 0;
				regionSize = size_t(m_allocUsed) * size_t(1024)/ sizeof(BYTE);

				if (memset(newCommit, 170, regionSize) == NULL)
				{
					m_edtStatus.SetWindowTextW(_T("memset failed"));
					return;
				}
			}

		}
		
		m_totalReserv += (m_allocSize - m_allocCommit);
		m_totalCommit += m_allocCommit;
		m_totalUsage += m_allocUsed;

		if ( (m_allocSize-m_allocCommit) != 0)
			m_reservations.push(newAllocation);

		if (newCommit!=0)
			m_commits.push(newCommit);

		
		_stprintf_s(szTotalCommit, MAX_TOTAL_DIGITS, _T("%I64d"), m_totalCommit );
		_stprintf_s(szTotalReserve, MAX_TOTAL_DIGITS, _T("%I64d"), m_totalReserv);
		_stprintf_s(szTotalUsage, MAX_TOTAL_DIGITS, _T("%I64d"), m_totalUsage);

		m_edtReservation.SetWindowTextW(szTotalReserve);
		m_edtCommitment.SetWindowTextW(szTotalCommit);
		m_edtUsage.SetWindowTextW(szTotalUsage);
		m_edtStatus.SetWindowTextW(_T("Allocation OK"));
		
		UpdateData(TRUE);
	}
	else
	{
		KillTimer(WM_USER + 200);
		m_TimerFired = 0;
		m_btnStart.EnableWindow(TRUE);
		m_btnStop.EnableWindow(FALSE);
		m_edtStatus.SetWindowTextW(_T("Run is completed"));
	}

	CDialogEx::OnTimer(nIDEvent);
}


void VirtualAllocIncrease::OnBnClickedButtonVaIncreaseStart()
{
	SetTimer(WM_USER + 200, m_allocFrequency * 1000, NULL);
		
	m_btnStart.EnableWindow(FALSE);	
	m_btnStop.EnableWindow(TRUE);
}


void VirtualAllocIncrease::OnBnClickedButtonVaIncreaseFree()
{
	BYTE* ip = NULL;
	
	while (!(m_reservations.empty()))
	{
		ip = m_reservations.top();		
		VirtualFree(ip, 0, MEM_RELEASE);
		m_reservations.pop();
	}

	while (!(m_commits.empty()))
	{
		ip = m_commits.top();
		VirtualFree(ip, 0, MEM_RELEASE);
		m_commits.pop();
	}	

	m_totalCommit = 0;
	m_totalReserv = 0;
	m_totalUsage = 0;

	m_edtCommitment.SetWindowTextW(_T("0"));
	m_edtReservation.SetWindowTextW(_T("0"));
	m_edtUsage.SetWindowTextW(_T("0"));
	m_edtStatus.SetWindowTextW(_T(""));
	UpdateData(TRUE);
}


void VirtualAllocIncrease::OnBnClickedButtonVaIncreaseStop()
{
	KillTimer(WM_USER + 200);
	m_TimerFired = 0;
	m_btnStart.EnableWindow(TRUE);
	m_btnStop.EnableWindow(FALSE);
	m_edtStatus.SetWindowTextW(_T("Run is stopped"));
}


void VirtualAllocIncrease::OnEnChangeEditVaIncSize()
{
	UpdateData(TRUE);
}


void VirtualAllocIncrease::OnEnChangeEditVaIncCmtSize()
{
	UpdateData(TRUE);
}


void VirtualAllocIncrease::OnEnChangeEditVaIncInterval()
{
	UpdateData(TRUE);
}


void VirtualAllocIncrease::OnEnChangeEditVaIncDuration()
{
	UpdateData(TRUE);
}


BOOL VirtualAllocIncrease::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetControls();
	return TRUE;  
}
