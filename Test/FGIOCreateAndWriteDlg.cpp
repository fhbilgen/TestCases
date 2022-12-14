// FGIOCreateAndWriteDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "FGIOCreateAndWriteDlg.h"
#include "afxdialogex.h"
#include "..\TestHelpers\TestHelpers.h"


// FGIOCreateAndWriteDlg dialog

IMPLEMENT_DYNAMIC(FGIOCreateAndWriteDlg, CDialogEx)

FGIOCreateAndWriteDlg::FGIOCreateAndWriteDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(FGIOCreateAndWriteDlg::IDD, pParent)
	, m_iFileSize(0)
	, m_iNumberOfFiles(0)
{

}

FGIOCreateAndWriteDlg::~FGIOCreateAndWriteDlg()
{
}

void FGIOCreateAndWriteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_FGIO_PATH, m_edtPath);
	DDX_Control(pDX, IDC_COMBO_FGIO_BUFFERSIZE, m_cmbBufferSizes);
	DDX_Control(pDX, IDC_EDIT_FGIO_FILESIZE, m_edtFileSize);
	DDX_Control(pDX, IDC_EDIT_FGIO_NUMBEROFFILES, m_edtNumberOfFiles);
	DDX_Control(pDX, IDC_CHECK_FGIO_FLUSHBUFFER, m_chkFlushBuffer);
	DDX_Text(pDX, IDC_EDIT_FGIO_FILESIZE, m_iFileSize);
	DDX_Text(pDX, IDC_EDIT_FGIO_NUMBEROFFILES, m_iNumberOfFiles);
	DDX_Control(pDX, IDC_BUTTON_FGIO_START, m_btnFGIOStart);
	DDX_Control(pDX, IDC_PROGRESS_FGIO, m_progFileNumber);
	DDX_Control(pDX, IDC_STATIC_FGIO_START_TIME, m_statStartTime);
	DDX_Control(pDX, IDC_STATIC_FGIO_COMPLETE_TIME, m_statCompleteTime);
	DDX_Control(pDX, IDC_CHECK_FGIO_WRITE_THROUGH, m_chkWriteThrough);
	DDX_Control(pDX, IDC_CHECK_FGIO_NO_BUFFERING, m_chkNoBuffering);
	DDX_Control(pDX, IDC_STATIC_FGIO_THROUGHPUT, m_statThroughput);
}


BEGIN_MESSAGE_MAP(FGIOCreateAndWriteDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_FGIO_PATH, &FGIOCreateAndWriteDlg::OnBnClickedButtonFgioPath)
	ON_EN_CHANGE(IDC_EDIT_FGIO_PATH, &FGIOCreateAndWriteDlg::OnEnChangeEditFgioPath)
	ON_EN_CHANGE(IDC_EDIT_FGIO_FILESIZE, &FGIOCreateAndWriteDlg::OnEnChangeEditFgioFilesize)
	ON_EN_CHANGE(IDC_EDIT_FGIO_NUMBEROFFILES, &FGIOCreateAndWriteDlg::OnEnChangeEditFgioNumberoffiles)
	ON_BN_CLICKED(IDC_BUTTON_FGIO_START, &FGIOCreateAndWriteDlg::OnBnClickedButtonFgioStart)
	ON_BN_CLICKED(IDC_BUTTON_FGIO_CLOSE, &FGIOCreateAndWriteDlg::OnBnClickedButtonFgioClose)
END_MESSAGE_MAP()


// FGIOCreateAndWriteDlg message handlers

void FGIOCreateAndWriteDlg::OnBnClickedButtonFgioPath()
{
		
	CString pathName;
	_TCHAR* path = NULL;
	CFileDialog dlgFile(TRUE, NULL, NULL, OFN_EXPLORER, NULL, NULL, 0, TRUE);
	CFolderPickerDialog dlgFP(NULL, BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE, NULL, NULL);

	dlgFP.DoModal();
	pathName = dlgFP.GetPathName();

	int ln = pathName.GetLength() + 1;
	path = (_TCHAR*)malloc(sizeof(_TCHAR) * ln);

	if (path != NULL)
		_tcscpy_s(path, ln, (const _TCHAR*)pathName);


	if (path != nullptr && *path != '\0')
	{
		
		m_edtPath.SetWindowTextW(path);
		free(path);
	}
		
}


void FGIOCreateAndWriteDlg::SetControls()
{
	m_cmbBufferSizes.AddString(_T("   2"));
	m_cmbBufferSizes.AddString(_T("   4"));
	m_cmbBufferSizes.AddString(_T("   8"));
	m_cmbBufferSizes.AddString(_T("  16"));
	m_cmbBufferSizes.AddString(_T("  32"));
	m_cmbBufferSizes.AddString(_T("  64"));
	m_cmbBufferSizes.AddString(_T(" 128"));
	m_cmbBufferSizes.AddString(_T(" 256"));
	m_cmbBufferSizes.AddString(_T(" 512"));
	m_cmbBufferSizes.AddString(_T("1024"));
	m_cmbBufferSizes.SetCurSel(0);

	m_progFileNumber.SetRange(0, 100);
	m_progFileNumber.SetStep(1);
	m_edtPath.Clear();
	m_edtFileSize.Clear();
	m_edtNumberOfFiles.Clear();
	m_chkFlushBuffer.SetState(FALSE);
}


void FGIOCreateAndWriteDlg::OnEnChangeEditFgioPath()
{
	UpdateData(TRUE);
}


void FGIOCreateAndWriteDlg::OnEnChangeEditFgioFilesize()
{
	UpdateData(TRUE);
}


void FGIOCreateAndWriteDlg::OnEnChangeEditFgioNumberoffiles()
{	
	UpdateData(TRUE);
}


BOOL FGIOCreateAndWriteDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	SetControls();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void FGIOCreateAndWriteDlg::OnBnClickedButtonFgioStart()
{
	IOOPENTRY		*pIOEntry = NULL;
	FILEPROPS		*fp = NULL;
	SYSTEMTIME		st, st2;
	ULONGLONG		tickStart = 0, tickEnd = 0;
	_TCHAR			szStartTime[100];
	_TCHAR			szCompleteTime[100];
	_TCHAR			szErrorMessage[100];
	int				curPos = 1, newPos = 0;
	long			lThroughput = 0;
	_TCHAR			szThroughPut[100];
		
	pIOEntry = (IOOPENTRY*)malloc( sizeof(IOOPENTRY) );
	if (NULL == pIOEntry)
		return;

	fp = (FILEPROPS*)malloc(sizeof(FILEPROPS));
	if (NULL == fp)
		return;

	pIOEntry->lBufferSize = (long)pow(2, m_cmbBufferSizes.GetCurSel() + 1) * 1024;
	pIOEntry->lFileSize = m_iFileSize * 1024;
	pIOEntry->lNumOfFiles = m_iNumberOfFiles;
	
	if (pIOEntry->lFileSize < pIOEntry->lBufferSize)
	{
		_stprintf_s(szErrorMessage, 100, _T("A file size smaller than the buffer size does not make sense. Operation is cancelled."));
		AfxMessageBox(szErrorMessage, MB_ICONERROR | MB_OK, 0);
		free(pIOEntry);
		free(fp);
		return;
	}

	m_edtPath.GetWindowTextW(pIOEntry->szPath, MAX_PATH);

	if (BST_CHECKED == m_chkFlushBuffer.GetState())
		pIOEntry->fFlushBuffer = TRUE;
	else
		pIOEntry->fFlushBuffer = FALSE;


	pIOEntry->dwFlags = 0;
	
	if (BST_CHECKED == m_chkWriteThrough.GetState())
		pIOEntry->dwFlags |= FILE_FLAG_WRITE_THROUGH;

	if (BST_CHECKED == m_chkNoBuffering.GetState())
		pIOEntry->dwFlags |= FILE_FLAG_NO_BUFFERING;

	// FILE_ATTRIBUTE_NORMAL should be used alone
	if (!pIOEntry->dwFlags)
		pIOEntry->dwFlags = FILE_ATTRIBUTE_NORMAL;

	fp->dwFlags = pIOEntry->dwFlags;
	fp->fFlushBuffer = pIOEntry->fFlushBuffer;
	fp->lFileSize = pIOEntry->lFileSize;

	m_progFileNumber.SetPos(0);
	curPos = 1;
	
	GetLocalTime(&st);	
	_stprintf_s(szStartTime, 100, _T("Started at %02d:%02d:%02d.%03d"), st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
	m_statStartTime.SetWindowTextW(szStartTime);
	m_statCompleteTime.SetWindowTextW(_T("Completed at "));	// we don't want to display previous end time
	m_statThroughput.SetWindowTextW( _T(" bytes/sec") );

	InitializeAndFillTheBuffer(pIOEntry->lBufferSize);
	tickStart = GetTickCount64();
	for (int i = 0; i != pIOEntry->lNumOfFiles; i++)
	{
		_stprintf_s(fp->szFileName, MAX_PATH, _T("%s\\Test_%d.txt"), pIOEntry->szPath, i);
		CreateWriteCloseFile((void*)fp);
		
		newPos = int((double)(i + 1.0) / (double)(pIOEntry->lNumOfFiles) * 100.0);
		if (newPos > curPos)			
			m_progFileNumber.SetPos(newPos);		
	}
	tickEnd = GetTickCount64();
	GetLocalTime(&st2);
	_stprintf_s(szCompleteTime, 100, _T("Completed at %02d:%02d:%02d.%03d"), st2.wHour, st2.wMinute, st2.wSecond, st2.wMilliseconds);
	m_statCompleteTime.SetWindowTextW(szCompleteTime);

	lThroughput = (long)(((double)pIOEntry->lNumOfFiles * (double)pIOEntry->lFileSize*1024.0) / double(tickEnd - tickStart) / 1000.0);
	//_stprintf_s(szThroughPut, 100, _T("%d bytes/sec"), pIOEntry->szPath, lThroughput);
	_stprintf_s(szThroughPut, 100, _T("%d bytes/sec"), lThroughput);
	m_statThroughput.SetWindowTextW(szThroughPut);
	
	_stprintf_s(szThroughPut, 100, _T("%lld"), tickEnd-tickStart);
	AfxMessageBox(szThroughPut, MB_OK, 0);
	free(fp);	
	free(pIOEntry);
	fp = NULL;
	pIOEntry = NULL;

}


void FGIOCreateAndWriteDlg::OnBnClickedButtonFgioClose()
{
	this->EndDialog(IDOK);
}
