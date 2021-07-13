#include "threadhandle.h"
#include "mythread.h"
#include "sqlexec.h"

ThreadHandle *ThreadHandle::thObj = nullptr;

ThreadHandle::ThreadHandle(QObject *parent) : QObject(parent)
{
    for(int i = 0;i < 10;i++){
        SqlExec *db = new SqlExec(
                    QString("DBCon-%1").arg(i)
                    );
        MyThread *thread = new MyThread;
        thread->setDB(db);

        db->moveToThread(thread);//数据库的操作移到线程中
        thread->start();//开启线程
        threadList.append(thread);//添加线程到线程池
    }
}

ThreadHandle *ThreadHandle::getObject()
{
    if(thObj == nullptr)
        thObj = new ThreadHandle;
    return thObj;
}

MyThread *ThreadHandle::getThread()
{
    int index = 0;
    int minCount = threadList.at(0)->getCount();

    for(int i = 1;i < 10;i++){
        if(threadList.at(i)->getCount() < minCount){
            minCount = threadList.at(i)->getCount();
            index = i;
        }
    }
    threadList.at(index)->addCount();
    return threadList.at(index);
}

void ThreadHandle::removeThread(MyThread *th)
{
    for(int i = 0;i < 10;i++){
        if(threadList.at(i) == th){
            threadList.at(i)->subCount();
            return;
        }
    }
}

