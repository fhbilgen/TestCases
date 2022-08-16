#pragma once
#include "afxcmn.h"
#include "..\TestHelpers\TestHelpers.h"

// VirtualAllocOpsDlg dialog

class VirtualAllocOpsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(VirtualAllocOpsDlg)

public:
	VirtualAllocOpsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~VirtualAllocOpsDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_VA_OPERATIONS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	void SetControls();
	void LVAddData(CListCtrl &ctrl, int row, int col, const wchar_t *str);
	void LVUpdateData(CListCtrl &ctrl, int row, int col, const wchar_t *str);
	void ResetVAEntry();
	static int filterFunc(unsigned int code, struct _EXCEPTION_POINTERS *ep);
	static void BlockFill(_TCHAR* pStartAddress,int iSize);
	CListCtrl m_lvEntries;
	virtual BOOL OnInitDialog();
	afx_msg void OnNMRClickListVaEntries(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNewNew();
	afx_msg void OnNewCommit();
	afx_msg void OnNewFree();
	afx_msg void OnNewFill();

	// Member to control the current allocation
	VAENTRY	m_VAEntry;
	VAENTRY* GetVAEntryFromLV(int iRow);
	void InsertAllocation();
	void UpdateAllocation(int iRow);
	void DeleteAllocation(int iRow);
	
};
