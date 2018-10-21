#ifndef PERFORMANCEWIDGET_H
#define PERFORMANCEWIDGET_H

#include <QWidget>

class LineChartDialog;
class QLabel;

class PerformanceWidget :public QWidget
{
    Q_OBJECT
public:
    PerformanceWidget(QWidget *parent = 0);
    void setCpuData(double cpuData);
    void setMemoryData(double memoryData);

private slots:
   void updateDial();

private:
    QLabel *m_cpuLabel;
    QLabel *m_memoryLabel;
    LineChartDialog *m_cpuDial;
    LineChartDialog *m_memoryDial;
};

#endif // PERFORMANCEWIDGET_H
