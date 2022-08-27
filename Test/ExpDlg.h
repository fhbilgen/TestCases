#pragma once


// ExpDlg dialog

class ExpDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ExpDlg)

public:
	ExpDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~ExpDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_EXP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonExpAv();
	afx_msg void OnBnClickedButtonAvWithHandler();
	afx_msg void OnBnClickedButtonExpDivByZero();
	virtual BOOL OnInitDialog();
};
