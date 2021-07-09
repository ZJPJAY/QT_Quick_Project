#ifndef SERVER_H
#define SERVER_H

#include <QObject>

class QTcpServer;

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

protected:
       QTcpServer *server;

protected slots:
       void newConnectionSlot();
       void socketReadyReadSlot();

       void stateChange();

signals:

public slots:
};

#endif // SERVER_H
