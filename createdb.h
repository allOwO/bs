#ifndef CREATEDB_H
#define CREATEDB_H

#include <QList>
#include <QStringList>

class CreateDb
{
public:
    CreateDb();

    void initDB();
    bool addfirstsql(QString&);
    QList<QStringList> selectDataFromBase();
    QList<QStringList> treedata();
    QStringList maindata(QStringList tmp);
};

#endif // CREATEDB_H
