#pragma once
#include "..\TestHelpers\TestHelpers.h"

// HiCPUHiIO dialog

class HiCPUHiIODlg : public CDialogEx
{
	DECLARE_DYNAMIC(HiCPUHiIODlg)

public:
	HiCPUHiIODlg(CWnd* pParent = nullptr);   // standard constructor
	DWORD CountSetBits(ULONG_PTR bitMask);
	UINT NumberOfCores(void);
	virtual ~HiCPUHiIODlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_HIGH_CPU_HIGH_IO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	// SetControls
	void SetControls();
	CEdit m_edtCoreCount;
	virtual BOOL OnInitDialog();
	BOOL m_fEnableThreadChange = FALSE;
	
	CSpinButtonCtrl m_spinNumOfThread;
	
	CEdit m_edtNumOfThreads;
	int m_iNumOfThreads;
	CEdit m_edtPath;
	
	CEdit m_edtFileSize;
	int m_iFileSize;
	CEdit m_edtNumberOfFiles;
	int m_iNumberOfFiles;
	afx_msg void OnBnClickedBtnHicpuhiioFgioPath();
	//afx_msg void OnEnChangeEdtHicpuhiioThreadCount();
	afx_msg void OnEnChangeEdtHicpuhiioFgioPath();
	afx_msg void OnEnChangeEdtHicpuhiioFilesize();
	afx_msg void OnEnChangeEdtHicpuhiioFilecount();
	afx_msg void OnBnClickedBtnHicpuhiioStart();
	DWORD ThreadController();
	HANDLE	m_hController;
	HANDLE m_hStop = NULL;
	DWORD ThreadManager();
	DWORD WorkerThread();
	static DWORD WINAPI ThreadStarter(LPVOID data);
	static DWORD WINAPI WorkerThreadStarter(LPVOID data);
	IOOPENTRY		*pIOEntry;
	FILEPROPS		*fp = NULL;
	HANDLE* m_hThreads = NULL;
	DWORD* m_ThreadIDs = NULL;
	afx_msg void OnBnClickedBtnHicpuhiioStop();
	CEdit m_edtStatus;
	afx_msg void OnChangeEdtHicpuhiioThreadCount();
};
