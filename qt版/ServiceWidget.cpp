#include "ServiceWidget.h"

#include <windows.h>
#include <shellapi.h>
#include <QDebug>
#include <QString>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSortFilterProxyModel>
#include <QTreeView>
#include <QGroupBox>
#include <QPushButton>
#include <QProcess>

ServiceWidget::ServiceWidget(QWidget *parent)
    : QWidget(parent)
{
    resize(700,350);
    m_proxyModel = new QSortFilterProxyModel;

    m_proxyView = new QTreeView;
    m_proxyView->setRootIsDecorated(false);
    m_proxyView->setAlternatingRowColors(true);
    m_proxyView->setModel(m_proxyModel);
    m_proxyView->setSortingEnabled(true);

    m_proxyGroupBox = new QGroupBox(tr("服务信息"));

    QHBoxLayout *proxyLayout = new QHBoxLayout;
    proxyLayout->addWidget(m_proxyView);
    m_proxyGroupBox->setLayout(proxyLayout);

    m_serviceButton = new QPushButton("服务");
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_proxyGroupBox);
    mainLayout->addWidget(m_serviceButton, 0, Qt::AlignRight |  Qt::AlignJustify);

    connect(m_serviceButton,SIGNAL(clicked()),this,SLOT(openService()));

    setLayout(mainLayout);
    m_proxyView->sortByColumn(0, Qt::AscendingOrder);
}

void ServiceWidget::setSourceModel(QAbstractItemModel *model)
{
    QAbstractItemModel *oldmodel = m_proxyModel->sourceModel();
    m_proxyModel->setSourceModel(model);
    if(oldmodel)
        oldmodel->destroyed();
}

void ServiceWidget::updateModel()
{

}

void ServiceWidget::openService()
{
    QString str1 = "open";
    const wchar_t *wstr1 = reinterpret_cast<const wchar_t *>(str1.utf16());
    QString str2 = "services.msc";
    const wchar_t *wstr2 = reinterpret_cast<const wchar_t *>(str2.utf16());
    ShellExecute(NULL, wstr1, wstr2,NULL,NULL,SW_SHOWNORMAL);
}
