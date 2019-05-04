#include "createdb.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtDebug>
#include <QString>
CreateDb::CreateDb()
{

}

struct tabledata{ //数据传输结构体
   QString d;
   QByteArray image;
};



void CreateDb::initDB()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("test1.db");
    bool db_ok=db.open();
    if(!db_ok)
    {

        return ;
    }
    QString Selectsql ="SELECT COUNT(*) FROM sqlite_master where type='table' and name='tree'" ;
    QSqlQuery query;
    bool query_OK= query.exec(Selectsql);
    if(query.next())
    {
        qDebug()<< "have tree";
    }
    else
    {
        qDebug()<< "no tree!"  << db.lastError();
        query_OK=query.exec("CREATE TABLE tree ("
                            "ID integer PRIMARY KEY,"
                            "name TEXT(50) NOT NULL UNIQUE)");
        if(query_OK)
        {
            qDebug()<< "create tree success!";
        }
        else
        {
            qDebug()<< "create tree fail!"  << db.lastError();

        }
        query.exec("create table main(name TEXT(50) NOT NULL,idfrom integer NOT NULL)");
    }
}

QList<QStringList> CreateDb::selectDataFromBase()
{
    QSqlQuery query("SELECT * FROM StuManager");

    QList<QStringList> stuInfo;

    while (query.next())
    {
        QStringList rowData ;

        rowData <<query.value(2).toString();
        rowData <<query.value(1).toString();
        rowData <<query.value(3).toString();
        rowData <<query.value(4).toString();
        rowData <<query.value(5).toString();
        rowData <<query.value(6).toString();
        rowData <<query.value(7).toString();
        rowData <<query.value(8).toString();

        stuInfo.append(rowData);
    }
    return stuInfo;
}
QList<QStringList> CreateDb::treedata(){
    QSqlQuery query;
    query.exec("SELECT * FROM tree");
    QList<QStringList> treeinfo;
    while(query.next()){
         QStringList tmp;
         tmp << query.value(0).toString();//tree.ID
         tmp << query.value(1).toString();//tree.name
         treeinfo.append(tmp);
    }
    return treeinfo;
}

QStringList CreateDb::maindata(QStringList tmp){
    QString sql=QString("SELECT name FROM main where idfrom=%1").arg(tmp[0]);
    QSqlQuery query;
    bool ok=query.exec(sql);
//    qDebug()<<"maindata:"<<ok<<endl;

    QStringList ans;
    while(query.next()){
//        qDebug()<<"maindata:"<<query.value(0).toString()<<endl;
        QString data;
        data=query.value(0).toString();
        ans.append(data);
    }
    return ans;
}

bool CreateDb::addfirstsql(QString name)
{
   QString sql=QString("INSERT OR IGNORE INTO tree VALUES(NULL,'%1')").arg(name);
   QSqlQuery query;
   bool ok=query.exec(sql);
   return ok;
}
bool CreateDb::renamefirstsql(QString name,QString rename){
    if(rename.size()==0||name.size()==0){
        return false;
    }
    QString sql=QString("UPDATE tree set name='%1' where name='%2'").arg(rename).arg(name);
    QString sqls=QString("SELECT count(*) FROM tree where name='%1'").arg(rename);
    QSqlQuery query;
    query.exec(sqls);
    if (query.next()){
        int count =query.value(0).toInt();
//        qDebug()<<"renamesql "<<count<<endl;
        if(count){
            return false;
        }
    }
    bool ok=query.exec(sql);
    return ok;
}
bool CreateDb::deletefirstsql(QString name){
    if(name.size()==0){
        return false;
    }
    QString sql=QString("SELECT ID FROM tree where name='%1'").arg(name);
    int id;
    QSqlQuery query;
    query.exec(sql);
    if(query.next()){
        id=query.value(0).toInt();
    }
    else{
        return false;
    }
    QString sqls=QString("DELETE FROM tree WHERE ID=%1").arg(id);

    bool ok= query.exec(sqls);
    if(!ok){
        return false;
    }
    return deletesecondsql(id);
}
bool CreateDb::addsecondsql(QString name){
    QString sql=QString("INSERT OR IGNORE INTO main VALUES(NULL,'%1')").arg(name);
    QSqlQuery query;
    bool ok=query.exec(sql);
    if(!ok)return ok;
    QString Selectsql =QString("SELECT COUNT(*) FROM sqlite_master where type='table' and name='%1'").arg(name) ;
    query.exec(Selectsql);

    QString sqls=QString("CREATE TABLE %1 ( name TEXT(50) PRIMARY KEY NOT NULL,"
                                                       "addtime TEXT(50) NOT NULL,"
                                                       "shootime text(50) NOT NULL,"
                                                       "place TEXT(50) NOT NULL,"
                                                       "from TEXT(50) NOT NULL,"
                                                       "region TEXT(50) NOT NULL)").arg(name);
    ok=query.exec(sqls);
    return ok;
}
bool CreateDb::deletesecondsql(int id){
    return true;
}
bool CreateDb::deletesecondsql(QString name){
    return true;
}


