#ifndef CHOOSEHEAD_H
#define CHOOSEHEAD_H

#include <QWidget>

class QPushButton;

class chooseHead :public QWidget
{
    Q_OBJECT
public:
     chooseHead(QWidget *parent = 0);

private slots:
    void emit_Process();
    void emit_Service();
    void emit_Performance();
    void emit_System();

signals:
    void processPressed();
    void servicePressed();
    void performancePressed();
    void systemPressed();

private:
    QPushButton *m_processButton;
    QPushButton *m_serviceButton;
    QPushButton *m_performanceButton;
    QPushButton *m_systemButton;
};

#endif // CHOOSEHEAD_H
