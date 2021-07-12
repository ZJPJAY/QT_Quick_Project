#include "sqlexec.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

SqlExec::SqlExec(QObject *parent) : QObject(parent)
{
    db = new QSqlDatabase(QSqlDatabase::addDatabase("QMYSQL"));

    db->setHostName("127.0.0.1");
    db->setPort(3306);
    db->setUserName("root");
    db->setPassword("123456");
    db->setDatabaseName("test");
    db->open();

    qDebug() << "Connecting to Databases: " << db->open();
    qDebug() << "Error: " << db->lastError().type() << " -" << db->lastError();
}

bool SqlExec::addValue(int id, QString name)
{
    QString cmd;
    cmd = QString("Insert into zjctabletest (id,name) "
                  "values (%1,'%2')").arg(id).arg(name);

    QSqlQuery query;
    bool ok = query.exec(cmd);
    QString qd = (ok==1)? "[+] Insert Success!":"[-] Insert Failed!";
    qDebug() << qd.toUtf8().data();
    return ok;
}

bool SqlExec::selectValue(QString tableName)
{
    QString cmd;
    cmd = QString("Select * From %1").arg(tableName);

    QSqlQuery query;
    bool ok = query.exec(cmd);
    QString qd = (ok==1)? "[+] Success!":"[-] Failed!";
    qDebug() << qd.toUtf8().data();

    if(!ok)return false;
    while(query.next()){
        qDebug() << query.value(0) << "  ";
        qDebug() << query.value(1);
    }
    return ok;
}


