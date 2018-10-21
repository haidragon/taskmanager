#ifndef PROCESSWIDGET_H
#define PROCESSWIDGET_H

#include <QWidget>

class QAbstractItemModel;
class QSortFilterProxyModel;
class QGroupBox;
class QTreeView;
class QPushButton;

class ProcessWidget :public QWidget
{
    Q_OBJECT
public:
    ProcessWidget(QWidget *parent = 0);

    void setSourceModel(QAbstractItemModel *model);
    int GetProcessNum();

private slots:
    void updateModel();
    void killProcess();

private:
    QSortFilterProxyModel *m_proxyModel;
    QGroupBox *m_proxyGroupBox;
    QTreeView *m_proxyView;
    QPushButton *m_killButton;
};

#endif // PROCESSWIDGET_H
