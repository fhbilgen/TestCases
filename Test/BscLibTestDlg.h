#pragma once
#include "afxdialogex.h"
#include "LibHandler.h"

// BscLibTestDlg dialog

class BscLibTestDlg : public CDialogEx
{
	DECLARE_DYNAMIC(BscLibTestDlg)
private:
	LibHandler m_lhCurrent;
	int	m_nOperation;

public:
	BscLibTestDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~BscLibTestDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_BSC_LIB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:

	CEdit m_edtLibStat;
	CButton m_btnLibLoad;
	CButton m_btnLibUnload;
	afx_msg void OnClickedButtonBsclibLoad();
	afx_msg void OnClickedButtonBsclibUnload();
	virtual BOOL OnInitDialog();
	CStatic m_gbOperations;
	afx_msg void OnClickedButtonBsclibCalculate();
	CButton m_btnLibCalc;
	CEdit m_edtParam1;
	CEdit m_edtParam2;
	CEdit m_edtResult;
};
