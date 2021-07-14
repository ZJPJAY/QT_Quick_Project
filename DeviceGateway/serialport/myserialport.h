#ifndef MYSERIALPORT_H
#define MYSERIALPORT_H

#include <QSerialPort>

class MySerialPort : public QSerialPort
{
    Q_OBJECT
protected:
    explicit MySerialPort(QObject *parent = nullptr);

public:
    static MySerialPort *getObject();
    QStringList getPortList();

protected:
    static MySerialPort *mspObj;

signals:

public slots:
};

#endif // MYSERIALPORT_H
