#include "createdb.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtDebug>
#include <QString>
#include <QPixmap>
CreateDb::CreateDb(){

}
void CreateDb::initDB()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("test1.db");
    bool db_ok=db.open();
    if(!db_ok)
    {

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
                            "ID integer PRIMARY KEY AUTOINCREMENT,"
                            "name TEXT(20) NOT NULL UNIQUE)");
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
//查找单个目录
QStringList CreateDb::treeonedata(QString name)
{
    qDebug()<<"treeonedata:"<<name<<endl;
    QStringList tmp;
    QString sql=QString("SELECT * FROM tree where name='%1'").arg(name);
    QSqlQuery query;
    query.exec(sql);
    while(query.next()){
        tmp <<query.value(0).toString();//id||idfrom
        tmp <<query.value(1).toString();//name
        qDebug()<<"treeonedata:"<<tmp<<endl;
    }
    return tmp;
}
//查找子节点
QStringList CreateDb::maindata(QStringList tmp){
    QString sql=QString("SELECT name FROM main where idfrom=%1").arg(tmp[0]);
    QSqlQuery query;
    query.exec(sql);
    QStringList ans;
    while(query.next()){
//        qDebug()<<"maindata:"<<query.value(0).toString()<<endl;
        QString data;
        data=query.value(0).toString();
        ans.append(data);
    }
    return ans;
}
//查找单个子节点
QStringList CreateDb::mainonedata(QString name)
{
    QStringList tmp;
    QString sql=QString("SELECT * FROM main where name='%1'").arg(name);
    QSqlQuery query;
    query.exec(sql);
    while(query.next()){
        tmp <<query.value(0).toString();//name
        tmp <<query.value(1).toString();//idfrom
    }
    return tmp;
}
bool CreateDb::addfirstsql(QString name)
{
   QSqlQuery query;
   QString sql2=QString("SELECT count(*) FROM tree where name='%1'").arg(name);
   QString sql=QString("INSERT OR IGNORE INTO tree VALUES(NULL,'%1')").arg(name);
   query.exec(sql2);
   if(query.next()){
       if(query.value(0).toInt()==1){
           return false;
       }
   }
   bool ok=query.exec(sql);
   return ok;
}
bool CreateDb::renamefirstsql(QString name,QString rename){
    if(rename.size()==0||name.size()==0){
        return false;
    }
    QString sqls=QString("SELECT count(*) FROM tree where name='%1'").arg(rename);
    QString sql=QString("UPDATE tree set name='%1' where name='%2'").arg(rename).arg(name);
    QSqlQuery query;
    qDebug()<<"renamefirst ??"<<endl;
    query.exec(sqls);
    if (query.next()){
        int count =query.value(0).toInt();
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
    QString id=treeonedata(name).value(0);
    if(id.size()==0)return false;
    QString sqls=QString("DELETE FROM tree WHERE ID=%1").arg(id);
    QSqlQuery query;
    deletesecondsql(id.toInt());
    query.exec(sqls);
    return true;
}
bool CreateDb::addsecondsql(QString id,QString name){
    QString sql=QString("INSERT OR IGNORE INTO main VALUES(%1,'%2')").arg(id).arg(name);
    QSqlQuery query;
    bool ok=query.exec(sql);
    if(!ok)return ok;
    QString Selectsql =QString("SELECT COUNT(*) FROM sqlite_master where type='table' and name='%1'").arg(name) ;
    ok=query.exec(Selectsql);
    if(query.next()&&query.value(0).toInt()!=0){
            return ok;
    }
    QString sqls=QString("CREATE TABLE %1 ( name TEXT(20)  NOT NULL,"
                                                       "addtime TEXT(25) NOT NULL,"
                                                       "shootime TEXT(25) NOT NULL,"
                                                       "place TEXT(40) NOT NULL,"
                                                       "wherefrom TEXT(20) NOT NULL,"
                                                       "region TEXT(20) NOT NULL,image BLOB NOT NULL)").arg(name);
    ok=query.exec(sqls);
    if(!ok){
        query.exec(QString("DROP TABLE %1").arg(name));
    }
//     qDebug()<<"addsecondsql 2::"<<ok<<endl;
    return ok;
}
bool CreateDb::renamesecondsql(QString name,QString rename){
    if(rename.size()==0||name.size()==0){
        return false;
    }
    QString sqls=QString("SELECT count(*) FROM main where name='%1'").arg(rename);
    QString sql=QString("UPDATE main set name='%1' where name='%2'").arg(rename).arg(name);
    QSqlQuery query;
    query.exec(sqls);
    if (query.next()){
        int count =query.value(0).toInt();
        if(count){
            return false;
        }
    }
    bool ok=query.exec(sql);
    return ok;
}
bool CreateDb::deletesecondsql(int id){
    QString sql1=QString("SELECT name FROM main WHERE idfrom=%1").arg(id);
    QSqlQuery query;
    bool ok= query.exec(sql1);
    while(query.next()){
        deletesecondsql(query.value(1).toString());
    }
    return ok;
}
bool CreateDb::deletesecondsql(QString name){
    if(name.size()==0){
        return false;
    }
    QString sql=QString("DELETE FROM main WHERE name='%1'").arg(name);
    QSqlQuery query;
    bool ok= query.exec(sql);
    if(!ok){
        return false;
    }
    QString sqls=QString("DROP TABLE %1").arg(name);
    query.exec(sqls);
    return ok;
}

QList<tabledata> CreateDb::tableline(QString name){
    qDebug()<< "tableline1"<<endl;
    QString sql1=QString("SELECT * FROM %1").arg(name);
    QList<tabledata> tmp;
    QSqlQuery query;
    if(query.exec(sql1))
    {
        while(query.next()){
            tabledata data{ query.value(0).toString(),
                            query.value(1).toString(),
                            query.value(2).toString(),
                            query.value(3).toString(),
                            query.value(4).toString(),
                            query.value(5).toString(),
                            query.value(6).toByteArray()};
            tmp.append(data);
//            qDebug()<< "tableline"<<data.addtime<<endl;
        }
    }
    return tmp;
}

bool CreateDb::addnzwimage(QVariantMap info)
{
    QString name= info.value("name").toString();
    QString shoot=info.value("shootime").toString();
    QString place=info.value("place").toString();
    QString region=info.value("region").toString();
    QString from=info.value("from").toString();
    QString path=info.value("path").toString();
    QString addtime;
    QByteArray image;
    if(path.size()==0){
            return false;
    }
    else{
        addtime=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        QFile imagefile(path);
        bool ok=imagefile.open(QIODevice::ReadOnly);
        if(!ok){
            return false;
        }
        image=imagefile.readAll();
    }
    addfirstsql(from);
    QString id=treeonedata(from).value(0);
    addsecondsql(id,name);
    QSqlQuery query;
    QString sql=QString("INSERT INTO %1 VALUES('%1','%2','%3','%4','%5','%6',").arg(name).arg(addtime).arg(shoot).arg(place).arg(from).arg(region);
    query.prepare(sql+":image)");
    query.bindValue(":image",image);
    bool ok=query.exec();
    qDebug()<<"addnzwimage "<<ok<<endl;
    return ok;
}


bool CreateDb::changenzwimage(QVariantMap info){
    QString name= info.value("name").toString();
    QString shoot=info.value("shootime").toString();
    QString place=info.value("place").toString();
    QString region=info.value("region").toString();
    QString from=info.value("from").toString();
    QString addtime=info.value("addtime").toString();
    QString oldname=info.value("oldname").toString();
    qDebug()<<name<<" changenzwimage  "<<oldname<<endl;
    bool ok=true;
    if(name.isEmpty()||shoot.isEmpty()||place.isEmpty()||region.isEmpty()||from.isEmpty())
        return false;
    else{
        addfirstsql(from);
        QString id=treeonedata(from).value(0);
        addsecondsql(id,name);

        QSqlQuery query;
        QString sql2=QString("UPDATE  %1 set name='%1',shootime='%2',place='%3',wherefrom='%4',region='%5' where addtime='%6'").arg(oldname).arg(shoot).arg(place).arg(from).arg(region).arg(addtime);
        qDebug()<<"changenzwimage f"<<sql2<<endl;
        if(name!=oldname){
            QString sql_sel=QString("SELECT * FROM %1 where addtime='%2'").arg(oldname).arg(addtime);
            QString sql_in=QString("INSERT INTO %1 VALUES('%1','%2','%3','%4','%5','%6',").arg(name).arg(addtime).arg(shoot).arg(place).arg(from).arg(region);

            query.exec(sql_sel);
            query.next();
            QByteArray image=query.value(6).toByteArray();
            query.prepare(sql_in+":image)");
            query.bindValue(":image",image);
            QVariantMap olddata;
            olddata.insert("name",oldname);
            olddata.insert("addtime",addtime);
            deletenzwimage(olddata);
        }
        else{
            query.exec(sql2);//名称没变，更新
        }
    qDebug()<<"changenzwimage s"<<ok<<endl;
    return ok;
}
}


bool CreateDb::deletenzwimage(QVariantMap info)
{
    QString name= info.value("name").toString();
    QString addtime=info.value("addtime").toString();
    QString sql=QString("DELETE FROM %1 WHERE addtime='%2'").arg(name).arg(addtime);
    QSqlQuery query;
    bool ok=query.exec(sql);
    return ok;
}
