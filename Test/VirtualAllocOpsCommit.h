#pragma once
#include "VirtualAllocOpsDlg.h"
#include "afxwin.h"

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

public :
	//int						m_lCommitSize;
	SIZE_T					m_lCommitSize;
	_TCHAR					*m_pStartAddress;
	DWORD					m_dwProtection;
	VirtualAllocOpsDlg		*m_dlgParent;
	void SetParentDialog(VirtualAllocOpsDlg* dlgParent);
	void SetCommitParams(_TCHAR* pStartAdress, int iCommitSize, DWORD	dwProtection);
	void SetControls();
	CEdit m_edtCommitSize;
	//int m_CommitSize;
	SIZE_T m_CommitSize;
	afx_msg void OnEnChangeEditVaOpsCommitSize();
	virtual BOOL OnInitDialog();
	CButton m_btnCommit;
	afx_msg void OnBnClickedButtonVaOpsCommitAllocate();
};
