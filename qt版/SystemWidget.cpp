#include "SystemWidget.h"

#include <QLabel>
#include <QGroupBox>
#include <windows.h>
#include <qdebug.h>
#include <QVBoxLayout>
#include <QSysInfo>
#include <QSettings>

SystemWidget::SystemWidget(QWidget *parent)
    : QWidget(parent)
{
    QSettings *reg = new QSettings("HKEY_LOCAL_MACHINE\\HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", QSettings::NativeFormat);
    QString str1 = reg->value("ProcessorNameString").toString();
       qDebug() << str1;
    QString cpustr = "处理器： " + str1;

    double nMemTotal;
    MEMORYSTATUSEX memsStat;
    memsStat.dwLength = sizeof(memsStat);
    if (!GlobalMemoryStatusEx(&memsStat)) {
        nMemTotal = -1;
    } else {
        nMemTotal = memsStat.ullTotalPhys/( 1024.0*1024.0*1024.0);
    }
    qDebug() << nMemTotal;
    QString str2 = QString::number(nMemTotal,'f', 2);
    QString memorystr = "安装内存： " + str2 + "GB";

    QSysInfo *sysinfo = new QSysInfo;
    qDebug() << sysinfo->currentCpuArchitecture();
    qDebug() << sysinfo->machineHostName();
    qDebug() << sysinfo->prettyProductName();
    QString namestr = "计算机名： " + sysinfo->machineHostName();
    QString osstr = "操作系统： " + sysinfo->prettyProductName();
    QString typestr = "系统类型： " + sysinfo->currentCpuArchitecture();

    m_nameLabel = new QLabel(namestr);
    m_cpuLabel = new QLabel(cpustr);
    m_memoryLabel = new QLabel(memorystr);
    m_osLabel = new QLabel(osstr);
    m_typeLabel = new QLabel(typestr);

    m_systemGroup = new QGroupBox(tr("系统信息"));
    QVBoxLayout *sysLayout = new QVBoxLayout;
    sysLayout->addWidget(m_nameLabel);
    sysLayout->addWidget(m_cpuLabel);
    sysLayout->addWidget(m_memoryLabel);
    sysLayout->addWidget(m_osLabel);
    sysLayout->addWidget(m_typeLabel);
    sysLayout->setSpacing(50);
    m_systemGroup->setLayout(sysLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_systemGroup);
    mainLayout->addStretch();
    setLayout(mainLayout);
}
