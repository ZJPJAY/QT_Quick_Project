#ifndef SQLEXEC_H
#define SQLEXEC_H

#include <QObject>
class QSqlDatabase;

class SqlExec : public QObject
{
    Q_OBJECT
public:
    explicit SqlExec(QString name, QObject *parent = nullptr);
    bool addValue(int id,QString name);
    bool selectValue(QString tableName);
    bool deleteValue(QString tableName,QString typeName,QString deleteThing);
    //delete from <tableName> where <typeName> = deleteName;
    bool updateValue(QString tableName,QString typeName,QString updateThing);
    //update <tableName> set <typename> = <updateThing>;

protected:
    QSqlDatabase *db;

signals:

public slots:
};

#endif // SQLEXEC_H
