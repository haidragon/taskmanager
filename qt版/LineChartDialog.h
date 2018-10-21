#ifndef LINECHARTDIALOG_H
#define LINECHARTDIALOG_H

#include <QDialog>
#include <QVector>

class LineChartDialog:public QDialog
{
    Q_OBJECT
public:
    LineChartDialog(QWidget *parent=0);
    ~LineChartDialog();
    void setCurrentData(double currentData);

protected:
    void paintEvent(QPaintEvent *);

private:
    QPixmap m_Pixmap;
    int m_Base;
    int m_columnInc;    // 动态列偏移值
    int m_Len;          // 记录数组长度
    int m_ptNum;        // 点数目
    QVector<int> m_dataVec;
    double m_currentData;
};

#endif // LINECHARTDIALOG_H
