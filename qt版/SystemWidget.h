#ifndef SYSTEMWIDGET_H
#define SYSTEMWIDGET_H

#include <QWidget>

class QLabel;
class QGroupBox;

class SystemWidget : public QWidget
{
    Q_OBJECT
public:
     SystemWidget(QWidget *parent = 0);

private:
    QLabel *m_nameLabel;
    QLabel *m_cpuLabel;
    QLabel *m_memoryLabel;
    QLabel *m_typeLabel;
    QLabel *m_osLabel;
    QGroupBox *m_systemGroup;
};

#endif // WIDGET4_H
