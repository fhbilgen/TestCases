#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// HeapOperations dialog
#define MAX_HEAPS	10

class HeapOperations : public CDialogEx
{
	DECLARE_DYNAMIC(HeapOperations)

public:
	HeapOperations(CWnd* pParent = NULL);   // standard constructor
	virtual ~HeapOperations();

// Dialog Data
	enum { IDD = IDD_DIALOG_HEAP_OPERATIONS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnStnClickedStaticHeapOpsIniSize();
	CEdit m_edtInitHeapSize;
	int m_InitHeapSize;
	HANDLE m_hHeap;
	afx_msg void OnBnClickedButtonHeapOpsNewHeap();
	afx_msg void OnEnChangeEditHeapOpsIniSize();
	CStatic m_statNewHeap;
	virtual BOOL OnInitDialog();
	CEdit m_edtCount;
	int m_iCount;
	int m_iSize;
	CListCtrl m_lvHeapEntries;
	afx_msg void OnBnClickedButtonHeapOpsAlloc();
	void SetControls();
	afx_msg void OnEnChangeEditHeapOpsSize();
	afx_msg void OnEnChangeEditHeapOpsCount();
	CEdit m_edtSize;
	CButton m_btnNewHeap;
	afx_msg void OnBnClickedButtonHeapOpsFree();
};
