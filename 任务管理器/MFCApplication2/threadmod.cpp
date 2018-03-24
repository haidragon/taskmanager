// threadmod.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "threadmod.h"
#include "afxdialogex.h"
#include<TlHelp32.h>

// threadmod 对话框

IMPLEMENT_DYNAMIC(threadmod, CDialogEx)

threadmod::threadmod(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	, threadid(_T(""))
{

}

threadmod::~threadmod()
{
}

void threadmod::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, mythreadlistctrl);

	DDX_Text(pDX, IDC_EDIT1, threadid);
}


BEGIN_MESSAGE_MAP(threadmod, CDialogEx)
	//ON_BN_CLICKED(IDOK, &threadmod::OnBnClickedOk)
	ON_WM_PAINT()
	ON_EN_CHANGE(IDC_EDIT1, &threadmod::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON1, &threadmod::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &threadmod::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &threadmod::OnBnClickedButton3)
END_MESSAGE_MAP()


// threadmod 消息处理程序


bool threadmod::Enumthread()
{
	// 1. 先创建快照
	HANDLE hTool32 = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (INVALID_HANDLE_VALUE == hTool32)
	{
		MessageBox(L"权限太低，看清名称不要瞎点！！！！");
		//printf("快照error!\n");
		return false;
	}
	//typedef struct tagTHREADENTRY32 {
	//	DWORD dwSize;
	//	DWORD cntUsage;
	//	DWORD th32ThreadID;
	//	DWORD th32OwnerProcessID;
	//	LONG  tpBasePri;
	//	LONG  tpDeltaPri;
	//	DWORD dwFlags;
	//} THREADENTRY32, *PTHREADENTRY32;
	// 2. 开始遍历进程
	THREADENTRY32 mi = { sizeof(THREADENTRY32) };
	BOOL bRet = Thread32First(hTool32, &mi);
	if (!bRet)
	{
		printf("Thread32First error!\n");
		return false;
	}
	
	mythreadlistctrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	CRect rc;
	mythreadlistctrl.GetClientRect(rc);
	DWORD nwidth = rc.Width();
	//	DWORD th32OwnerProcessID;
	mythreadlistctrl.InsertColumn(0, L"th32OwnerProcessID", 0, nwidth / 7);
	//	DWORD th32ThreadID;
	mythreadlistctrl.InsertColumn(1, L"th32ThreadID", 1, nwidth / 7);
	//	DWORD dwSize;
	mythreadlistctrl.InsertColumn(2, L"dwSize", 2, nwidth / 7);
	//	DWORD cntUsage;
	mythreadlistctrl.InsertColumn(3, L"cntUsage", 3, nwidth / 7);
	//	DWORD tpBasePri;
	mythreadlistctrl.InsertColumn(4, L"tpBasePri", 4, nwidth / 7);
	//	DWORD tpDeltaPri;
	mythreadlistctrl.InsertColumn(5, L"tpDeltaPri", 5, nwidth / 7);
	//	DWORD dwFlags;
	mythreadlistctrl.InsertColumn(6, L"dwFlags", 6, nwidth / 7);
	int i = 0;
	do
	{
		//	DWORD th32OwnerProcessID;
		CString th32OwnerProcessID;
		th32OwnerProcessID.Format(L"%4d", mi.th32OwnerProcessID);
		mythreadlistctrl.InsertItem(i, th32OwnerProcessID);
		//	DWORD th32ThreadID;
		CString th32ThreadID;
		th32ThreadID.Format(L"%4d", mi.th32ThreadID);
		mythreadlistctrl.SetItemText(i, 1, th32ThreadID);
		//	DWORD dwSize;
		CString dwSize;
		dwSize.Format(L"%4d", mi.dwSize);
		mythreadlistctrl.SetItemText(i, 2, dwSize);
		//	DWORD cntUsage;
		CString cntUsage;
		cntUsage.Format(L"%4d", mi.cntUsage);
		mythreadlistctrl.SetItemText(i, 3, cntUsage);
		//	DWORD tpBasePri;
		CString tpBasePri;
		tpBasePri.Format(L"%4d", mi.tpBasePri);
		mythreadlistctrl.SetItemText(i, 4, tpBasePri);
		//	DWORD tpDeltaPri;
		CString tpDeltaPri;
		tpDeltaPri.Format(L"%4d", mi.tpDeltaPri);
		mythreadlistctrl.SetItemText(i, 5, tpDeltaPri);
		//	DWORD dwFlags;
		CString dwFlags;
		dwFlags.Format(L"%4d", mi.dwFlags);
		mythreadlistctrl.SetItemText(i, 6, dwFlags);
		++i;

	} while (Thread32Next(hTool32, &mi));
	return false;
}

//void threadmod::OnBnClickedOk()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	CDialogEx::OnOK();
//
//
//}
void threadmod::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	Enumthread();

}

bool threadmod::Enumthread(DWORD pid)
{
	// 1. 先创建快照
	HANDLE hTool32 = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (INVALID_HANDLE_VALUE == hTool32)
	{
		MessageBox(L"权限太低，看清名称不要瞎点！！！！");
		//printf("快照error!\n");
		return false;
	}
	//typedef struct tagTHREADENTRY32 {
	//	DWORD dwSize;
	//	DWORD cntUsage;
	//	DWORD th32ThreadID;
	//	DWORD th32OwnerProcessID;
	//	LONG  tpBasePri;
	//	LONG  tpDeltaPri;
	//	DWORD dwFlags;
	//} THREADENTRY32, *PTHREADENTRY32;
	// 2. 开始遍历进程
	THREADENTRY32 mi = { sizeof(THREADENTRY32) };
	BOOL bRet = Thread32First(hTool32, &mi);
	if (!bRet)
	{
		printf("Thread32First error!\n");
		return false;
	}

	mythreadlistctrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	CRect rc;
	mythreadlistctrl.GetClientRect(rc);
	DWORD nwidth = rc.Width();
	//	DWORD th32OwnerProcessID;
	mythreadlistctrl.InsertColumn(0, L"th32OwnerProcessID", 0, nwidth / 7);
	//	DWORD th32ThreadID;
	mythreadlistctrl.InsertColumn(1, L"th32ThreadID", 1, nwidth / 7);
	//	DWORD dwSize;
	mythreadlistctrl.InsertColumn(2, L"dwSize", 2, nwidth / 7);
	//	DWORD cntUsage;
	mythreadlistctrl.InsertColumn(3, L"cntUsage", 3, nwidth / 7);
	//	DWORD tpBasePri;
	mythreadlistctrl.InsertColumn(4, L"tpBasePri", 4, nwidth / 7);
	//	DWORD tpDeltaPri;
	mythreadlistctrl.InsertColumn(5, L"tpDeltaPri", 5, nwidth / 7);
	//	DWORD dwFlags;
	mythreadlistctrl.InsertColumn(6, L"dwFlags", 6, nwidth / 7);
	int i = 0;
	do
	{
		if (mi.th32OwnerProcessID == pid) {
			//	DWORD th32OwnerProcessID;
			CString th32OwnerProcessID;
			th32OwnerProcessID.Format(L"%4d", mi.th32OwnerProcessID);
			mythreadlistctrl.InsertItem(i, th32OwnerProcessID);
			//	DWORD th32ThreadID;
			CString th32ThreadID;
			th32ThreadID.Format(L"%4d", mi.th32ThreadID);
			mythreadlistctrl.SetItemText(i, 1, th32ThreadID);
			//	DWORD dwSize;
			CString dwSize;
			dwSize.Format(L"%4d", mi.dwSize);
			mythreadlistctrl.SetItemText(i, 2, dwSize);
			//	DWORD cntUsage;
			CString cntUsage;
			cntUsage.Format(L"%4d", mi.cntUsage);
			mythreadlistctrl.SetItemText(i, 3, cntUsage);
			//	DWORD tpBasePri;
			CString tpBasePri;
			tpBasePri.Format(L"%4d", mi.tpBasePri);
			mythreadlistctrl.SetItemText(i, 4, tpBasePri);
			//	DWORD tpDeltaPri;
			CString tpDeltaPri;
			tpDeltaPri.Format(L"%4d", mi.tpDeltaPri);
			mythreadlistctrl.SetItemText(i, 5, tpDeltaPri);
			//	DWORD dwFlags;
			CString dwFlags;
			dwFlags.Format(L"%4d", mi.dwFlags);
			mythreadlistctrl.SetItemText(i, 6, dwFlags);
		}
		++i;

	} while (Thread32Next(hTool32, &mi));
	return false;
}


void threadmod::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
}

//挂起线程
void threadmod::OnBnClickedButton1()
{

	//MessageBox(threadid);
	// TODO: 在此添加控件通知处理程序代码
	if (threadid != "") {
		DWORD hid = _ttoi(threadid);
		HANDLE hihan =  OpenThread(THREAD_ALL_ACCESS, false,hid);
		if (SuspendThread(hihan)) {
			
			MessageBox(L"成功！");
		}
		else {
			MessageBox(L"失败！");
		}

	}
	else {
		MessageBox(L"请输入pid");
	}
}

//恢复线程
void threadmod::OnBnClickedButton2()
{
	//MessageBox(threadid);
	// TODO: 在此添加控件通知处理程序代码
	if (threadid != "") {
		DWORD hid = _ttoi(threadid);
		HANDLE hihan = OpenThread(THREAD_ALL_ACCESS, false, hid);
		if (ResumeThread(hihan)) {

			MessageBox(L"成功！");
		}
		else {
			MessageBox(L"失败！");
		}

	}
	else {
		MessageBox(L"请输入pid");
	}
}

//线束线程
void threadmod::OnBnClickedButton3()
{
	if (threadid != "") {
		DWORD hid = _ttoi(threadid);
		HANDLE hihan = OpenThread(THREAD_ALL_ACCESS, false, hid);
		if (TerminateThread(hihan,0)) {

			MessageBox(L"成功！");
		}
		else {
			MessageBox(L"失败！");
		}

	}
	else {
		MessageBox(L"请输入pid");
	}
}
