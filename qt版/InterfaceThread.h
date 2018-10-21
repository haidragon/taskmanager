#ifndef INTERFACETHREAD_H
#define INTERFACETHREAD_H

#include <QThread>

class ISysInfo;
class QMutex;
class QAbstractItemModel;

class InterfaceThread : public QThread
{
    Q_OBJECT
public:
    InterfaceThread(QObject *parent = 0);
    void run();
    int getCpu();
    int getMemoryTotal();
    int getMemoryUsed();
    int getProcessNum();
    QAbstractItemModel *m_serviceModel;
    QAbstractItemModel *m_processModel;
    QAbstractItemModel *createProcessModel();
    QAbstractItemModel *createServiceModel();
    void addService(QAbstractItemModel *model, const QString &ServiceName,const QString &State, const QString &Dependencies);
    void addProcess(QAbstractItemModel *model, const QString &ProcessName,
                    const int &PID, const int &Cpu, const double &Memory, const QString &Description);

signals:
    void ReadyToUpdate();

private slots:

private:
    QMutex *m_lock;
    int m_Cpu;
    int m_MemoryTotal;
    int m_MemoryUsed;
    int m_ProcessNum;
    ISysInfo* m_systemInfo;


};

QAbstractItemModel *createServiceModel();
void test();





#endif // INTERFACETHREAD_H
