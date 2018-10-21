#include "InterfaceThread.h"

#include <windows.h>
#include <TlHelp32.h>
#include <Psapi.h>
#include <tchar.h>
#include "isyswin.h"
#include "ISysInfo.h"
#include <QThread>
#include <QMutex>
#include <QDebug>
#include <QStandardItemModel>
#include <QString>

InterfaceThread::InterfaceThread(QObject *parent)
    :QThread(parent)
{
    m_lock = new QMutex;
    m_Cpu = 0;
    m_MemoryTotal = 0;
    m_MemoryUsed = 0;
    m_ProcessNum = 0;
    m_systemInfo = new ISysWin();
    m_serviceModel = createServiceModel();
    m_processModel = createProcessModel();
}

void InterfaceThread::run()
{
    int cpu,memorytotal,memoryused;
    while(1) {
        m_systemInfo->GetSysCpu(cpu);
        m_systemInfo->GetSysMemory(memorytotal,memoryused);
        m_lock->lock();
        m_Cpu = cpu;
        m_MemoryTotal = memorytotal;
        m_MemoryUsed = memoryused;
        m_serviceModel = createServiceModel();
        m_processModel = createProcessModel();
        m_lock->unlock();
        emit ReadyToUpdate();
        sleep(1);
    }
}

int InterfaceThread::getCpu()
{
    return m_Cpu;
}

int InterfaceThread::getMemoryTotal()
{
    return m_MemoryTotal;
}

int InterfaceThread::getMemoryUsed()
{
    return m_MemoryUsed;
}

int InterfaceThread::getProcessNum()
{
    return m_ProcessNum;
}

void InterfaceThread::addService(QAbstractItemModel *model, const QString &ServiceName,const QString &State, const QString &Dependencies)
{
    model->insertRow(0);
    model->setData(model->index(0, 0), ServiceName);
    model->setData(model->index(0, 1), State);
    model->setData(model->index(0, 2), Dependencies);
}

QAbstractItemModel* InterfaceThread::createServiceModel()
{
    QStandardItemModel *model = new QStandardItemModel(0, 3);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("服务名"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("状态"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("工作组"));
    int menu = 1;
        while (1)
        {
            if(menu == 1)
            {
                SC_HANDLE SCMan = OpenSCManager(0, 0, SC_MANAGER_CONNECT | SC_MANAGER_ENUMERATE_SERVICE); //打开系统服务控制器
                if(SCMan == NULL)
                {
                    qDebug() << "OpenSCManager Eorror";
                    return NULL;
                }
                LPENUM_SERVICE_STATUS service_status; //保存系统服务的结构
                DWORD cbBytesNeeded = NULL;
                DWORD ServicesReturned = NULL;
                DWORD ResumeHandle = NULL;

                service_status = (LPENUM_SERVICE_STATUS)LocalAlloc(LPTR, 1024 * 64);//分配内存，注意大小
                //获取系统服务的简单信息
                bool ESS = EnumServicesStatus(SCMan, //系统服务句柄
                    SERVICE_WIN32, //服务的类型
                    SERVICE_STATE_ALL,  //服务的状态
                    (LPENUM_SERVICE_STATUS)service_status,  //输出参数，系统服务的结构
                    1024 * 64,  // 结构的大小
                    &cbBytesNeeded, //输出参数，接收返回所需的服务
                    &ServicesReturned, //输出参数，接收返回服务的数量
                    &ResumeHandle); //输入输出参数，第一次调用必须为0，返回为0代表成功
                if(ESS == NULL)
                {
                    qDebug() << "EnumServicesStatus Eorror/n";
                    return NULL;
                }
                for(int i = 0; i < ServicesReturned; i++)
                {
                    QString strService = (QString::fromUtf16(reinterpret_cast<const unsigned short *>(service_status[i].lpDisplayName)));
                    QString strState;
                    switch(service_status[i].ServiceStatus.dwCurrentState)// 服务状态
                    {
                    case SERVICE_CONTINUE_PENDING:
                        strState = "挂起";
                        break;
                    case SERVICE_PAUSE_PENDING:
                        strState = "正在暂停";
                        break;
                    case SERVICE_PAUSED:
                        strState = "已经暂停";
                        break;
                    case SERVICE_RUNNING:
                        strState = "正在运行";
                        break;
                    case SERVICE_START_PENDING:
                        strState = "启动";
                        break;
                    case SERVICE_STOPPED:
                        strState = "已经停止";
                        break;
                    default:
                        strState = "未知";
                        break;
                    }
                    LPQUERY_SERVICE_CONFIG lpServiceConfig = NULL; //服务详细信息结构
                    SC_HANDLE service_curren = NULL; //当前的服务句柄
                    service_curren = OpenService(SCMan, service_status[i].lpServiceName, SERVICE_QUERY_CONFIG); //打开当前服务
                    lpServiceConfig = (LPQUERY_SERVICE_CONFIG)LocalAlloc(LPTR, 8 * 1024);      //分配内存， 最大为8kb

                    if(NULL == QueryServiceConfig(service_curren, lpServiceConfig, 8 * 1024, &ResumeHandle))
                    {
                        qDebug() << "QueryServiceConfig Error";
                        return NULL;
                    }
                    QString strDenpen = (QString::fromUtf16(reinterpret_cast<const unsigned short *>(lpServiceConfig->lpDependencies)));
                    addService(model, strService, strState, strDenpen);//添加进模型
                    CloseServiceHandle(service_curren);//关闭当前服务的句柄
                }
                CloseServiceHandle(SCMan);//关闭服务管理器的句柄
            }
            break;
        }
        return model;
}

void GetFileDescriptionAndProductVersionA(LPCSTR lpstrFilename, LPSTR lpoutFileDescription, UINT cbDescSize)
{
    typedef DWORD(WINAPI *pfnGetFileVersionInfoSizeA)(LPCSTR,LPDWORD);
    typedef BOOL(WINAPI *pfnGetFileVersionInfoA)(LPCSTR,DWORD,DWORD,LPVOID);
    typedef	BOOL(WINAPI	*pfnVerQueryValueA)(const LPVOID,LPCSTR,LPVOID*,PUINT);

    HMODULE hDll = 0;
    DWORD	dwHandle=0;
    DWORD	dwInfoSize=0;

    pfnGetFileVersionInfoSizeA	fnGetFileVersionInfoSizeA = 0;
    pfnGetFileVersionInfoA	fnGetFileVersionInfoA = 0;
    pfnVerQueryValueA	fnVerQueryValueA = 0;

    *lpoutFileDescription = 0;
    // Load system32\version.dll module
    hDll = LoadLibraryA("version.dll");

    if (!hDll) {
        return;
    }

    fnGetFileVersionInfoSizeA = (pfnGetFileVersionInfoSizeA) GetProcAddress(hDll, "GetFileVersionInfoSizeA");
    fnGetFileVersionInfoA = (pfnGetFileVersionInfoA) GetProcAddress(hDll, "GetFileVersionInfoA");
    fnVerQueryValueA = (pfnVerQueryValueA)GetProcAddress(hDll, "VerQueryValueA");

    // If failed  to get procdure address

    if (!fnGetFileVersionInfoSizeA || !fnGetFileVersionInfoA || !fnVerQueryValueA){
        FreeLibrary(hDll);
        return;
    }

    dwInfoSize = fnGetFileVersionInfoSizeA(lpstrFilename, &dwHandle);
    if (dwInfoSize > 0){
        void *pvInfo = malloc(dwInfoSize);
        if (!pvInfo)
            exit(-1);	// Out of memory
        if (fnGetFileVersionInfoA(lpstrFilename, 0, dwInfoSize, pvInfo)){
            struct LANGANDCODEPAGE {
                WORD wLanguage;
                WORD wCodePage; } *lpTranslate;

        // Read the list of languages and code pages.
            UINT cbTranslate = 0;
            if ( fnVerQueryValueA(pvInfo, "\\VarFileInfo\\Translation", (void**) &lpTranslate, &cbTranslate) ){
        // ONLY Read the file description for FIRST language and code page.
                if ((cbTranslate/sizeof(struct LANGANDCODEPAGE)) > 0){
                    const char *lpBuffer=0;
                    UINT cbSizeBuf = 0;
                    char szSubBlock[50];
                    wsprintfA(szSubBlock,"\\StringFileInfo\\%04x%04x\\FileDescription", lpTranslate[0].wLanguage, lpTranslate[0].wCodePage);
                    if ( fnVerQueryValueA(pvInfo, szSubBlock, (void**)&lpBuffer, &cbSizeBuf) ){
                        strncpy_s(lpoutFileDescription, cbDescSize, lpBuffer, cbDescSize-1); lpoutFileDescription[cbDescSize-1] = 0;
                    }
                }
            }
        }
        free(pvInfo);
    }
    FreeLibrary(hDll);
}

void InterfaceThread::addProcess(QAbstractItemModel *model, const QString &ProcessName,
             const int &PID, const int &Cpu, const double &Memory, const QString &Description)
{
    model->insertRow(0);
    model->setData(model->index(0, 0), ProcessName);
    model->setData(model->index(0, 1), PID);
    model->setData(model->index(0, 2), Cpu);
    model->setData(model->index(0, 3), Memory);
    model->setData(model->index(0, 4), Description);
}

BOOL EnablePrivilege(HANDLE hToken,LPCWSTR szPrivName)
{

    TOKEN_PRIVILEGES tkp;

    LookupPrivilegeValue( NULL,szPrivName,&tkp.Privileges[0].Luid );//修改进程权限
    tkp.PrivilegeCount=1;
    tkp.Privileges[0].Attributes=SE_PRIVILEGE_ENABLED;
    AdjustTokenPrivileges( hToken,FALSE,&tkp,sizeof tkp,NULL,NULL );//通知系统修改进程权限

    return( (GetLastError()==ERROR_SUCCESS) );

}

BOOL DosPathToNtPath(LPWSTR pszDosPath, LPWSTR pszNtPath)
{
    wchar_t            szDriveStr[500];
    wchar_t            szDrive[3];
    wchar_t            szDevName[100];
    INT                cchDevName;
    INT                i;

    //检查参数
    if(!pszDosPath || !pszNtPath )
        return FALSE;

    //获取本地磁盘字符串
    if(GetLogicalDriveStrings(sizeof(szDriveStr), szDriveStr))
    {
        for(i = 0; szDriveStr[i]; i += 4)
        {
            QString str1 = "A:\\";
            QString str2 = "B:\\";
            wchar_t wstr1[10];
            wchar_t wstr2[10];
            str1.toWCharArray(wstr1);
            str2.toWCharArray(wstr2);
            if(!lstrcmpi(&(szDriveStr[i]), wstr1) || !lstrcmpi(&(szDriveStr[i]), wstr2)) {
                continue;
            }
            szDrive[0] = szDriveStr[i];
            szDrive[1] = szDriveStr[i + 1];
            szDrive[2] = '\0';
            if(!QueryDosDevice(szDrive, szDevName, 100)) {//查询 Dos 设备名
                return FALSE;
            }
            cchDevName = lstrlen(szDevName);
            QString str3 = QString::fromStdWString(pszDosPath);
            QString str4 = QString::fromStdWString(szDevName);

            if(_tcsnicmp(str3.toLatin1(), str4.toLatin1(), cchDevName) == 0)//命中
            {
                lstrcpy(pszNtPath, szDrive);//复制驱动器
                lstrcat(pszNtPath, pszDosPath + cchDevName);//复制路径

                return TRUE;
            }
        }
    }

    lstrcpy(pszNtPath, pszDosPath);

    return FALSE;
}

QAbstractItemModel* InterfaceThread::createProcessModel()
{
    m_ProcessNum = 0;
    //提升程序权限
    HANDLE  hToken;
    OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES,&hToken);
    EnablePrivilege(hToken,SE_DEBUG_NAME);
    QStandardItemModel *model = new QStandardItemModel(0, 5);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("进程名"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("PID"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("CPU"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("内存(KB)"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("描述"));

    HANDLE hProcessSnap;    //进程快照的句柄
    HANDLE hProcess;    //用于获取进程的句柄
    PROCESSENTRY32 pe32;//进程信息的结构体
    // 获取系统进程信息的快照
    hProcessSnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
    if( hProcessSnap == INVALID_HANDLE_VALUE )
    {
        qDebug()<<"CreateToolhelp32Snapshot Failed!";// 打印错误信息
        if(NULL !=hProcessSnap)
        {
            CloseHandle( hProcessSnap );          // 关闭进程快照信息
            hProcessSnap = NULL;
        }
        return NULL;
    }
    // 在使用之前设置PROCESSENTRY32结构体的初始大小值,如果不初始化dwSize, Process32First 调用会失败.
    pe32.dwSize = sizeof( PROCESSENTRY32 );
    if( !Process32First( hProcessSnap, &pe32 ) )// 开始获取第一个进程的信息，如果获取失败就返回
    {
        qDebug()<<"Process32First Failed!"; // 打印错误信息
        if(NULL !=hProcessSnap)
        {
            CloseHandle( hProcessSnap );          // 关闭进程快照信息
            hProcessSnap = NULL;
        }
        return NULL;
    }
    //开始遍历所有进程
    do
    {
        m_ProcessNum++;
            QString strProcessName =(QString::fromUtf16(reinterpret_cast<const unsigned short *>(pe32.szExeFile)));
            int PID = (int)pe32.th32ProcessID;
            if(PID == 4)
                continue;
            //qDebug() << strProcessName << " " << PID ;
            wchar_t    fullpath[_MAX_PATH+1];
            wchar_t    path[_MAX_PATH+1];
            HANDLE h_Process=OpenProcess(PROCESS_QUERY_INFORMATION,0,pe32.th32ProcessID);
            //HANDLE h_Process=OpenProcess(PROCESS_ALL_ACCESS,0,pe32.th32ProcessID);

            if (!h_Process)
            {
                //qDebug() << "open process fail";
                continue;
            }
            PROCESS_MEMORY_COUNTERS pmc;//该线程的内存信息结构体
            if ( !GetProcessMemoryInfo( h_Process, &pmc, sizeof(pmc)) )
            {
                //qDebug()<<"GetProcessMemoryInfo Failed!";
                continue;
            }
            double processMemory = (double)pmc.WorkingSetSize / 1024;
            //qDebug() << processMemory;
            GetProcessImageFileName(h_Process, path,MAX_PATH+1);
            DosPathToNtPath(path, fullpath);
            //GetModuleFileNameEx(h_Process,NULL,path,MAX_PATH+1);
            QString strProcessPath =  (QString::fromUtf16(reinterpret_cast<const unsigned short *>(fullpath)));
            //QString strProcessPath(path);
            //qDebug() << strProcessPath;

            char  szFileDesc[128];
            GetFileDescriptionAndProductVersionA(strProcessPath.toLatin1().data(), szFileDesc, 128);
            QString descripStr = QString::fromLocal8Bit(szFileDesc);
            //qDebug() << descripStr;

            addProcess(model, strProcessName, PID, 0, processMemory, descripStr);
            //CloseHandle(hProcessShot);
        //当然还可以获取到很多其他信息，例如进程名字(szExeFile[MAX_PATH])、父进程PPID(th32ParentProcessID)。。。
        /* 附上该结构体信息
        typedef struct tagPROCESSENTRY32 {
        DWORD     dwSize;
        DWORD     cntUsage;
        DWORD     th32ProcessID;
        ULONG_PTR th32DefaultHeapID;
        DWORD     th32ModuleID;
        DWORD     cntThreads;
        DWORD     th32ParentProcessID;
        LONG      pcPriClassBase;
        DWORD     dwFlags;
        TCHAR     szExeFile[MAX_PATH];
        } PROCESSENTRY32, *PPROCESSENTRY32;
        */
    }
    while( Process32Next( hProcessSnap, &pe32 ) );// 获取下一个进程的信息
    if(NULL !=hProcessSnap)//最后关闭快照句柄
    {
        CloseHandle( hProcessSnap );
        hProcessSnap = NULL;
    }
    return model;
}
