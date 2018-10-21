#ifndef TASKMANAGERWINDOW_H
#define TASKMANAGERWINDOW_H

#include <QMainWindow>

class QAction;
class QMenu;
class QStackedWidget;
class ProcessWidget;
class ServiceWidget;
class PerformanceWidget;
class SystemWidget;
class chooseHead;
class infoWindow;
class InterfaceThread;

class TaskManagerWindow : public QMainWindow
{
    Q_OBJECT
public:
    TaskManagerWindow(QWidget *parent = 0);
    ~TaskManagerWindow();

signals:
    void timeChange();

private slots:
    void newTask();
    void minInUsing();
    void quickUpdate();
    void Help();
    void timeUp();

private:
    void createMenus();
    QMenu *m_fileMenu;
    QMenu *m_optionMenu;
    QMenu *m_viewMenu;
    QMenu *m_helpMenu;
    QAction *m_newAct;
    QAction *m_exitAct;
    QAction *m_miniAct;
    QAction *m_quickupAct;
    QAction *m_helpAct;
    chooseHead *m_hd;
    ProcessWidget *m_processWidget;
    ServiceWidget *m_serviceWidget;
    PerformanceWidget *m_performanceWidget;
    SystemWidget *m_systemWidget;
    QStackedWidget *m_stackWidget;
    infoWindow *m_infoWindow;
    //ISysInfo* m_systemInfo;
    InterfaceThread* m_interfaceThread;

private slots:
    void changed_process();
    void changed_service();
    void changed_performance();
    void changed_system();
};

#endif // TASKMANAGERWINDOW_H
