#pragma once


// CritSecDlg dialog

class CritSecDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CritSecDlg)

public:
	CritSecDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CritSecDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_CRITSEC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonCsDeadlock();
	afx_msg void OnBnClickedButtonCsOrphant();
};
