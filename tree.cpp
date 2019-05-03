#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::treeInit(){
    righttreemenuinit();
    ui->treeWidget->clear();
    ui->treeWidget->setHeaderLabel("农作物列表");
    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeWidget,SIGNAL(customContextMenuRequested(const QPoint&)),this,SLOT(treemenuclicked(const QPoint&)));
    connect(ui->treeWidget,SIGNAL(itemClicked(QTreeWidgetItem* ,int )),this,SLOT(treeclicked(QTreeWidgetItem* ,int)));
//    connect(ui->treeWidget,SIGNAL(:itemDoubleClicked(QTreeWidgetItem* ,int ),this,SLOT()));

    treeshow();
}
//展示
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
        }
    }
}


//2号再写
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

    connect(addsecond,SIGNAL(triggered()),this,SLOT(secondaddclicked()));
    connect(deletesecond,SIGNAL(triggered()),this,SLOT(seconddeleteclicked()));
    connect(renamesecond,SIGNAL(triggered()),this,SLOT(secondrenameclicked()));

}
void MainWindow::firstaddclicked(){
    QString first;
    qDebug()<<first<<endl;
    bool ok=m_pCreateDb->addfirstsql(first);
    if(ok){

    }
}
void MainWindow::firstdeleteclicked(){
    QTreeWidgetItem* item=ui->treeWidget->currentItem();
    QString first=item->text(0);
    qDebug()<<first<<endl;
}
void MainWindow::firstrenameclicked(){
    QTreeWidgetItem* item=ui->treeWidget->currentItem();
    QString first=item->text(0);
    qDebug()<<first<<endl;
}
void MainWindow::secondaddclicked(){

}
void MainWindow::seconddeleteclicked(){

}
void MainWindow::secondrenameclicked(){

}
//右键事件
void MainWindow::treemenuclicked(const QPoint& p){
    QTreeWidgetItem* item=ui->treeWidget->currentItem();
    qDebug()<<"*item "<<(item->parent()==nullptr)<<endl;
    if(item->parent()==nullptr){
         firstree->exec(QCursor::pos());
    }
    else{
        secondtree->exec(QCursor::pos());
    }
}

      










