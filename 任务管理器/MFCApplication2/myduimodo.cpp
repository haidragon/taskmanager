// myduimodo.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "myduimodo.h"
#include "afxdialogex.h"
#include<TlHelp32.h>


// myduimodo 对话框

IMPLEMENT_DYNAMIC(myduimodo, CDialogEx)

myduimodo::myduimodo(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{

}

myduimodo::~myduimodo()
{
}

bool myduimodo::Enumheap(DWORD PID)
{
	// 1. 先创建快照
	HANDLE hHeapSnap = CreateToolhelp32Snapshot(TH32CS_SNAPHEAPLIST, PID);
	if (INVALID_HANDLE_VALUE == hHeapSnap)
	{
		MessageBox(L"权限不够或打错，请重试！");
		//printf("快照error!\n");
		return false;
	}
	
	// 2. 开始遍历进程
	
	HEAPLIST32  mi = { sizeof(HEAPLIST32) };
	BOOL bRet = Heap32ListFirst(hHeapSnap, &mi);
	if (!bRet)
	{
		printf("Thread32First error!\n");
		return false;
	}

	myduictrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	CRect rc;
	myduictrl.GetClientRect(rc);
	DWORD nwidth = rc.Width();
	//typedef struct tagHEAPLIST32 {
	//	SIZE_T    dwSize;
	//	DWORD     th32ProcessID;
	//	ULONG_PTR th32HeapID;
	//	DWORD     dwFlags;
	//} HEAPLIST32, *PHEAPLIST32;
	//	DWORD th32HeapID;
	myduictrl.InsertColumn(0, L"th32HeapID", 0, nwidth / 4);
	//	DWORD th32ProcessID;
	myduictrl.InsertColumn(1, L"th32ProcessID", 1, nwidth / 4);
	//	DWORD dwSize;
	myduictrl.InsertColumn(2, L"dwSize", 2, nwidth / 4);
	//	DWORD dwFlags;
	myduictrl.InsertColumn(6, L"dwFlags", 6, nwidth / 4);
	int i = 0;
	do
	{
			//	DWORD th32HeapID;
			CString th32HeapID;
			th32HeapID.Format(L"%4d", mi.th32HeapID);
			myduictrl.InsertItem(i, th32HeapID);
			//	DWORD th32ProcessID;
			CString th32ProcessID;
			th32ProcessID.Format(L"%4d", mi.th32ProcessID);
			myduictrl.SetItemText(i, 1, th32ProcessID);
			//	DWORD dwSize;
			CString dwSize;
			dwSize.Format(L"%4d", mi.dwSize);
			myduictrl.SetItemText(i, 2, dwSize);
			//	DWORD dwFlags;
			CString dwFlags;
			dwFlags.Format(L"%4d", mi.dwFlags);
			myduictrl.SetItemText(i, 3, dwFlags);
		++i;

	} while (Heap32ListNext(hHeapSnap, &mi));
	return false;
}

void myduimodo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, myduictrl);
}


BEGIN_MESSAGE_MAP(myduimodo, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()

void myduimodo::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	
	Enumheap(pid);
}

// myduimodo 消息处理程序
