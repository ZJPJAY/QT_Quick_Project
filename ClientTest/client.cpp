#include "client.h"
#include <QTcpSocket>

Client::Client(QObject *parent)
    : QObject(parent)
    , socket(new QTcpSocket)
{
    socket->connectToHost("127.0.0.1",10001);

    connect(socket,
            &QTcpSocket::readyRead,
            this,
            &Client::readyReadSlot);
}

void Client::sendData(const QByteArray &data)
{
    socket->write(data);
}

void Client::readyReadSlot()
{
    QByteArray data;
    data = socket->readAll();

    emit readData(data);
}
