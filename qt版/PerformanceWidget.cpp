#include "PerformanceWidget.h"

#include <QVBoxLayout>
#include <LineChartDialog.h>
#include <QLabel>
#include <QGridLayout>

PerformanceWidget::PerformanceWidget(QWidget *parent)
    : QWidget(parent)
{
    m_cpuLabel = new QLabel;
    m_cpuLabel->setWordWrap(true);
    m_cpuLabel->setAlignment(Qt::AlignTop);
    QString cpustr = "CPU使用记录";
    m_cpuLabel->setText(cpustr.split("", QString::SkipEmptyParts).join("\n"));

    m_memoryLabel = new QLabel;
    m_memoryLabel->setWordWrap(true);
    m_memoryLabel->setAlignment(Qt::AlignTop);
    QString memorystr = "内存使用记录";
    m_memoryLabel->setText(memorystr.split("", QString::SkipEmptyParts).join("\n"));

    m_cpuDial = new LineChartDialog;
    m_memoryDial = new LineChartDialog;

    QGridLayout *mainGridLayout = new QGridLayout;
    mainGridLayout->addWidget(m_cpuLabel, 0, 0, 1, 1, Qt::AlignCenter | Qt::AlignRight);
    mainGridLayout->addWidget(m_cpuDial, 0, 1, 1, 3);
    mainGridLayout->addWidget(m_memoryLabel, 1, 0, 1, 1, Qt::AlignCenter | Qt::AlignRight);
    mainGridLayout->addWidget(m_memoryDial, 1, 1, 1, 3);
    mainGridLayout->setSpacing(50);

    setLayout(mainGridLayout);
}

void PerformanceWidget::setCpuData(double cpuData)
{
    m_cpuDial->setCurrentData(cpuData);
}

void PerformanceWidget::setMemoryData(double memoryData)
{
    m_memoryDial->setCurrentData(memoryData);
}

void PerformanceWidget::updateDial()
{
    m_cpuDial->update();
    m_memoryDial->update();
}
