#include "TaskManagerWindow.h"

#include "ProcessWidget.h"
#include "chooseHead.h"
#include "ServiceWidget.h"
#include "PerformanceWidget.h"
#include "SystemWidget.h"
#include "infoWindow.h"
#include "InterfaceThread.h"

#include <QAction>
#include <QFileDialog>
#include <QMenuBar>
#include <QPushButton>
#include <QStackedWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStandardItemModel>
#include <QDebug>



TaskManagerWindow::TaskManagerWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(800, 800);
    QWidget* cenwidget = new QWidget(this);

    createMenus();
    setWindowTitle(tr("任务管理器"));

    m_interfaceThread = new InterfaceThread;

    m_hd = new chooseHead;
    m_processWidget = new ProcessWidget;
    m_processWidget->setSourceModel(m_interfaceThread->m_processModel);
    m_serviceWidget = new ServiceWidget;
    m_serviceWidget->setSourceModel(m_interfaceThread->m_serviceModel);
    m_performanceWidget = new PerformanceWidget;
    m_systemWidget = new SystemWidget;

    m_stackWidget = new QStackedWidget;
    m_stackWidget->addWidget(m_processWidget);
    m_stackWidget->addWidget(m_serviceWidget);
    m_stackWidget->addWidget(m_performanceWidget);
    m_stackWidget->addWidget(m_systemWidget);
    m_stackWidget->setCurrentIndex(0);

    m_infoWindow = new infoWindow;

    QVBoxLayout *vlout = new QVBoxLayout;
    vlout->addWidget(m_hd);
    vlout->addWidget(m_stackWidget);
    vlout->addWidget(m_infoWindow);
    vlout->setSpacing(0);

    connect(m_hd,SIGNAL(processPressed()),this,SLOT(changed_process()));
    connect(m_hd,SIGNAL(servicePressed()),this,SLOT(changed_service()));
    connect(m_hd,SIGNAL(performancePressed()),this,SLOT(changed_performance()));
    connect(m_hd,SIGNAL(systemPressed()),this,SLOT(changed_system()));

    cenwidget->setLayout(vlout);
    setCentralWidget(cenwidget);

    connect(this, SIGNAL(timeChange()), m_infoWindow, SLOT(infoChanged()));
    connect(this, SIGNAL(timeChange()), m_performanceWidget, SLOT(updateDial()));

    m_interfaceThread->start();
    connect(m_interfaceThread, SIGNAL(ReadyToUpdate()), this, SLOT(timeUp()));
}

TaskManagerWindow::~TaskManagerWindow()
{

}

void TaskManagerWindow::createMenus()
{
    m_fileMenu = menuBar()->addMenu(tr("文件"));

    m_newAct = new QAction(tr("新建进程"), this);
    m_fileMenu->addAction(m_newAct);
    connect(m_newAct, &QAction::triggered, this, &TaskManagerWindow::newTask);

    m_exitAct = new QAction(tr("退出"), this);
    m_fileMenu->addAction(m_exitAct);
    connect(m_exitAct, &QAction::triggered, this, &QWidget::close);

    m_optionMenu = menuBar()->addMenu(tr("选项"));

    m_miniAct = new QAction(tr("使用时最小化"), this);
    m_optionMenu->addAction(m_miniAct);
    connect(m_miniAct, &QAction::triggered, this, &TaskManagerWindow::minInUsing);

    m_viewMenu = menuBar()->addMenu(tr("视图"));

    m_quickupAct = new QAction(tr("立即刷新"), this);
    m_viewMenu->addAction(m_quickupAct);
    connect(m_quickupAct, &QAction::triggered, this, &TaskManagerWindow::quickUpdate);

    m_helpMenu = menuBar()->addMenu(tr("帮助"));
    m_helpAct = new QAction(tr("帮助"), this);
    m_helpMenu->addAction(m_helpAct);
    connect(m_helpAct, &QAction::triggered, this, &TaskManagerWindow::Help);
}

void TaskManagerWindow::newTask()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty()) {
        if(fileName.contains("exe")) {
            qDebug() << fileName;
        }
        else {
            qDebug() << "File is not exe";
        }
    }
}

void TaskManagerWindow::minInUsing()
{

}

void TaskManagerWindow::quickUpdate()
{
    emit timeChange();
}

void TaskManagerWindow::Help()
{

}

void TaskManagerWindow::changed_process()
{
    m_stackWidget->setCurrentIndex(0);
}


void TaskManagerWindow::changed_service()
{
    m_stackWidget->setCurrentIndex(1);
}

void TaskManagerWindow::changed_performance()
{
    m_stackWidget->setCurrentIndex(2);
}

void TaskManagerWindow::changed_system()
{
    m_stackWidget->setCurrentIndex(3);
}

void TaskManagerWindow::timeUp()
{
    int process;
    int cpu = m_interfaceThread->getCpu();
    int memorytotal = m_interfaceThread->getMemoryTotal();
    int memoryused = m_interfaceThread->getMemoryUsed();
    process = m_interfaceThread->getProcessNum();
    double cpuuse = (double)cpu/100;
    double memoryuse = (double)memoryused/memorytotal;
    m_infoWindow->setProcess(process);
    m_infoWindow->setCpuuse(cpuuse);
    m_infoWindow->setMemoryuse(memoryuse);
    m_performanceWidget->setCpuData(cpuuse);
    m_performanceWidget->setMemoryData(memoryuse);
    m_processWidget->setSourceModel(m_interfaceThread->m_processModel);
    m_serviceWidget->setSourceModel(m_interfaceThread->m_serviceModel);
    emit timeChange();
}

