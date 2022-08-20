#pragma once
#include "afxdialogex.h"
#include "ThreadHandler.h"

// BscThreadTestDlg dialog

class BscThreadTestDlg : public CDialogEx
{
	DECLARE_DYNAMIC(BscThreadTestDlg)


private:
	ThreadHandler thCurrent;
public:
	BscThreadTestDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~BscThreadTestDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_BSC_THREAD};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CButton m_btnBscThreadCount;
	CEdit m_edtThreadCount;	
	CEdit m_edtThreadCountLimit;
	afx_msg void OnBnClickedButtonThreadCount();
};
