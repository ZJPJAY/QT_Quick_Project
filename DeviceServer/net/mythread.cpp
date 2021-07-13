#include "mythread.h"

MyThread::MyThread(QObject *parent) : QThread(parent)
{

}

int MyThread::getCount()
{
    return count;
}

void MyThread::addCount()
{
    count++;
}

void MyThread::subCount()
{
    count--;
    if(count < 0)
        count = 0;
}

void MyThread::setDB(SqlExec *db)
{
    this->db = db;
}

SqlExec *MyThread::getDB()
{
    return db;
}
