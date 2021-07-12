#include <QCoreApplication>
#include "mytcpserver.h"
#include "sqlexec.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyTcpServer s;
    s.listen(QHostAddress::Any, 10001);
    
    SqlExec sql;
    sql.addValue(3,"张三");
    sql.selectValue("zjctabletest");

    return a.exec();
}
