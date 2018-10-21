#include "chooseHead.h"
#include "TaskManagerWindow.h"
#include <QHBoxLayout>
#include <QPushButton>

chooseHead::chooseHead(QWidget *parent) :
    QWidget(parent)
{
    m_processButton = new QPushButton("进程");
    m_serviceButton = new QPushButton("服务");
    m_performanceButton = new QPushButton("性能");
    m_systemButton = new QPushButton("系统");

    connect(m_processButton,SIGNAL(clicked()),this,SLOT(emit_Process()));
    connect(m_serviceButton,SIGNAL(clicked()),this,SLOT(emit_Service()));
    connect(m_performanceButton,SIGNAL(clicked()),this,SLOT(emit_Performance()));
    connect(m_systemButton,SIGNAL(clicked()),this,SLOT(emit_System()));

    QHBoxLayout *vlout = new QHBoxLayout;
    vlout->addWidget(m_processButton,0,Qt::AlignLeft | Qt::AlignJustify);
    vlout->addWidget(m_serviceButton,0, Qt::AlignLeft | Qt::AlignJustify);
    vlout->addWidget(m_performanceButton,0, Qt::AlignLeft |  Qt::AlignJustify);
    vlout->addWidget(m_systemButton,0, Qt::AlignLeft | Qt::AlignJustify);
    vlout->addStretch();
    vlout->setContentsMargins(0,0,0,0);
    vlout->setSpacing(0);
    setLayout(vlout);
}

void chooseHead::emit_Process()
{
    emit processPressed();
}

void chooseHead::emit_Service()
{
    emit servicePressed();
}

void chooseHead::emit_Performance()
{
    emit performancePressed();
}

void chooseHead::emit_System()
{
    emit systemPressed();
}



