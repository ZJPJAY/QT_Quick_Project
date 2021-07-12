#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include <QTcpSocket>
class SqlExec;

class MyTcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit MyTcpSocket(QObject *parent = nullptr);

protected slots:
    void readyReadSlot();

protected:
    SqlExec *sqlExec;

signals:


public slots:
};

#endif // MYTCPSOCKET_H
