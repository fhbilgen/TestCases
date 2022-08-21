#pragma once
#include "afxdialogex.h"
#include "FileHandler.h"
#include "MutexHandler.h"

// BscHandleTestDlg dialog

class BscHandleTestDlg : public CDialogEx
{
	DECLARE_DYNAMIC(BscHandleTestDlg)

private:
	int m_nFileMode;
	int m_nMutexMode;
	FileHandler m_fhCurrent;
	MutexHandler m_mhCurrent;

public:
	BscHandleTestDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~BscHandleTestDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_BSC_HANDLE};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CButton m_btnOpenFile;
	CButton m_btnCloseFile;
	CButton m_btnOpenMutex;
	CButton m_btnCloseMutex;
	CEdit m_edtFilePath;
	CEdit m_edtFileHandle;
	CEdit m_edtMutexName;
	CEdit m_edtMutexHandle;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonBschndlFile();
	afx_msg void OnBnClickedButtonBschndlFileClose();
	afx_msg void OnBnClickedButtonBschndlMutex();
	afx_msg void OnBnClickedButtonBschndlMutexClose();
};
