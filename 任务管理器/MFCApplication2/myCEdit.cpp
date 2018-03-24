// myCEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "myCEdit.h"


// myCEdit

IMPLEMENT_DYNAMIC(myCEdit, CEdit)

myCEdit::myCEdit()
{

}

myCEdit::~myCEdit()
{
}


BEGIN_MESSAGE_MAP(myCEdit, CEdit)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()



// myCEdit 消息处理程序




void myCEdit::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int DropCount = DragQueryFile(hDropInfo, -1, NULL, 0);//取得被拖动文件的数目 
	WCHAR wcStr[MAX_PATH];
	DragQueryFile(hDropInfo, 0, wcStr, MAX_PATH);//获得拖曳的第i个文件的文件名
	//第一个路径
	CString ctr2;
	ctr2.Format(L"%s", wcStr);
	
	SYSTEMTIME time;
	WIN32_FILE_ATTRIBUTE_DATA lpinf;
	CString TestDate;
	GetFileAttributesEx(ctr2, GetFileExInfoStandard, &lpinf);
	//创建时间
	FileTimeToSystemTime(&lpinf.ftCreationTime, &time);
	TestDate.Format(_T("创建时间：%d-%d-%d\r\n"), time.wYear, time.wMonth, time.wDay);
	ctr += TestDate;
	//最后修改时间
	FileTimeToSystemTime(&lpinf.ftLastWriteTime, &time);
	TestDate.Format(_T("最后修改时间：%d-%d-%d\r\n"), time.wYear, time.wMonth, time.wDay);
	ctr += TestDate;
	//最后进入时间
	FileTimeToSystemTime(&lpinf.ftLastAccessTime, &time);
	TestDate.Format(_T("最后访问时间：%d-%d-%d\r\n"), time.wYear, time.wMonth, time.wDay);
	ctr += TestDate;


	double size;
	CFileStatus fileStatus;

	if (CFile::GetStatus(ctr2, fileStatus))
	{
		size = fileStatus.m_size;
	}
	CString temp;
	temp.Format(L"大小：%f M\r\n", size / 1024.0 / 1024.0);
	ctr += temp;
	temp.Format(L"路径：%s\r\n", fileStatus.m_szFullName);
	ctr += temp;
	














	DragFinish(hDropInfo);  //拖放结束后,释放内存  
	//HWND myHWND = ::GetDlgItem((HWND)GetModuleHandle(NULL), IDC_EDIT3);
	//::SetWindowTextA((::GetDlgItem((HWND)GetModuleHandle(NULL), IDC_EDIT3)), (LPCSTR)wcStr);
	SetWindowText(ctr);
	ctr = "";
	CEdit::OnDropFiles(hDropInfo);
}
