#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include <QTcpSocket>
class SqlExec;

class MyTcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit MyTcpSocket(QObject *parent = nullptr);
    void setDB(SqlExec *db);

signals:
    void sendData(QByteArray data);//群发的触发信号

public:
    void sendDataSlot(QByteArray data);
    //从MyTcpServer上绑定回来的信号槽，即每个socket都绑定了
    //只要触发一个socket上的senData信号就会触发所有socket的该信号槽

protected slots:
    void readyReadSlot();
    void disconnectedSlot();

protected:
    void handleData(QByteArray data);//解析tcp数据,得到完整的一组数据
    void handleFrame(QByteArray data);//解析Json数据,将完整的数据输入
    QByteArray temp;//缓存数据

    SqlExec *sqlExec;

signals:
    void socketDisconnected(QThread *th);


public slots:
};

#endif // MYTCPSOCKET_H
