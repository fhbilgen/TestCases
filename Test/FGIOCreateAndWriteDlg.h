#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// FGIOCreateAndWriteDlg dialog

class FGIOCreateAndWriteDlg : public CDialogEx
{
	DECLARE_DYNAMIC(FGIOCreateAndWriteDlg)

public:
	FGIOCreateAndWriteDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~FGIOCreateAndWriteDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_FILE_GENERAL_IO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonFgioPath();
	CEdit m_edtPath;
	void SetControls();
	CComboBox m_cmbBufferSizes;
	CEdit m_edtFileSize;
	int m_iFileSize;
	CEdit m_edtNumberOfFiles;
	int m_iNumberOfFiles;
	CButton m_chkFlushBuffer;
	afx_msg void OnEnChangeEditFgioPath();
	afx_msg void OnEnChangeEditFgioFilesize();
	afx_msg void OnEnChangeEditFgioNumberoffiles();
	virtual BOOL OnInitDialog();
	CButton m_btnFGIOStart;
	afx_msg void OnBnClickedButtonFgioStart();
	CProgressCtrl m_progFileNumber;
	CStatic m_statStartTime;
	CStatic m_statCompleteTime;
	afx_msg void OnBnClickedButtonFgioClose();
	CButton m_chkWriteThrough;
	CButton m_chkNoBuffering;
	CStatic m_statThroughput;
};
