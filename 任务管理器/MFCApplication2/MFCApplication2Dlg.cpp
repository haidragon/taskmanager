
// MFCApplication2Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "MFCApplication2Dlg.h"
#include "afxdialogex.h"
#include<TlHelp32.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//CString CAboutDlg::ctrpath = L"";

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication2Dlg 对话框



CMFCApplication2Dlg::CMFCApplication2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCAPPLICATION2_DIALOG, pParent)
	, cpustr(_T(""))
	, ctrpath(_T(""))
	, filestr(_T(""))
	//, mycleactr(_T(""))
	, myclearctring(_T(""))
	, mypidctr(_T(""))
	, mypidheap(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, cclistctrl);
	//DDX_Text(pDX, IDC_EDIT1, myctr);
	DDX_Text(pDX, IDC_EDIT1, cpustr);
	DDX_Control(pDX, IDC_EDIT1, myCpuEdit);
	DDX_Text(pDX, IDC_EDIT4, ctrpath);
	DDX_Text(pDX, IDC_EDIT3, filestr);
	DDX_Control(pDX, IDC_EDIT3, myfileCEdit);
	DDX_Control(pDX, IDC_EDIT2, myclear);
	//DDX_Text(pDX, IDC_EDIT2, mycleactr);
	DDX_Text(pDX, IDC_EDIT2, myclearctring);
	DDX_Text(pDX, IDC_EDIT5, mypidctr);
	DDX_Text(pDX, IDC_EDIT6, mypidheap);
}

BEGIN_MESSAGE_MAP(CMFCApplication2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CMFCApplication2Dlg::OnNMClickList1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CMFCApplication2Dlg::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication2Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication2Dlg::OnBnClickedButton2)
	//ON_EN_CHANGE(IDC_EDIT1, &CMFCApplication2Dlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication2Dlg::OnBnClickedButton3)
	ON_EN_CHANGE(IDC_EDIT1, &CMFCApplication2Dlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCApplication2Dlg::OnBnClickedButton4)
	//ON_BN_CLICKED(IDC_BUTTON5, &CMFCApplication2Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CMFCApplication2Dlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CMFCApplication2Dlg::OnBnClickedButton7)
	ON_EN_CHANGE(IDC_EDIT3, &CMFCApplication2Dlg::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, &CMFCApplication2Dlg::OnEnChangeEdit4)
	//ON_BN_CLICKED(IDC_BUTTON5, &CMFCApplication2Dlg::OnBnClickedButton5)
	ON_EN_CHANGE(IDC_EDIT2, &CMFCApplication2Dlg::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCApplication2Dlg::OnBnClickedButton5)
	ON_EN_CHANGE(IDC_EDIT5, &CMFCApplication2Dlg::OnEnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT6, &CMFCApplication2Dlg::OnEnChangeEdit6)
	ON_BN_CLICKED(IDC_BUTTON8, &CMFCApplication2Dlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CMFCApplication2Dlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CMFCApplication2Dlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CMFCApplication2Dlg::OnBnClickedButton11)
	ON_WM_HOTKEY()

END_MESSAGE_MAP()


// CMFCApplication2Dlg 消息处理程序

BOOL CMFCApplication2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//MessageBox(L"点击进程号列出当前进程的所有模块!!!!!");


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	myCpuEdit.SetReadOnly(TRUE);
	//myfileCEdit.SetReadOnly(TRUE);
	myfileCEdit.DragAcceptFiles(TRUE);
	HWND myallen = (HWND)::GetModuleHandle(NULL);
	::RegisterHotKey(this->m_hWnd, 0x1234, MOD_CONTROL, 'G');
	EnumProcess();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


bool CMFCApplication2Dlg::EnumProcess() {
	// 1. 先创建快照
	HANDLE hTool32 = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (INVALID_HANDLE_VALUE == hTool32)
	{
		printf("快照error!\n");
		return false;
	}
	// 2. 开始遍历进程
	PROCESSENTRY32W psi = { sizeof(PROCESSENTRY32W) };
	BOOL bRet = Process32FirstW(hTool32, &psi);
	if (!bRet)
	{
		//printf("Process32FirstW error!\n");
		return false;
	}
	//printf("PID    EXE:\n");
	int i = 0;
	cclistctrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	cclistctrl.GetClientRect(rc);
	nwidth = rc.Width();
	cclistctrl.InsertColumn(0, L"名称", 0, nwidth / 6);
	cclistctrl.InsertColumn(1, L"dwSize", 1, nwidth / 8);
	cclistctrl.InsertColumn(2, L"cntUsage", 2, nwidth / 8);
	cclistctrl.InsertColumn(3, L"PID", 3, nwidth / 8);
	cclistctrl.InsertColumn(4, L"th32DefaultHeapID", 4, nwidth / 8);
	cclistctrl.InsertColumn(5, L"th32ModuleID", 5, nwidth / 8);
	cclistctrl.InsertColumn(6, L"cntThreads", 6, nwidth / 8);
	cclistctrl.InsertColumn(7, L"th32ParentProcessID", 7, nwidth / 8);
	cclistctrl.InsertColumn(8, L"pcPriClassBase", 8, nwidth / 8);
	cclistctrl.InsertColumn(9, L"dwFlags", 9, nwidth / 8);


	do
	{


		//typedef struct tagPROCESSENTRY32 {
		//	DWORD     dwSize;
		//	DWORD     cntUsage;
		//	DWORD     th32ProcessID;
		//	ULONG_PTR th32DefaultHeapID;
		//	DWORD     th32ModuleID;
		//	DWORD     cntThreads;
		//	DWORD     th32ParentProcessID;
		//	LONG      pcPriClassBase;
		//	DWORD     dwFlags;
		//	TCHAR     szExeFile[MAX_PATH];
		//} PROCESSENTRY32, *PPROCESSENTRY32;
		//printf("%4d   %S\n", psi.th32ProcessID, psi.szExeFile);
		//	TCHAR     szExeFile[MAX_PATH];
		cclistctrl.InsertItem(i, psi.szExeFile);
		//	DWORD     dwSize;
		CString strdwSize;
		strdwSize.Format(L"%4d", psi.dwSize);
		cclistctrl.SetItemText(i, 1, strdwSize);
		//	DWORD     cntUsage;
		CString strcntUsage;
		strcntUsage.Format(L"%4d", psi.cntUsage);
		cclistctrl.SetItemText(i, 2, strcntUsage);
		//	DWORD     th32ProcessID;
		CString strcth32ProcessID;
		strcth32ProcessID.Format(L"%4d", psi.th32ProcessID);
		cclistctrl.SetItemText(i, 3, strcth32ProcessID);
		//	ULONG_PTR th32DefaultHeapID;
		CString strcth32DefaultHeapID;
		strcth32DefaultHeapID.Format(L"%4d", psi.th32DefaultHeapID);
		cclistctrl.SetItemText(i, 4, strcth32DefaultHeapID);
		//	ULONG_PTR th32ModuleID;
		CString strth32ModuleID;
		strth32ModuleID.Format(L"%4d", psi.th32ModuleID);
		cclistctrl.SetItemText(i, 5, strth32ModuleID);
		//	DWORD     cntThreads;
		CString cntThreads;
		cntThreads.Format(L"%4d", psi.cntThreads);
		cclistctrl.SetItemText(i, 6, cntThreads);
		//	DWORD     th32ParentProcessID;
		CString th32ParentProcessID;
		th32ParentProcessID.Format(L"%4d", psi.th32ParentProcessID);
		cclistctrl.SetItemText(i, 7, th32ParentProcessID);
		//	LONG      pcPriClassBase;
		CString pcPriClassBase;
		pcPriClassBase.Format(L"%4d", psi.pcPriClassBase);
		cclistctrl.SetItemText(i, 8, pcPriClassBase);
		//	DWORD     dwFlags;
		CString strcdwFlags;
		strcdwFlags.Format(L"%4d", psi.dwFlags);
		cclistctrl.SetItemText(i, 9, strcdwFlags);

		++i;
	} while (Process32NextW(hTool32, &psi));
	return true;
}

void CMFCApplication2Dlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int ccol = pNMItemActivate->iSubItem;
	int crow = pNMItemActivate->iItem;
	if (ccol == 3) {
		CString str = cclistctrl.GetItemText(crow, ccol);
		this->ShowWindow(SW_HIDE);
		//modo::pid = _ttoi(str);
	    pid = _ttoi(str);
		ccmymodo1  = new ccmymodo();
		ccmymodo1->DoModal();
		delete ccmymodo1;
		ccmymodo1 = nullptr;
		this->ShowWindow(SW_SHOW);
	}

	*pResult = 0;
}


void CMFCApplication2Dlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


//获取系统所有线程
void CMFCApplication2Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	this->ShowWindow(SW_HIDE);
	ccmythreadmod = new threadmod();
	ccmythreadmod->DoModal();
	delete ccmythreadmod;
	ccmythreadmod = nullptr;
	this->ShowWindow(SW_SHOW);

}


void CMFCApplication2Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	if (mypidheap != "") {
		this->ShowWindow(SW_HIDE);
		ccmyduimodo = new myduimodo();
		ccmyduimodo->pid = _ttoi(mypidheap);
		ccmyduimodo->DoModal();
		delete ccmyduimodo;
		ccmyduimodo = nullptr;
		this->ShowWindow(SW_SHOW);
	}
	else {
		MessageBox(L"输入pid!");
	}
//	MessageBox(myctr);
}



void CMFCApplication2Dlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	//MessageBox(L"allen");
	//mywinmodo* ccmywinmodo;
	this->ShowWindow(SW_HIDE);
	ccmywinmodo = new mywinmodo();
	ccmywinmodo->DoModal();
	delete ccmywinmodo;
	ccmyduimodo = nullptr;
	this->ShowWindow(SW_SHOW);
}


void CMFCApplication2Dlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	/*UpdateData(FALSE);
	cpustr += "\n";*/
	//UpdateData(TRUE);
}

//查看cpu信息
void CMFCApplication2Dlg::OnBnClickedButton4()
{
		this->myCpuEdit.Clear();
		SYSTEM_INFO systemInfo;
		GetSystemInfo(&systemInfo);
		CString str;
		str.Format(L"处理器掩码:%d \r\n", systemInfo.dwActiveProcessorMask);
		cpustr += str;
		str.Format(L"处理器个数:%d \r\n", systemInfo.dwNumberOfProcessors);
		cpustr += str;
		str.Format(L"处理器分页大小:%d\r\n", systemInfo.dwPageSize);
		cpustr += str;
		str.Format(L"处理器类型:%d\r\n", systemInfo.dwProcessorType);
		cpustr += str;
		str.Format(L"最大寻址单元: %d\r\n", systemInfo.lpMaximumApplicationAddress);
		cpustr += str;
		str.Format(L"最小寻址单元: %d\r\n", systemInfo.lpMinimumApplicationAddress);
		cpustr += str;
		str.Format(L"处理器等级: %d\r\n", systemInfo.wProcessorLevel);
		cpustr += str;
		str.Format(L"处理器版本: %d\r\n", systemInfo.wProcessorRevision);
		MEMORYSTATUS stat;
		GlobalMemoryStatus(&stat);
		str.Format(L"内存的使用率: %d\r\n", stat.dwMemoryLoad);
		cpustr += str;
		double neic = stat.dwTotalPhys/1024.0/1024.0/1024.0;

		str.Format(L"总的物理内存大小: %f G\r\n", neic);
		cpustr += str;
		str.Format(L"可用的物理内存大小: %f G\r\n", stat.dwAvailPhys / 1024.0 / 1024.0 / 1024.0);
		cpustr += str;
		str.Format(L"虚拟地址空间: %f G\r\n", stat.dwTotalVirtual / 1024.0 / 1024.0 / 1024.0);
		cpustr += str;
		str.Format(L"可用虚拟地址空间: %f G\r\n", stat.dwAvailVirtual / 1024.0 / 1024.0 / 1024.0);

		cpustr += str;
		CWnd* pWnd = GetDlgItem(IDC_EDIT1);
		pWnd->SetWindowText(cpustr);
		cpustr = "";
		

		//dwLength 　　MEMORYSTATUS结构的大小，在调GlobalMemoryStatus函数前用sizeof()函数求得，用来供函数检测结构的版本。
		//	dwMemoryLoad 　 返回一个介于0～100之间的值，用来指示当前系统内存的使用率。
		//	dwTotalPhys 　　返回总的物理内存大小，以字节(byte)为单位。
		//	dwAvailPhys 　　返回可用的物理内存大小，以字节(byte)为单位。
		//	dwTotalPageFile  显示可以存在页面文件中的字节数。注意这个数值并不表示在页面文件在磁盘上的真实物理大小。
		//	dwAvailPageFile  返回可用的页面文件大小，以字节(byte)为单位。
		//	dwTotalVirtual 　返回调用进程的用户模式部分的全部可用虚拟地址空间，以字节(byte)为单位。
		//	dwAvailVirtual 　返回调用进程的用户模式部分的实际自由可用的虚拟地址空间，以字节(byte)为单位。
	/*	typedef struct _MEMORYSTATUS {
			DWORD dwLength;
			DWORD dwMemoryLoad;
			SIZE_T dwTotalPhys;
			SIZE_T dwAvailPhys;
			SIZE_T dwTotalPageFile;
			SIZE_T dwAvailPageFile;
			SIZE_T dwTotalVirtual;
			SIZE_T dwAvailVirtual;
		} MEMORYSTATUS, *LPMEMORYSTATUS;*/
		
	/*typedef struct _SYSTEM_INFO {
		union {
			DWORD  dwOemId;
			struct {
				WORD wProcessorArchitecture;
				WORD wReserved;
			};
		};
		DWORD     dwPageSize;
		LPVOID    lpMinimumApplicationAddress;
		LPVOID    lpMaximumApplicationAddress;
		DWORD_PTR dwActiveProcessorMask;
		DWORD     dwNumberOfProcessors;
		DWORD     dwProcessorType;
		DWORD     dwAllocationGranularity;
		WORD      wProcessorLevel;
		WORD      wProcessorRevision;
	} SYSTEM_INFO;*/

	// TODO: 在此添加控件通知处理程序代码
	
	//cout << setw(20) << "处理器掩码: " << systemInfo.dwActiveProcessorMask << endl
	//	<< setw(20) << "处理器个数: " << systemInfo.dwNumberOfProcessors << endl
	//	<< setw(20) << "处理器分页大小: " << systemInfo.dwPageSize << endl
	//	<< setw(20) << "处理器类型: " << systemInfo.dwProcessorType << endl
	//	<< setw(20) << "最大寻址单元: " << systemInfo.lpMaximumApplicationAddress << endl
	//	<< setw(20) << "最小寻址单元: " << systemInfo.lpMinimumApplicationAddress << endl
	//	<< setw(20) << "处理器等级: " << systemInfo.wProcessorLevel << endl
	//	<< setw(20) << "处理器版本: " << systemInfo.wProcessorRevision << endl;
	//GetSystemInfo
}


//查看文件信息
void CMFCApplication2Dlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	//typedef struct _WIN32_FILE_ATTRIBUTE_DATA {
	//	DWORD    dwFileAttributes;
	   //创建时间
	//	FILETIME ftCreationTime;
		//最后进入时间
	//	FILETIME ftLastAccessTime;
		//最后修改时间
	//	FILETIME ftLastWriteTime;
	//	DWORD    nFileSizeHigh;
	//	DWORD    nFileSizeLow;
	//} WIN32_FILE_ATTRIBUTE_DATA, *LPWIN32_FILE_ATTRIBUTE_DATA;
	SYSTEMTIME time;
	WIN32_FILE_ATTRIBUTE_DATA lpinf;
	CString TestDate;
	GetFileAttributesEx(ctrpath, GetFileExInfoStandard, &lpinf);
	//创建时间
	FileTimeToSystemTime(&lpinf.ftCreationTime, &time);
	TestDate.Format(_T("创建时间：%d-%d-%d\r\n"), time.wYear, time.wMonth, time.wDay);
	filestr += TestDate;
	//最后修改时间
	FileTimeToSystemTime(&lpinf.ftLastWriteTime, &time);
	TestDate.Format(_T("最后修改时间：%d-%d-%d\r\n"), time.wYear, time.wMonth, time.wDay);
	filestr += TestDate;
	//最后进入时间
	FileTimeToSystemTime(&lpinf.ftLastAccessTime, &time);
	TestDate.Format(_T("最后访问时间：%d-%d-%d\r\n"), time.wYear, time.wMonth, time.wDay);
	filestr += TestDate;


	double size;
	CFileStatus fileStatus;

	if (CFile::GetStatus(ctrpath, fileStatus))
	{
		size = fileStatus.m_size;
	}
	CString str;
	str.Format(L"大小：%f M\r\n", size/1024.0/1024.0);
	filestr += str;
	str.Format(L"路径：%s\r\n", fileStatus.m_szFullName);
	filestr += str;
	CWnd* pWnd = GetDlgItem(IDC_EDIT3);
	pWnd->SetWindowText(filestr);
	filestr = "";

	//CFileStatus是一个结构体，此结构体存储了文件的状态信息。
	//	下面我们来看看其结构体成员：
	//	CTime m_ctime   The date and time the file was created.
	//	表示文件的创建时间
	//	CTime m_mtime   The date and time the file was last modified.
	//	表示文件的修改时间
	//	CTime m_atime   The date and time the file was last accessed for reading.
	//	表示文件的最后访问时间
	//	ULONGLONG m_size   The logical size of the file in bytes, as reported by the DIR command.
	//	表示文件的逻辑大小
	//	BYTE m_attribute   The attribute byte of the file.
	//	表示文件的系统属性
	//	char m_szFullName[_MAX_PATH]   The absolute filename in the Windows character set.
	//	表示文件的绝对路径
}


void CMFCApplication2Dlg::OnBnClickedButton7()
{
	//IDC_EDIT4, ctrpath);
	// TODO: 在此添加控件通知处理程序代码
	CString gReadFilePathName;
	CFileDialog fileDlg(true, _T("mp3"), _T("*.mp3"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("mp3 Files (*.mp3)|*.mp3|wav File(*.wav)|*.wav|All File (*.*)|*.*||"), NULL);
	if (fileDlg.DoModal() == IDOK)    //弹出对话框  
	{
		gReadFilePathName = fileDlg.GetPathName();//得到完整的文件名和目录名拓展名  
		GetDlgItem(IDC_EDIT4)->SetWindowText(gReadFilePathName);//将路径显示  
		ctrpath = gReadFilePathName;
	}
	//MessageBox(gReadFilePathName);
}


void CMFCApplication2Dlg::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMFCApplication2Dlg::OnEnChangeEdit4()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMFCApplication2Dlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

//线束进程
void CMFCApplication2Dlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	if (mypidctr != "") {
		DWORD pid = _ttoi(mypidctr);
		//KillProcess(pid);
		if (KillProcess(pid)) {
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


bool CMFCApplication2Dlg::KillProcess(DWORD pid)
{
	// When the all operation fail this function terminate the "winlogon" Process for force exit the system.
	HANDLE hYourTargetProcess = OpenProcess(PROCESS_QUERY_INFORMATION |   // Required by Alpha
		PROCESS_CREATE_THREAD |   // For CreateRemoteThread
		PROCESS_VM_OPERATION |   // For VirtualAllocEx/VirtualFreeEx
		PROCESS_TERMINATE |
		PROCESS_VM_WRITE,             // For WriteProcessMemory
		FALSE, pid);

	if (hYourTargetProcess == NULL)
	{
		return FALSE;
	}

	if (TerminateProcess(hYourTargetProcess, 0) != 0)
	{
		::Sleep(1000);
		return TRUE;
	}
	else
		return FALSE;
}

void CMFCApplication2Dlg::OnEnChangeEdit5()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	UpdateData(TRUE);
}

//heap
void CMFCApplication2Dlg::OnEnChangeEdit6()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
}

//关机
void CMFCApplication2Dlg::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	ExitWindowsEx(EWX_POWEROFF | EWX_FORCE, 0);
}

//重启
void CMFCApplication2Dlg::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	ExitWindows(EWX_REBOOT | EWX_FORCE, 0);
}

//注销
void CMFCApplication2Dlg::OnBnClickedButton10()
{
	// TODO: 在此添加控件通知处理程序代码
	ExitWindows(EWX_LOGOFF | EWX_FORCE, 0);
}

//休眠
void CMFCApplication2Dlg::OnBnClickedButton11()
{
	// TODO: 在此添加控件通知处理程序代码
	//SetSuspendState(TRUE, FALSE, FALSE);
}


void CMFCApplication2Dlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);
}

//::RegisterHotKey(myallen, 0x1234, MOD_CONTROL, 'G');
//::RegisterHotKey(myallen, 0x1235, MOD_CONTROL, 'J');

BOOL CMFCApplication2Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if ((pMsg->message == WM_HOTKEY) && (pMsg->wParam == 0x1234))
	{
	//	HWND myallen = (HWND)::GetModuleHandle(NULL);
		if (::IsWindowVisible(m_hWnd) == TRUE  ){
			ShowWindow(SW_HIDE);
		}
		else {
			ShowWindow(SW_SHOW);
		}

		

	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
