#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// VirtualAllocDlg dialog

class VirtualAllocDlg : public CDialogEx
{
	DECLARE_DYNAMIC(VirtualAllocDlg)

public:
	VirtualAllocDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~VirtualAllocDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_VA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edtSize;
	int m_iSize;	
	CButton m_btnFill;
	CButton m_btnFree;
	virtual BOOL OnInitDialog();
	void SetControls();	
	_TCHAR*	m_wszMemoryBlock;
	afx_msg void OnBnClickedButtonVaAllocate();
	afx_msg void OnBnClickedButtonVaFree();
	CButton m_btnReserve;
	CButton m_btnCommit;
	CStatic m_statReserve;
	CStatic m_statCommit;
	CStatic m_statFill;
	CStatic m_statFree;
	afx_msg void OnBnClickedButtonVaReserve();
	afx_msg void OnEnChangeEditVaSize();
	afx_msg void OnBnClickedButtonVaCommit();
	afx_msg void OnBnClickedButtonVaFill();
	CProgressCtrl m_progWS;
	CProgressCtrl m_progVB;
	CProgressCtrl m_progPB;
	CEdit m_edtCommitSize;
	int m_iCommitSize;
	afx_msg void OnEnChangeEditVaCommitSize();
	afx_msg void OnBnClickedButtonVaFragment();
};
