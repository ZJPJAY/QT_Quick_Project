#include "server.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>

Server::Server(QObject *parent)
    : QObject(parent)
    , server(new QTcpServer)
{
    server->listen(QHostAddress::Any,10001);

    connect(server,
            &QTcpServer::newConnection,
            this,
            &Server::newConnectionSlot);

}

void Server::newConnectionSlot()
{

    qDebug() << "New Connection";
    QTcpSocket *socket = server->nextPendingConnection();

    socket->write("Hello");
    connect(socket,
            &QTcpSocket::readyRead,
            this,
            &Server::socketReadyReadSlot);

    connect(socket,
            &QTcpSocket::stateChanged,
            this,
            &Server::stateChange);

}

void Server::socketReadyReadSlot()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket *> (sender());

    QByteArray data;
    data = socket->readAll();
    QString str = QString::fromLocal8Bit(data);
    qDebug() << str;
}

void Server::stateChange()
{
    qDebug() << "State Changed!";
}
