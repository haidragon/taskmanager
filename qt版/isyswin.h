#ifndef ISYSWIN_H
#define ISYSWIN_H

#include "ISysInfo.h"
#include <winternl.h>

class ISysWin: public ISysInfo
{
public:
    ISysWin(void);
    virtual ~ISysWin(void);
    bool GetSysCpu(int& nCpuRate) ;
    bool GetSysMemory(int& nMemTotal,int& nMemUsed);
    bool GetSysDisk(int& nDiskTotal,int& nDiskUsed) ;
    QMap<int,QString> GetAllProcess() ;
    bool GetProcessMemory(int nPid,int& nProcessMemRate) ;

protected:
    //时间转换
    __int64 Filetime2Int64(const FILETIME* ftime);
    //两个时间相减运算
    __int64 CompareFileTime(FILETIME preTime,FILETIME nowTime);
};

#endif // ISYSWIN_H
