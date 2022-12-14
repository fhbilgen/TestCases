// HiCPUHiIO.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "HiCPUHiIODlg.h"
#include "afxdialogex.h"
#include "..\TestHelpers\TestHelpers.h"

// HiCPUHiIO dialog

IMPLEMENT_DYNAMIC(HiCPUHiIODlg, CDialogEx)

HiCPUHiIODlg::HiCPUHiIODlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_HIGH_CPU_HIGH_IO, pParent)
	, m_iNumOfThreads(0)
	, m_iFileSize(0)
	, m_iNumberOfFiles(0)
{
	m_hController = NULL;
	m_hStop = CreateEvent(NULL, TRUE, FALSE, NULL);
}

HiCPUHiIODlg::~HiCPUHiIODlg()
{
}

void HiCPUHiIODlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDT_HICPUHIIO_CORECOUNT, m_edtCoreCount);

	DDX_Control(pDX, IDC_SPIN_HICPUHIIO_THREADCOUNT, m_spinNumOfThread);
	DDX_Text(pDX, IDC_EDT_HICPUHIIO_THREAD_COUNT, m_iNumOfThreads);
	DDX_Control(pDX, IDC_EDT_HICPUHIIO_THREAD_COUNT, m_edtNumOfThreads);
	DDX_Control(pDX, IDC_EDT_HICPUHIIO_FGIO_PATH, m_edtPath);	
	DDX_Control(pDX, IDC_EDT_HICPUHIIO_FILESIZE, m_edtFileSize);
	DDX_Text(pDX, IDC_EDT_HICPUHIIO_FILESIZE, m_iFileSize);
	DDX_Control(pDX, IDC_EDT_HICPUHIIO_FILECOUNT, m_edtNumberOfFiles);
	DDX_Text(pDX, IDC_EDT_HICPUHIIO_FILECOUNT, m_iNumberOfFiles);
	DDX_Control(pDX, IDC_EDT_HICPUHIIO_STAT, m_edtStatus);
}

BOOL HiCPUHiIODlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	InitializeCaseFunctions();
	SetControls();
	m_fEnableThreadChange = TRUE;
	return TRUE;  

}



// http://msdn.microsoft.com/en-us/library/ms683194(VS.85).aspx
// Helper function to count set bits in the processor mask.
DWORD HiCPUHiIODlg::CountSetBits(ULONG_PTR bitMask)
{
	DWORD LSHIFT = sizeof(ULONG_PTR) * 8 - 1;
	DWORD bitSetCount = 0;
	ULONG_PTR bitTest = (ULONG_PTR)1 << LSHIFT;
	DWORD i;

	for (i = 0; i <= LSHIFT; ++i)
	{
		bitSetCount += ((bitMask & bitTest) ? 1 : 0);
		bitTest /= 2;
	}

	return bitSetCount;
}

UINT HiCPUHiIODlg::NumberOfCores(void)
{
	LPFN_GLPI glpi;
	BOOL done = FALSE;
	PSYSTEM_LOGICAL_PROCESSOR_INFORMATION buffer = NULL;
	PSYSTEM_LOGICAL_PROCESSOR_INFORMATION ptr = NULL;
	DWORD returnLength = 0;
	DWORD logicalProcessorCount = 0;
	DWORD byteOffset = 0;

	glpi = (LPFN_GLPI)GetProcAddress(GetModuleHandle(TEXT("kernel32")), "GetLogicalProcessorInformation");
	if (NULL == glpi)
		return logicalProcessorCount;

	while (!done)
	{
		DWORD rc = glpi(buffer, &returnLength);

		if (FALSE == rc)
		{
			if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
			{
				if (buffer)
					free(buffer);

				buffer = (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION)malloc(
					returnLength);

				if (NULL == buffer)
					return logicalProcessorCount;
			}
			else
				return logicalProcessorCount;
		}
		else
			done = TRUE;
	}

	ptr = buffer;

	while (byteOffset + sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION) <= returnLength)
	{
		if (ptr->Relationship == RelationProcessorCore)
			logicalProcessorCount += CountSetBits(ptr->ProcessorMask);

		byteOffset += sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
		ptr++;
	}

	free(buffer);

	return logicalProcessorCount;
}

BEGIN_MESSAGE_MAP(HiCPUHiIODlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_HICPUHIIO_FGIO_PATH, &HiCPUHiIODlg::OnBnClickedBtnHicpuhiioFgioPath)
//	ON_EN_CHANGE(IDC_EDT_HICPUHIIO_THREAD_COUNT, &HiCPUHiIODlg::OnEnChangeEdtHicpuhiioThreadCount)
	ON_EN_CHANGE(IDC_EDT_HICPUHIIO_FGIO_PATH, &HiCPUHiIODlg::OnEnChangeEdtHicpuhiioFgioPath)
	ON_EN_CHANGE(IDC_EDT_HICPUHIIO_FILESIZE, &HiCPUHiIODlg::OnEnChangeEdtHicpuhiioFilesize)
	ON_EN_CHANGE(IDC_EDT_HICPUHIIO_FILECOUNT, &HiCPUHiIODlg::OnEnChangeEdtHicpuhiioFilecount)
	ON_BN_CLICKED(IDC_BTN_HICPUHIIO_START, &HiCPUHiIODlg::OnBnClickedBtnHicpuhiioStart)
	ON_BN_CLICKED(IDC_BTN_HICPUHIIO_STOP, &HiCPUHiIODlg::OnBnClickedBtnHicpuhiioStop)
	ON_EN_CHANGE(IDC_EDT_HICPUHIIO_THREAD_COUNT, &HiCPUHiIODlg::OnChangeEdtHicpuhiioThreadCount)
END_MESSAGE_MAP()


// HiCPUHiIO message handlers


// SetControls
void HiCPUHiIODlg::SetControls()
{
	int iCores = 0;
	int iSuggestedNumOfThreads = 0;
	_TCHAR	szNumOfCores[5];
	_TCHAR szSuggestedNumOfThreads[5];
	_TCHAR szCoreMessage[100];

	iCores = NumberOfCores();

	_itot_s(iCores, szNumOfCores, 5, 10);

	_stprintf_s(szCoreMessage, 100, _T("This computer has %s cores"), szNumOfCores);
	m_edtCoreCount.SetWindowTextW(szCoreMessage);

	iSuggestedNumOfThreads = iCores - 2;
	m_iNumOfThreads = iSuggestedNumOfThreads;

	_itot_s(iSuggestedNumOfThreads, szSuggestedNumOfThreads, 5, 10);
	m_edtNumOfThreads.SetWindowTextW(szSuggestedNumOfThreads);

	m_spinNumOfThread.SetRange(0, 100);
	
	m_edtPath.Clear();
	m_edtFileSize.Clear();
	m_edtNumberOfFiles.Clear();
	
	m_edtStatus.SetWindowTextW(_T(""));

	UpdateData(TRUE);
}



void HiCPUHiIODlg::OnBnClickedBtnHicpuhiioFgioPath()
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


void HiCPUHiIODlg::OnEnChangeEdtHicpuhiioFgioPath()
{
	UpdateData(TRUE);
}


void HiCPUHiIODlg::OnEnChangeEdtHicpuhiioFilesize()
{
	UpdateData(TRUE);
}


void HiCPUHiIODlg::OnEnChangeEdtHicpuhiioFilecount()
{
	UpdateData(TRUE);
}


void HiCPUHiIODlg::OnBnClickedBtnHicpuhiioStart()
{
	
	_TCHAR			szErrorMessage[100];
	
	UpdateData(FALSE);
		
	pIOEntry = (IOOPENTRY*)malloc(sizeof(IOOPENTRY));
	if (NULL == pIOEntry)
		return;

	fp = (FILEPROPS*)malloc(sizeof(FILEPROPS));
	if (NULL == fp)
		return;

	pIOEntry->lBufferSize = (long)pow(2,2 + 1) * 1024;
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

	
	pIOEntry->dwFlags = FILE_ATTRIBUTE_NORMAL;

	fp->dwFlags = pIOEntry->dwFlags;
	fp->fFlushBuffer = pIOEntry->fFlushBuffer;
	fp->lFileSize = pIOEntry->lFileSize;

	InitializeAndFillTheBuffer(pIOEntry->lBufferSize);

	// First create a thread and wait for it
	// The created thread should create the worker threads
	// this part is the body of the worker threads
	/*for (int i = 0; i != pIOEntry->lNumOfFiles; i++)
	{
		_stprintf_s(fp->szFileName, MAX_PATH, _T("%s\\Test_%d.txt"), pIOEntry->szPath, i);
		CreateWriteCloseFile((void*)fp);		
	}*/
	ThreadController();

	/*free(fp);
	free(pIOEntry);
	fp = NULL;
	pIOEntry = NULL;*/
}


DWORD HiCPUHiIODlg::ThreadController()
{
	DWORD   dwThreadID;
	DWORD	dwStatus = S_OK;
	int		*pInt = NULL;

	// There are better ways to close this handle. This is the easiest though.
	if (m_hController != NULL)
	{
		CloseHandle(m_hController);
		m_hController = NULL;
	}

//	g_HiCpuHandle = hStopEvent;

	pInt = (int*)malloc(sizeof(int));
	*pInt = m_iNumOfThreads;
	m_edtStatus.SetWindowTextW(_T(""));
	m_hController = CreateThread(NULL, 0, ThreadStarter, (void*) this, 0, &dwThreadID);

	if (m_hController == NULL)
		dwStatus = GetLastError();

	WaitForSingleObject(m_hController, INFINITE);
	m_edtStatus.SetWindowTextW(_T("All threads has been created"));

	return dwStatus;
}


DWORD HiCPUHiIODlg::ThreadManager()
{
	m_hThreads = (HANDLE*)malloc(sizeof(HANDLE)*m_iNumOfThreads);
	m_ThreadIDs = (DWORD*)malloc(sizeof(DWORD)*m_iNumOfThreads);

	if (m_hThreads == NULL)
		return E_OUTOFMEMORY;

	for (int i = 0; i != m_iNumOfThreads; i++)
	{
		m_hThreads[i] = CreateThread(NULL, 0, WorkerThreadStarter, (void*)this, 0, &(m_ThreadIDs[i]));
	}

	return S_OK;
}

// static method
DWORD WINAPI HiCPUHiIODlg::ThreadStarter(LPVOID data)
{
	HiCPUHiIODlg* This = (HiCPUHiIODlg*)data;
	return This->ThreadManager();
}

DWORD WINAPI HiCPUHiIODlg::WorkerThreadStarter(LPVOID data)
{
	HiCPUHiIODlg* This = (HiCPUHiIODlg*)data;
	return This->WorkerThread();
}

DWORD HiCPUHiIODlg::WorkerThread()
{
	DWORD dwStatus = S_OK;
	DWORD dwThreadID = GetCurrentThreadId();
	DWORD dwMinFileNo, dwMaxFileNo;
	dwMinFileNo = dwThreadID * pIOEntry->lNumOfFiles;
	dwMaxFileNo = dwMinFileNo + pIOEntry->lNumOfFiles;
	
	//for (int i = dwThreadID; i != pIOEntry->lNumOfFiles && (WaitForSingleObject(m_hStop, 0)== WAIT_TIMEOUT); i++)
	for (int i = dwMinFileNo; i != dwMaxFileNo && (WaitForSingleObject(m_hStop, 0) == WAIT_TIMEOUT); i++)
	{
		_stprintf_s(fp->szFileName, MAX_PATH, _T("%s\\Test_%d.txt"), pIOEntry->szPath, i);
		CreateWriteCloseFileSlow((void*)fp);
	}

	return dwStatus;
}

void HiCPUHiIODlg::OnBnClickedBtnHicpuhiioStop()
{
	SetEvent(m_hStop);
	WaitForMultipleObjects(m_iNumOfThreads, m_hThreads, TRUE, INFINITE);
	m_edtStatus.SetWindowTextW(_T("All threads has been terminated"));
}


void HiCPUHiIODlg::OnChangeEdtHicpuhiioThreadCount()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	if (m_fEnableThreadChange)
		UpdateData(TRUE);
	// TODO:  Add your control notification handler code here
}
