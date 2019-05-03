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
        query_OK=query.exec("CREATE TABLE tree (ID INTEGER primary key NOT NULL,"
                   "name TEXT NOT NULL)");
        if(query_OK)
        {
            qDebug()<< "create tree success!";
        }
        else
        {
            qDebug()<< "create tree fail!"  << db.lastError();

        }
        query.exec("create table main(name varchar(50) NOT NULL,idfrom integer NOT NULL");
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
    qDebug()<<"tredata"<<endl;
    while(query.next()){
         qDebug()<<"treedata:"<<query.value(0).toString()<<endl;
         QStringList tmp;
         tmp << query.value(0).toString();//tree.ID
         tmp << query.value(1).toString();//tree.name
         treeinfo.append(tmp);
    }
    return treeinfo;
}

QStringList CreateDb::maindata(QStringList tmp){
    QString sql=QString("SELECT name FROM main where idfrom=%1").arg(tmp[0]);
    qDebug()<<sql<<endl;
    QSqlQuery query;
    bool ok=query.exec(sql);
    qDebug()<<"maindata:"<<ok<<endl;

    QStringList ans;
    while(query.next()){
        qDebug()<<"maindata:"<<query.value(0).toString()<<endl;
        QString data;
        data=query.value(0).toString();
        ans.append(data);
    }
    return ans;
}

bool CreateDb::addfirstsql(QString& name)
{
   QString sql=QString("INSERT INTO tree VALUES(NULL,'%1')").arg(name);
   QSqlQuery query;
   bool ok=query.exec(sql);
   return ok;
}

