#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QTcpServer>
/**
 * @brief 提供网络服务
 * @author JAY_P
 * @date 2021-07-12
 * @version V1.0
 *          1.网络服务
 *          2.提供个性定制的socket对象
 *          3.socket移入线程池管控
 */
class MyTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = nullptr);

signals:
    void sendData(QByteArray data);//该触发信号与MyTcpSocket上的同名，以socket上的信号触发该信号

protected:
    virtual void incomingConnection(qintptr socketDescriptor);

protected slots:
    void socketDisconnectedSlot(QThread *th);

signals:

public slots:
};

#endif // MYTCPSERVER_H
