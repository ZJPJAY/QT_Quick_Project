#ifndef SERVER_H
#define SERVER_H

#include <QObject>

class QTcpServer;
class QTcpSocket;

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

    /**
     * @brief sendDataToAllClient 向所有的客户端发送请求
     * @param data  要发送的数据
     */
    void sendDataToAllClient(const QByteArray &data);

protected:
       QTcpServer *server;
       QList<QTcpSocket *> socketList;

protected slots:
       void newConnectionSlot();
       void socketReadyReadSlot();
       void socketDisconnectedSlot();

       void stateChange();

signals:

public slots:
};

#endif // SERVER_H
