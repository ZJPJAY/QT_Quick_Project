#include "sqlexec.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>

SqlExec::SqlExec(QString name,QObject *parent) : QObject(parent)
{
    db = new QSqlDatabase(QSqlDatabase::addDatabase("QMYSQL",name));

    db->setHostName("127.0.0.1");//192.168.43.247
    db->setPort(3306);
    db->setUserName("root");
    db->setPassword("123456");
    db->setDatabaseName("test");
    db->open();

    qDebug() << "Connecting to Databases: " << db->open();
    qDebug() << "Error: " << db->lastError().type() << " -" << db->lastError().text().toUtf8().data();
}
/*
bool SqlExec::addValue(int id, QString name)
{
    QString cmd;
    cmd = QString("Insert into models_co2 (id,name) "
                  "values (%1,'%2')").arg(id).arg(name);

    QSqlQuery query(*db);
    bool ok = query.exec(cmd);
    QString qd = (ok==1)? "[+] Insert Success!":"[-] Insert Failed!";
    qDebug() << qd.toUtf8().data();
    return ok;
}
*/
bool SqlExec::addValue(int id,double value,QString tableName,QString propertyName)
{
    QString cmd;
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy-MM-dd hh:mm:ss");
    cmd = QString("INSERT INTO %1 "
                  "(id, %2, add_time) "
                  "VALUES(%3,%4,'%5');").arg(tableName).arg(propertyName).arg(id).arg(value).arg(current_date);

    QSqlQuery query(*db);
    bool ok = query.exec(cmd);
    QString qd = (ok==1)? "[+] Insert Success!":"[-] Insert Failed!";

    qDebug() << qd.toUtf8().data() << current_date.toUtf8().data();
    if(db->lastError().type() != 0)qDebug() << db->lastError().text().toUtf8().data();
    return ok;
}
/*
bool SqlExec::addValue(int id, int value)
{
    QString cmd;
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy-MM-dd hh:mm:ss");
    cmd = QString("INSERT INTO models_co2 "
                  "(id, co2_consistence, add_time) "
                  "VALUES(%1,%2,'%3');").arg(id).arg(value).arg(current_date);


    QSqlQuery query(*db);
    bool ok = query.exec(cmd);
    QString qd = (ok==1)? "[+] Insert Success!":"[-] Insert Failed!";

    qDebug() << qd.toUtf8().data() << current_date.toUtf8().data();
    if(db->lastError().type() != 0)qDebug() << db->lastError().text().toUtf8().data();
    return ok;
}
*/
int SqlExec::selectValue(QString tableName)
{
    QString cmd;
    int id = 1;
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy-MM-dd hh:mm:ss");
    cmd = QString("SELECT * FROM %1").arg(tableName);

    QSqlQuery query(*db);
    bool ok = query.exec(cmd);
    QString qd = (ok==1)? "[+] Select Success!":"[-] Select Failed!";

    qDebug() << qd.toUtf8().data() << current_date.toUtf8().data();
    if(db->lastError().type() != 0)qDebug() << db->lastError().text().toUtf8().data();

    if(!ok){qDebug()<< "[-] SelectValue Return False!"; return false;}
    if((query.size() != 0) && query.last()){
        if(id >= query.value(0).toInt())
            id += query.value(0).toInt();
    }
    return id;
}


