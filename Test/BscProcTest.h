#pragma once
#include "afxdialogex.h"
#include "ProcHandler.h"

// BscProcTest dialog

class BscProcTestDlg : public CDialogEx
{
	DECLARE_DYNAMIC(BscProcTestDlg)

public:
	BscProcTestDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~BscProcTestDlg();

	void ClearProcessInfo();
	void SetProcessInfo();
	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_BSC_PROC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonProcAppname();
private:
	ProcHandler phCurrent;
public:
	CEdit m_edtAppPath;
	afx_msg void OnClickedButtonProccreate();
	CEdit m_edtProcHandle;
	CEdit m_edtProcID;
	CEdit m_edtThreadHandle;
	CEdit m_edtThreadID;	
	CButton m_btnproc;
	CButton m_btnProcKill;
	CButton m_btnProcExit;
	afx_msg void OnClickedButtonProckill();
	afx_msg void OnClickedButtonProcexit();

};
