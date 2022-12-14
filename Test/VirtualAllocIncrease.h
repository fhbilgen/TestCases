#pragma once

//#include "afxwin.h"
//#include "afxcmn.h"

using namespace std;
// VirtualAllocIncrease dialog

class VirtualAllocIncrease : public CDialogEx
{
	DECLARE_DYNAMIC(VirtualAllocIncrease)

public:
	VirtualAllocIncrease(CWnd* pParent = nullptr);   // standard constructor
	virtual ~VirtualAllocIncrease();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_VA_INCREASE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	//DECLARE_MESSAGE_MAP()
public:
		
	int m_allocSize;
	int m_allocFrequency;
	int m_allocCommit;
	int m_allocUsed;
	
	int m_allocDuration;
	int m_TimerFired;	
	int m_Commit;
	__int64 m_totalReserv;
	__int64 m_totalCommit;
	__int64 m_totalUsage;
	stack<BYTE*> m_reservations;
	stack<BYTE*> m_commits;
	CEdit m_edtAllocSize;
	CEdit m_edtCommitSize;
	CEdit m_edtAllocFrequency;
	CEdit m_edtAllocDuration;
	CEdit m_edtUseSize;
	void SetControls();
	CButton m_btnStart;
	CButton m_btnStop;		
	DECLARE_MESSAGE_MAP()
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonVaIncreaseStart();
	CEdit m_edtStatus;
	CButton m_btnFreeMemory;
	afx_msg void OnBnClickedButtonVaIncreaseFree();
	afx_msg void OnBnClickedButtonVaIncreaseStop();
	afx_msg void OnEnChangeEditVaIncSize();
	afx_msg void OnEnChangeEditVaIncCmtSize();
	afx_msg void OnEnChangeEditVaIncInterval();
	afx_msg void OnEnChangeEditVaIncDuration();	
	virtual BOOL OnInitDialog();
	CEdit m_edtReservation;
	CEdit m_edtCommitment;	
	CEdit m_edtUsage;
};
