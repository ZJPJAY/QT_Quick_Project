#ifndef THREADHANDLE_H
#define THREADHANDLE_H

#include <QObject>

class MyThread;
/**
 * @brief 线程处理
 * @author JAY_P
 * @version 1.0
 *          1.获取空闲线程
 *          2.移除连接
 */
class ThreadHandle : public QObject
{
    Q_OBJECT
protected:
    explicit ThreadHandle(QObject *parent = nullptr);

public:
    static ThreadHandle *getObject();
    /**
     * @brief 获取当前空闲线程，获取同时计数器加一
     * @return 当前空闲线程
     */
    MyThread *getThread();
    /**
     * @brief 从线程中删除一个对象,线程计数器减一
     */
    void removeThread(MyThread *);

protected:
    static ThreadHandle *thObj;
    QList<MyThread *> threadList;

signals:

public slots:
};

#endif // THREADHANDLE_H
