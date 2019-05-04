#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::treeInit(){
    ui->treeWidget->clear();
    ui->treeWidget->setHeaderLabel("农作物列表");
    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeWidget,SIGNAL(customContextMenuRequested(const QPoint&)),this,SLOT(treemenuclicked(const QPoint&)));
    connect(ui->treeWidget,SIGNAL(itemClicked(QTreeWidgetItem* ,int )),this,SLOT(treeclicked(QTreeWidgetItem* ,int)));
//    connect(ui->treeWidget,SIGNAL(:itemDoubleClicked(QTreeWidgetItem* ,int ),this,SLOT()));

    treeshow();
}
//显示
void MainWindow::treeshow()
{
    ui->treeWidget->clear();
    QList<QStringList> tmp=  m_pCreateDb->treedata();
    auto it=tmp.begin();
    for(;it!=tmp.end();it++){
        QStringList main=m_pCreateDb->maindata(*it);
        QTreeWidgetItem *item= new QTreeWidgetItem(ui->treeWidget,QStringList(QString((*it)[1])));
        auto it_m=main.begin();
        for(;it_m!=main.end();it_m++){
            QTreeWidgetItem *item_main=new QTreeWidgetItem(item,QStringList(QString(*it_m)));
            item_main->setIcon(0,QIcon(":/i/nzw.png"));
        }
    }
}


void MainWindow::treeclicked(QTreeWidgetItem* item,int col){
   qDebug()<<"treeclicked()"<<endl;
//   qDebug()<<item->columnCount()<<endl;
   qDebug()<<item->parent()<<endl;
   qDebug()<<ui->treeWidget->currentItem()->type()<<endl;
}


void MainWindow::treemainclicked(QTreeWidgetItem* ,int){

}
//右键菜单
//初始化
void MainWindow::righttreemenuinit(){
    firstree=new QMenu(this);
    secondtree=new QMenu(this);
    blank=new QMenu(this);
    addfirst=new QAction("添加分类",this);
    addfirst->setIcon(QIcon(":/i/plus.png"));
    deletefirst=new QAction("删除分类",this);
    deletefirst->setIcon((QIcon(":/i/delete.png")));
    renamefirst=new QAction("重命名分类",this);
    renamefirst->setIcon(QIcon(":/i/redo.png"));

    addsecond=new QAction("添加农作物",this);
    addsecond->setIcon(QIcon(":/i/plus.png"));
    deletesecond=new QAction("删除农作物",this);
    deletesecond->setIcon((QIcon(":/i/delete.png")));
    renamesecond=new QAction("重命名农作物",this);
    renamesecond->setIcon(QIcon(":/i/redo.png"));
    firstree->addAction(addfirst);
    firstree->addAction(deletefirst);
    firstree->addAction(renamefirst);
    secondtree->addAction(addsecond);
    secondtree->addAction(deletesecond);
    secondtree->addAction(renamesecond);
    blank->addAction(addfirst);
    connect(addfirst,SIGNAL(triggered()),this,SLOT(firstaddclicked()));
    connect(deletefirst,SIGNAL(triggered()),this,SLOT(firstdeleteclicked()));
    connect(renamefirst,SIGNAL(triggered()),this,SLOT(firstrenameclicked()));
    //子项菜单
    connect(addsecond,SIGNAL(triggered()),this,SLOT(secondaddclicked()));
    connect(deletesecond,SIGNAL(triggered()),this,SLOT(seconddeleteclicked()));
    connect(renamesecond,SIGNAL(triggered()),this,SLOT(secondrenameclicked()));

}
//目录右键添加
void MainWindow::firstaddclicked(){
    qDebug()<<"firstaddclicked"<<endl;
    operateType=Add;
    if(firstdlg){
        firstdlg->activateWindow();
        firstdlg->setWindowTitle("添加分类");
        firstdlg->exec();
    }
//    bool ok=m_pCreateDb->addfirstsql(first);
}
//添加返回处理
void MainWindow::firstadd(QString name){
    if(operateType==Add){
        bool ok=m_pCreateDb->addfirstsql(name);
        if(ok){
            QMessageBox::information(this ,tr("提示") , tr("添加成功!"));
        }
        else{
            QMessageBox::information(this ,tr("提示") , tr("添加失败!"));
        }
    }
    treeshow();
}

//目录右键删除
void MainWindow::firstdeleteclicked(){
    QTreeWidgetItem* item=ui->treeWidget->currentItem();
    QString first=item->text(0);
    bool ok=m_pCreateDb->deletefirstsql(first);
    if(ok){
        QMessageBox::information(this ,"提示" , "删除成功!");
    }
    else{
        QMessageBox::information(this ,"提示" , "删除失败!");
    }
    treeshow();
}
//目录右键重命名
void MainWindow::firstrenameclicked(){
    qDebug()<<"firstrenameclicked"<<endl;
    operateType=Edit;
    QTreeWidgetItem* item=ui->treeWidget->currentItem();
    QString first=item->text(0);
    if(first.isEmpty()){
        QMessageBox::information(this, "提示" , "请选中需要重命名的分类");
        return;
    }
    else{
       firstdlg->activateWindow();
       firstdlg->setWindowTitle("重命名分类");
       firstdlg->exec();

    }
    firstdlg->seteditdata(first);
}
void  MainWindow::firstrename(QString rename){
    qDebug()<<"firstrename "<<endl;
    if(operateType==Edit){
        QString name=nameclicked;
        qDebug()<<"firstrename "<<name<<endl;
        bool ok=m_pCreateDb->renamefirstsql(name,rename);
        if(ok){
            QMessageBox::information(this ,"提示" , "添加成功!");
        }
        else{
            QMessageBox::information(this ,"提示" , "添加失败!");
        }
    }
    treeshow();
}
//二级农作物添加
void MainWindow::secondaddclicked(){
qDebug()<<"secondaddclicked"<<endl;
operateType=Add;
if(seconddlg){
    seconddlg->activateWindow();
    seconddlg->setWindowTitle("添加农作物");
    seconddlg->exec();
}
}
void  MainWindow::secondadd(QString name){
    if(operateType==Add){
        bool ok=m_pCreateDb->addfirstsql(name);
        if(ok){
            QMessageBox::information(this ,tr("提示") , tr("添加成功!"));
        }
        else{
            QMessageBox::information(this ,tr("提示") , tr("添加失败!"));
        }
    }
    treeshow();
}
void MainWindow::seconddeleteclicked(){
qDebug()<<"seconddeleteclicked"<<endl;
}
void MainWindow::secondrenameclicked(){
qDebug()<<"secondrenameclicked"<<endl;
}
void  MainWindow::secondrename(QString name){
qDebug()<<"secondrename"<<endl;
}
void MainWindow::treemenuclicked(const QPoint& p){
    QTreeWidgetItem* item=ui->treeWidget->currentItem();
    nameclicked=item->text(0);
    qDebug()<<"*item "<<(item->parent()==nullptr)<<endl;
    if(item->parent()==nullptr){
         firstree->exec(QCursor::pos());
    }
    else{
        secondtree->exec(QCursor::pos());
    }

}

      
//addtree 窗口初始化
void MainWindow::firsttreeinit()
{
    firstdlg=new addtree;
    connect(firstdlg,SIGNAL(signalsname(QString)),this,SLOT(firstadd(QString)));
    connect(firstdlg,SIGNAL(signalsname(QString)),this,SLOT(firstrename(QString)));

}
void MainWindow::secondtreeinit()
{
    seconddlg=new addtree;
    connect(seconddlg,SIGNAL(signalsname(QString)),this,SLOT(secondadd(QString)));
    connect(seconddlg,SIGNAL(signalsname(QString)),this,SLOT(secondrename(QString)));
}




