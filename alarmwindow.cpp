#include "alarmwindow.h"
#include "ui_alarmwindow.h"
#include <QtSql>
#include <QTimer>
#include <QInputDialog>
#include <QDebug>

AlarmWindow::AlarmWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AlarmWindow)
{
    ui->setupUi(this);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(on_RefreshButton_clicked()));
    timer->start(60000*2.5);    //each 2.5 minutes

}

AlarmWindow::~AlarmWindow()
{
    delete ui;
}

void AlarmWindow::on_VUsersButton_clicked()     //VIEW USERS
{
    QSqlDatabase db;

    db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("");
        db.setDatabaseName(dbname);
        db.setUserName(dbusername);
        db.setPassword(dbpassword);

    if (db.open())
    {

            QTableView *view = new QTableView(this);

            QSqlQueryModel *tableViewModel = new QSqlQueryModel;
            tableViewModel->setQuery("SELECT * FROM alarmdb.users");

            tableViewModel->setHeaderData(0, Qt::Horizontal, "User ID");
            tableViewModel->setHeaderData(1, Qt::Horizontal, "Username");
            tableViewModel->setHeaderData(2, Qt::Horizontal, "Password");
            tableViewModel->setHeaderData(3, Qt::Horizontal, "Phone Number");
            tableViewModel->setHeaderData(4, Qt::Horizontal, "Address");
            tableViewModel->setHeaderData(5, Qt::Horizontal, "Metadata");

            view->setModel(tableViewModel);
            view->resizeColumnsToContents();
            view->setAlternatingRowColors(true);
            view->move(120,445);
            view->resize(ui->tableView_2->width(),ui->tableView_2->height());
            view->show();

            db.close();

    }
    else
    {
        qDebug() << "Error: " << db.lastError().text();
    }
    db.removeDatabase("QMYSQL");
}

void AlarmWindow::on_VAlarmsButton_clicked()        //VIEW ALARMS
{
    QSqlDatabase db;

    db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("");
        db.setDatabaseName(dbname);
        db.setUserName(dbusername);
        db.setPassword(dbpassword);

    if (db.open())
    {

            QTableView *view = new QTableView(this);

            QSqlQueryModel *tableViewModel = new QSqlQueryModel;
            tableViewModel->setQuery("SELECT * FROM alarmdb.alarms");

            tableViewModel->setHeaderData(0, Qt::Horizontal, "Alarm ID");
            tableViewModel->setHeaderData(1, Qt::Horizontal, "Alarm Description");
            tableViewModel->setHeaderData(2, Qt::Horizontal, "Config");

            view->setModel(tableViewModel);
            view->resizeColumnsToContents();
            view->setAlternatingRowColors(true);
            view->move(120,445);
            view->resize(ui->tableView_2->width(),ui->tableView_2->height());
            view->show();

            db.close();

    }
    else
    {
        qDebug() << "Error: " << db.lastError().text();
    }
    db.removeDatabase("QMYSQL");
}

void AlarmWindow::on_VEventsButton_clicked()        //VIEW EVENTS
{
    QSqlDatabase db;

    db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("");
        db.setDatabaseName(dbname);
        db.setUserName(dbusername);
        db.setPassword(dbpassword);

    if (db.open())
    {

            QTableView *view = new QTableView(this);

            QSqlQueryModel *tableViewModel = new QSqlQueryModel;
            tableViewModel->setQuery("SELECT * FROM alarmdb.events");

            tableViewModel->setHeaderData(0, Qt::Horizontal, "Event ID");
            tableViewModel->setHeaderData(1, Qt::Horizontal, "Event Time");
            tableViewModel->setHeaderData(2, Qt::Horizontal, "User ID");
            tableViewModel->setHeaderData(3, Qt::Horizontal, "EventDescription");

            view->setModel(tableViewModel);
            view->resizeColumnsToContents();
            view->setAlternatingRowColors(true);
            view->move(120,445);
            view->resize(ui->tableView_2->width(),ui->tableView_2->height());
            view->show();

            db.close();

    }
    else
    {
        qDebug() << "Error: " << db.lastError().text();
    }
    db.removeDatabase("QMYSQL");
}

void AlarmWindow::on_RefreshButton_clicked()        //VIEW MOST RECENT EVENTS
{
    QSqlDatabase db;

    db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("");
        db.setDatabaseName(dbname);
        db.setUserName(dbusername);
        db.setPassword(dbpassword);

    if (db.open())
    {

            QTableView *view = new QTableView(this);

            QSqlQueryModel *tableViewModel = new QSqlQueryModel;
            tableViewModel->setQuery("SELECT * FROM alarmdb.events ORDER BY EventID DESC");

            tableViewModel->setHeaderData(0, Qt::Horizontal, "Event ID");
            tableViewModel->setHeaderData(1, Qt::Horizontal, "Event Time");
            tableViewModel->setHeaderData(2, Qt::Horizontal, "User ID");
            tableViewModel->setHeaderData(3, Qt::Horizontal, "EventDescription");

            view->setModel(tableViewModel);
            view->resizeColumnsToContents();
            view->setAlternatingRowColors(true);
            view->move(300,134);
            view->resize(ui->tableView->width(),ui->tableView->height());
            view->show();

            db.close();

    }
    else
    {
        qDebug() << "Error: " << db.lastError().text();
    }
    db.removeDatabase("QMYSQL");
}

void AlarmWindow::on_AUserButton_clicked()
{
    QSqlDatabase db;

    db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("");
        db.setDatabaseName(dbname);
        db.setUserName(dbusername);
        db.setPassword(dbpassword);
        db.open();

    if (db.open())
    {
        QString newuser = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                                tr("New Username: "), QLineEdit::Normal);
        QString newpass = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                                tr("New Password: "), QLineEdit::Normal);
        QString newnumber = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                                tr("New Phone number: "), QLineEdit::Normal);
        QString newadd = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                                tr("New Address: "), QLineEdit::Normal);
        QString newmeta = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                                tr("New Metadata: "), QLineEdit::Normal);

        QSqlQuery query;
        query.prepare("INSERT INTO Users (username, password, phonenumber, address, metadata) "
                      "VALUES (:nusername, :npassword, :nphonenumber, :naddress, :nmetadata)");
        query.bindValue(":nusername", newuser);
        query.bindValue(":npassword", newpass);
        query.bindValue(":nphonenumber", newnumber.toInt());
        query.bindValue(":naddress", newadd);
        query.bindValue(":nmetadata", newmeta);
        //query.exec();

        if( !query.exec() )
                 qDebug() << query.lastError().text();
             else
                 qDebug( "Inserted!" );

        db.close();

    }
    else
    {
        qDebug() << "Error: " << db.lastError().text();
    }

    db.close();
    db.removeDatabase("QMYSQL");
}

void AlarmWindow::on_AAlarmButton_clicked()
{
    QSqlDatabase db;

    db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("");
        db.setDatabaseName(dbname);
        db.setUserName(dbusername);
        db.setPassword(dbpassword);

    if (db.open())
    {
        QString newalarmdesc = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                                tr("New Alarm description: "), QLineEdit::Normal);
        QString newconfig = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                                tr("New Configuration: "), QLineEdit::Normal);

        QSqlQuery query;
        query.prepare("INSERT INTO Alarms (alarmdescription, config) "
                      "VALUES (:ndesc, :nconfig)");
        query.bindValue(":ndesc", newalarmdesc);
        query.bindValue(":nconfig", newconfig);
        //query.exec();

        if( !query.exec() )
                 qDebug() << query.lastError().text();
             else
                 qDebug( "Inserted!" );

        db.close();

    }
    else
    {
        qDebug() << "Error: " << db.lastError().text();
    }

    db.removeDatabase("QMYSQL");
}

void AlarmWindow::on_RemoveButton_clicked()
{
    QSqlDatabase db;

    db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("");
        db.setDatabaseName(dbname);
        db.setUserName(dbusername);
        db.setPassword(dbpassword);
        db.open();

    if (db.open())
    {
        QString systoberemoved = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                                tr("System to be Removed: "), QLineEdit::Normal);

        QSqlQuery qry;
        qry.prepare("DELETE FROM Alarms WHERE AlarmID = :sysrem ");
        qry.bindValue(":sysrem", systoberemoved);
        qry.exec();

        QSqlQuery query;
        query.prepare("DELETE FROM Users WHERE UserID = :sysrem ");
        query.bindValue(":sysrem", systoberemoved);
        //query.exec();

        if( !query.exec() )
                 qDebug() << query.lastError().text();
             else
                 qDebug( "Removed!" );

        db.close();

    }
    else
    {
        qDebug() << "Error: " << db.lastError().text();
    }

    db.close();
    db.removeDatabase("QMYSQL");
}
