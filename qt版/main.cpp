#include "TaskManagerWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TaskManagerWindow w;
    w.show();

    return a.exec();
}
