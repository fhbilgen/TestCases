#pragma once
#include "afxwin.h"
#include "afxcmn.h"

//typedef BOOL(WINAPI *LPFN_GLPI)(
//	PSYSTEM_LOGICAL_PROCESSOR_INFORMATION,
//	PDWORD);

// HiCPUDlg dialog

class HiCPUDlg : public CDialogEx
{
	DECLARE_DYNAMIC(HiCPUDlg)

public:
	HiCPUDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~HiCPUDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_HIGH_CPU };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DWORD CountSetBits(ULONG_PTR bitMask);
	UINT NumberOfCores(void);
	HANDLE hHiCpu = NULL;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonHicpuStartThreads();
	afx_msg void OnBnClickedButtonHicpuStopThreads();
	void SetControls();
	CStatic m_statCores;
	virtual BOOL OnInitDialog();
	int m_iNumOfThreads;
	CEdit m_edtNumOfThreads;
//	afx_msg void OnEnChangeEditHicpuNumofthreads();
	CButton m_btnStartThreads;
	CButton m_btnStopThreads;
	CSpinButtonCtrl m_spinNumOfThread;
	afx_msg void OnDeltaposSpinNumOfThread(NMHDR *pNMHDR, LRESULT *pResult);
};
