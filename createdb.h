#ifndef CREATEDB_H
#define CREATEDB_H

#include <QList>
#include <QStringList>

class CreateDb
{
public:
    CreateDb();
    void initDB();
    bool addfirstsql(QString);
    bool renamefirstsql(QString,QString);
    bool deletefirstsql(QString);
    bool addsecondsql(QString);
    bool renamesecondsql(QString,QString);
    bool deletesecondsql(QString);
    bool deletesecondsql(int);
    QList<QStringList> selectDataFromBase();
    QList<QStringList> treedata();
    QStringList maindata(QStringList tmp);
};

#endif // CREATEDB_H
