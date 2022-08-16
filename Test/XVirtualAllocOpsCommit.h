#pragma once
#include "afxwin.h"
#include "VirtualAllocOpsDlg.h"

// VirtualAllocOpsCommit dialog

class VirtualAllocOpsCommit : public CDialogEx
{
	DECLARE_DYNAMIC(VirtualAllocOpsCommit)

public:
	VirtualAllocOpsCommit(CWnd* pParent = NULL);   // standard constructor
	virtual ~VirtualAllocOpsCommit();

// Dialog Data
	enum { IDD = IDD_DIALOG_VA_OPS_COMMIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	void SetControls();
	CEdit m_edtCommitSize;
	long m_lCommitSize;
	afx_msg void OnBnClickedButtonVaOpsCommitCommit();
	VirtualAllocOpsDlg* m_dlgParent;
	void SetParentDialog(VirtualAllocOpsDlg* dlgParent);
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeEditVaOpsCommitSize();
};
