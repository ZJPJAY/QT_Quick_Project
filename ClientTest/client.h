#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>

class QTcpSocket;

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    /**
     * @brief sendData  向服务器发送数据
     * @param data  要发送的数据
     */
    void sendData(const QByteArray &data);

protected:
    QTcpSocket *socket;

protected slots:
    void readyReadSlot();

signals:
    /**
     * @brief readData  从服务器接收数据
     * @param data  接收到的数据
     */
    void readData(QByteArray data);

public slots:
};

#endif // CLIENT_H
