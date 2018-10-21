#ifndef INFOWINDOW_H
#define INFOWINDOW_H

#include <QWidget>

class QLabel;

class infoWindow : public QWidget
{
    Q_OBJECT

public:
    explicit infoWindow(QWidget *parent = 0);
    void setProcess(int processnum);
    void setCpuuse(double cpuuse);
    void setMemoryuse(double memoryuse);

private slots:
    void infoChanged();

private:
    QLabel *m_processLabel;
    QLabel *m_cpuLabel;
    QLabel *m_memoryLabel;
    int m_processNum;
    double m_cpuUse;
    double m_memoryUse;
};

#endif // INFO_H
