#pragma once
#include "afxwin.h"
#include "VirtualAllocOpsDlg.h"


// VirtualAllocOpsNew dialog

class VirtualAllocOpsNew : public CDialogEx
{
	DECLARE_DYNAMIC(VirtualAllocOpsNew)

public:
	VirtualAllocOpsNew(CWnd* pParent = NULL);   // standard constructor
	virtual ~VirtualAllocOpsNew();

// Dialog Data
	enum { IDD = IDD_DIALOG_VA_OPS_NEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	void SetControls();
	CEdit m_vaNewSize;
	CButton m_chkvaNewReserve;
	CButton m_chkvaNewCommit;
	CComboBox m_cmbvaNewProtection;
	CButton m_btnvaNewAllocate;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonVaOpsNewAllocate();
	VirtualAllocOpsDlg *m_dlgParent;
	void SetParentDialog(VirtualAllocOpsDlg* dlgParent);
	//long m_lSize;
	SIZE_T m_lSize;
	bool m_fReserve;
	bool m_fCommit;
	afx_msg void OnEnChangeEditVaOpsNewSize();
//	afx_msg void OnBnClickedCheckVaOpsNewReserved();
//	afx_msg void OnBnClickedCheckVaOpsNewCommit();
};
