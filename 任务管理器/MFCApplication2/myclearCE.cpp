// myclearCE.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "myclearCE.h"


// myclearCE

IMPLEMENT_DYNAMIC(myclearCE, CEdit)

myclearCE::myclearCE()
{

}

myclearCE::~myclearCE()
{
}


BEGIN_MESSAGE_MAP(myclearCE, CEdit)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()



// myclearCE 消息处理程序




void myclearCE::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int DropCount = DragQueryFile(hDropInfo, -1, NULL, 0);//取得被拖动文件的数目 
	WCHAR wcStr[MAX_PATH];
	DragQueryFile(hDropInfo, 0, wcStr, MAX_PATH);//获得拖曳的第i个文件的文件名
	//根目录
	CString ctr2;
	ctr2.Format(L"%s", wcStr);
	rootctr = ctr2;
	ctr2.Format(L"%s\r\n", wcStr);
	myctr += ctr2;
	MessageBox(L"确定要删除吗？");
	EnumLoad(wcStr);
	DragFinish(hDropInfo);  //拖放结束后,释放内存 
	MessageBox(L"清理成功！");
	//SetWindowText(myctr);
	//HWND myHWND = ::GetDlgItem((HWND)GetModuleHandle(NULL), IDC_EDIT3);
	//::SetWindowTextA((::GetDlgItem((HWND)GetModuleHandle(NULL), IDC_EDIT3)), (LPCSTR)wcStr);
	CEdit::OnDropFiles(hDropInfo);
}
void myclearCE::EnumLoad(TCHAR * load)
{
	BOOL Flag = FALSE;
	TCHAR szSearchPath[MAX_PATH] = {};
	_stprintf_s(szSearchPath, MAX_PATH, L"%s\\*.*", load);
	WIN32_FIND_DATA wsd = {};
	HANDLE hFile = FindFirstFile(szSearchPath, &wsd);
	if (hFile == INVALID_HANDLE_VALUE) {
		return;
	}
	do {
		if (wsd.cFileName[0] == '.') {
			continue;
		}
		if (wsd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY) {
			TCHAR oppo[MAX_PATH];
			_stprintf_s(oppo, MAX_PATH, L"%s\\%s", load, wsd.cFileName);
			if (_tcscmp(L"Debug", wsd.cFileName) == 0 || _tcscmp(L"x64", wsd.cFileName) == 0 || _tcscmp(L"Release", wsd.cFileName) == 0
				|| _tcscmp(L"ipch", wsd.cFileName) == 0) {
				//_stprintf_s(oppo, MAX_PATH, L"%s%s", oppo, "\0");
				SetWindowText(oppo);
				deleteFolder(oppo);
				
				continue;
			}
			EnumLoad(oppo);
		}
		else {
			int Size = _tcslen(wsd.cFileName);
			if (NULL != StrStr(wsd.cFileName, L".db")) {
				TCHAR oppoStr[MAX_PATH];
				_stprintf_s(oppoStr, MAX_PATH, L"%s\\%s", load, wsd.cFileName);
				//deleteFolder(oppoStr);
				SetWindowText(oppoStr);
				DeleteFile(oppoStr);
				
			}

		}
	} while (FindNextFile(hFile, &wsd));
}

void myclearCE::deleteFolder(TCHAR * load)
{


	/*char c[100] = {};
	CString temp1;
	temp1.Format(L"rd /s/q  %s", load);

	WCHAR_TO_CHAR(temp1.GetBuffer(), c);
	system(c);*/
	SHFILEOPSTRUCT FileOp = {};
	FileOp.fFlags = FOF_NOCONFIRMATION;
	//	FileOp.hNameMappings = NULL;
	//	FileOp.hwnd = NULL;
	//	FileOp.lpszProgressTitle = NULL;
	CString temp = load;
	temp += '\0';
	FileOp.pFrom = temp;
	//	FileOp.pTo = NULL;
	FileOp.wFunc = FO_DELETE;
	SHFileOperation(&FileOp);

}