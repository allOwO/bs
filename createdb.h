#ifndef CREATEDB_H
#define CREATEDB_H

#include <QList>
#include <QStringList>
#include <QVariantMap>
#include<QDateTime>
struct tabledata//数据传输结构体
{
   QString name,addtime,shootime,place,wherefrom,region,imagesuffix;
   QByteArray image;
};
class CreateDb
{
public:
    CreateDb();
    void initDB();
    bool addfirstsql(QString);
    bool renamefirstsql(QString,QString);
    bool deletefirstsql(QString);
    bool addsecondsql(QString,QString);
    bool renamesecondsql(QString,QString);
    bool deletesecondsql(QString);
    bool deletesecondsql(int);
    QList<QStringList> treedata();
    QStringList maindata(QStringList);
    QStringList mainonedata(QString);
    QStringList treeonedata(QString);
    QStringList treeiddata(QString );
    QList<tabledata> tableline(QString);
    QList<tabledata> findline(QString,int,QString);
    bool addnzwimage(QVariantMap);
    bool changenzwimage(QVariantMap);
    bool deletenzwimage(QVariantMap);
};

#endif // CREATEDB_H
