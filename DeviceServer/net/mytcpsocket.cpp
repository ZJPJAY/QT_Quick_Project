#include "mytcpsocket.h"
#include <QDebug>
#include "sqlexec.h"

MyTcpSocket::MyTcpSocket(QObject *parent) : QTcpSocket(parent)
{
    sqlExec = new SqlExec;
    connect(this,
            &MyTcpSocket::readyRead,
            this,
            &MyTcpSocket::readyReadSlot);
}

void MyTcpSocket::readyReadSlot()
{
    QByteArray data;
    data = this->readAll();
    qDebug() << data;
}
