#pragma once
#include "afxwin.h"


// InterProcWaitDlg dialog

class InterProcWaitDlg : public CDialogEx
{
	DECLARE_DYNAMIC(InterProcWaitDlg)

public:
	InterProcWaitDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~InterProcWaitDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_WAIT_PROCESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonIpGetResource();
	afx_msg void OnBnClickedButtonIpReleaseResource();
	void SetControls();
	CButton m_btnGetResource;
	CButton m_btnReleaseResource;
	CStatic m_picTrafficLight;
	CImage imgRedLight;
	CImage imgGreenLight;
	CStatic m_statStatus;
	CString m_strResourceWait;
	CString m_strResourceAcquired;
	CString m_strResourceReleased;
};
