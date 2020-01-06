#ifndef ALARMWINDOW_H
#define ALARMWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QString>
#include <QTimer>

namespace Ui {
class AlarmWindow;
}

class AlarmWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AlarmWindow(QWidget *parent = 0);
    ~AlarmWindow();
    QSqlDatabase db;
    QTimer *timer = new QTimer(this);

    QString servername = "127.0.0.1";
    QString dbname = "alarmdb";
    QString dbusername = "root";
    QString dbpassword = "";

private slots:
    void on_VUsersButton_clicked();

    void on_VAlarmsButton_clicked();

    void on_VEventsButton_clicked();

    void on_RefreshButton_clicked();

    void on_AUserButton_clicked();

    void on_AAlarmButton_clicked();

    void on_RemoveButton_clicked();

private:
    Ui::AlarmWindow *ui;
};

#endif // ALARMWINDOW_H
