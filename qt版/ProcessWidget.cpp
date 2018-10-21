#include "ProcessWidget.h"

#include <QDebug>
#include <QString>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTreeView>
#include <QGroupBox>
#include <QPushButton>
#include <QSortFilterProxyModel>

ProcessWidget::ProcessWidget(QWidget *parent)
    : QWidget(parent)
{
    resize(700,350);
    m_proxyModel = new QSortFilterProxyModel;
    m_proxyView = new QTreeView;
    m_proxyView->setRootIsDecorated(false);
    m_proxyView->setAlternatingRowColors(true);
    m_proxyView->setModel(m_proxyModel);
    m_proxyView->setSortingEnabled(true);
    m_proxyGroupBox = new QGroupBox(tr("进程信息"));

    QHBoxLayout *proxyLayout = new QHBoxLayout;
    proxyLayout->addWidget(m_proxyView);
    m_proxyGroupBox->setLayout(proxyLayout);

    m_killButton = new QPushButton("结束进程");

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_proxyGroupBox);
    mainLayout->addWidget(m_killButton, 0, Qt::AlignRight |  Qt::AlignJustify);

    connect(m_killButton,SIGNAL(clicked()),this,SLOT(killProcess()));
    setLayout(mainLayout);
    m_proxyView->sortByColumn(1, Qt::AscendingOrder);
}

void ProcessWidget::setSourceModel(QAbstractItemModel *model)
{
    QAbstractItemModel *oldmodel = m_proxyModel->sourceModel();
    m_proxyModel->setSourceModel(model);
    if(oldmodel)
        oldmodel->destroyed();
}

void ProcessWidget::updateModel()
{

}

void ProcessWidget::killProcess()
{
    int curRow = m_proxyView->currentIndex().row();
    QModelIndex indextemp = m_proxyView->model()->index(curRow, 1);
    QVariant datatemp = m_proxyView->model()->data(indextemp);
    int PID = datatemp.toInt();
    qDebug() << "ready to kill PID " << PID;
}

int ProcessWidget::GetProcessNum()
{
    return m_proxyModel->rowCount();
}

