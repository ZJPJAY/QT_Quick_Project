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

protected slots:
    void readyReadSlot();
    void disconnectedSlot();

protected:
    void handleData(QByteArray data);//解析tcp数据,得到完整的一组数据
    void handleFrame(QByteArray data);//解析json数据,将完整的数据输入
    QByteArray temp;//缓存数据

    SqlExec *sqlExec;

signals:
    void socketDisconnected(QThread *th);


public slots:
};

#endif // MYTCPSOCKET_H
