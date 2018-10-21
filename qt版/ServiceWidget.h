#ifndef SERVICEWIDGET_H
#define SERVICEWIDGET_H

#include <QWidget>

class QSortFilterProxyModel;
class QAbstractItemModel;
class QGroupBox;
class QTreeView ;
class QPushButton;

class ServiceWidget :public QWidget
{
    Q_OBJECT
public:
   ServiceWidget(QWidget *parent = 0);
   void setSourceModel(QAbstractItemModel *model);

private slots:
   void updateModel();
   void openService();

private:
   QSortFilterProxyModel *m_proxyModel;
   QGroupBox *m_proxyGroupBox;
   QTreeView *m_proxyView;
   QPushButton *m_serviceButton;
};

#endif // WIDGET2_H
