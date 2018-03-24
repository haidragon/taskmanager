// mywinmodo.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "mywinmodo.h"
#include "afxdialogex.h"
// mywinmodo 对话框
IMPLEMENT_DYNAMIC(mywinmodo, CDialogEx)

mywinmodo::mywinmodo(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG4, pParent)
{

}

mywinmodo::~mywinmodo()
{
}

void mywinmodo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, mywinctrl);
}

BOOL CALLBACK  EnumWindowsProc(
	_In_ HWND   hwnd,
	_In_ LPARAM lParam
) {
    //把this指针传进来
	mywinmodo* allen=(mywinmodo*)lParam;
	if (allen != NULL) {
		static int num = 0;
		CString ctrHWND;
		ctrHWND.Format(L"%08x", hwnd);
		allen->mywinctrl.InsertItem(num, ctrHWND);
		TCHAR tch[1000] = { 0 };
		GetClassName(hwnd, tch, 240);
	    allen->mywinctrl.SetItemText(num, 1, tch);
		num++;
		return true;
	}
	return false;

}
void mywinmodo::Enumwin()
{
	::EnumWindows(&EnumWindowsProc,(LPARAM)this);


}


BEGIN_MESSAGE_MAP(mywinmodo, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()

void mywinmodo::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	mywinctrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	mywinctrl.GetClientRect(rc);
    nwidth = rc.Width();
	//	TCHAR   szModule[MAX_MODULE_NAME32 + 1];
	mywinctrl.InsertColumn(0, L"HWND", 0, nwidth / 2);
	mywinctrl.InsertColumn(1, L"classname", 1, nwidth / 2);

	Enumwin();

}
// mywinmodo 消息处理程序
