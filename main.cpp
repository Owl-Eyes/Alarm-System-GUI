#include "alarmwindow.h"
#include <QApplication>
#include <QtSql>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AlarmWindow w;
    w.show();

    return a.exec();
}
