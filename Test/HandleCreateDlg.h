#pragma once


// HandleCreateDlg dialog

class HandleCreateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(HandleCreateDlg)

public:
	HandleCreateDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~HandleCreateDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_HANDLE_CREATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
