
// TestDlg.h : header file
//

#pragma once


// CTestDlg dialog
class CTestDlg : public CDialogEx
{
// Construction
public:
	CTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnHangCriticalsection();
	afx_msg void OnHangWaitanotherprocess();
	afx_msg void OnCpuHighutilization();
	afx_msg void OnExceptionsAvDivbyzero();
	afx_msg void OnMemoryVirtualalloc();
	afx_msg void OnMemoryVirtualallocationoperations();
	afx_msg void OnIoFilecreate();
	afx_msg void OnMemoryHeapoperations();
	afx_msg void OnMemoryVirtualmemincreaseovertime();
	afx_msg void OnCpuHighutilizationhighfilei();
	afx_msg void OnBasicsProcess();
	afx_msg void OnBasicsThread();
	afx_msg void OnBasicsHandle();
};
