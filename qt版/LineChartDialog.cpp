#include "LineChartDialog.h"

#include <QPixmap>
#include <QPainter>
#include <QPen>
#include <QColor>
#include <QTime>
#include <QDebug>

LineChartDialog::LineChartDialog(QWidget *parent):QDialog(parent)
{
    this->resize(470,320);

    m_Len = 0;
    m_Base=10;
    m_columnInc=0;

    m_Pixmap=QPixmap(width()-m_Base*2,height()-m_Base*2);
    m_Pixmap.fill(Qt::black);
}

LineChartDialog::~LineChartDialog()
{

}

void LineChartDialog::setCurrentData(double currentData)
{
    m_currentData = currentData;
}

void LineChartDialog::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);

    QPen pen(QColor(46, 139, 87),1.0);
    painter.setPen(pen);
    painter.drawPixmap(10,10,m_Pixmap);

    int graphW=m_Pixmap.width();
    int graphH=m_Pixmap.height();

    int graphRow=graphH/10;
    for (int i = m_Base; i <= graphH+m_Base; i += graphRow) {
        painter.drawLine(m_Base,i,m_Base+graphW,i);
    }

    int graphColumn=graphW/15;
    if(m_columnInc==0)
    {
        m_columnInc=graphColumn;
    }

    for(int j=m_Base+m_columnInc;j<graphW+m_Base;j+=graphColumn)
    {
        painter.drawLine(j,m_Base,j,m_Base+graphH);
    }

    m_columnInc -= 10;

    if(m_Len == 0)
    {
        m_Len=graphW/10;
        m_ptNum=0;
    }else
    {
        painter.setPen(QPen(Qt::yellow,2.0));
        m_dataVec.push_back(graphH - graphH * m_currentData - graphRow + m_Base);

        for(int j = m_Base + graphW- m_ptNum * 10, k = 0; k < m_ptNum; k++,j+=10)
        {
            if(k!=0)
            {

                    painter.drawLine(j-10,m_dataVec[k-1],j,m_dataVec[k]);

            }
        }
        if(m_ptNum == m_Len)
        {
            m_dataVec.pop_front();
        }else
        {
            m_ptNum++;
        }
    }
}

