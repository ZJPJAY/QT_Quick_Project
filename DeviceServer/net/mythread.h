#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>

class SqlExec;
/**
 * @brief 线程处理
 * @author JAY_P
 * @version 1.0
 *          1.保持数据库连接
 *          2.记录当前线程的负载
 */
class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = nullptr);
    /**
     * @brief 获取当前连接数
     * @return 连接数
     */
    int getCount();
    /**
     * @brief 连接数加一
     */
    void addCount();
    /**
     * @brief 连接数减一
     */
    void subCount();
    /**
     * @brief 设置数据库连接
     * @param db
     */
    void setDB(SqlExec *db);
    /**
     * @brief 获取数据库连接
     * @return 数据库
     */
    SqlExec *getDB();

protected:
    int count = 0;
    SqlExec *db;

signals:

public slots:
};

#endif // MYTHREAD_H
