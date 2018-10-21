#include "infoWindow.h"

#include <QHBoxLayout>
#include <QTextStream>
#include <QLabel>

infoWindow::infoWindow(QWidget *parent) :
    QWidget(parent)
{
    m_processNum = 0;
    m_cpuUse = 0;
    m_memoryUse = 0;
    m_processLabel = new QLabel("进程数: 0");
    m_cpuLabel = new QLabel("CPU使用率: 0%");
    m_memoryLabel = new QLabel("内存使用率: 0%");

    QHBoxLayout *vlout = new QHBoxLayout;
    vlout->addWidget(m_processLabel,0,Qt::AlignLeft | Qt::AlignJustify);
    vlout->addWidget(m_cpuLabel,0, Qt::AlignLeft | Qt::AlignJustify);
    vlout->addWidget(m_memoryLabel,0, Qt::AlignLeft |  Qt::AlignJustify);
    vlout->addStretch();
    vlout->setContentsMargins(0,10,0,5);
    vlout->setSpacing(80);
    setLayout(vlout);
}

void infoWindow::setProcess(int processnum)
{
    m_processNum = processnum;
}

void infoWindow::setCpuuse(double cpuuse)
{
    m_cpuUse = cpuuse;
}

void infoWindow::setMemoryuse(double memoryuse)
{
    m_memoryUse = memoryuse;
}

QString str1 = "进程数: ";
QString str2 = "CPU使用率: ";
QString str3 = "内存使用率: ";

void infoWindow::infoChanged()
{
    QString prostr;
    QTextStream(&prostr) << str1 << m_processNum;
    int cpupercent = m_cpuUse * 100;
    int memorypercent = m_memoryUse * 100;
    QString cpustr;
    QTextStream(&cpustr) << str2 << cpupercent << "%";
    QString memorystr;
    QTextStream(&memorystr) << str3 <<memorypercent << "%";
    m_processLabel->setText(prostr);
    m_cpuLabel->setText(cpustr);
    m_memoryLabel->setText(memorystr);
}
