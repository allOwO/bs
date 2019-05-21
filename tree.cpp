#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::treeInit(){
    qDebug()<<"treeInit"<<endl;
    ui->treeWidget->setHeaderLabel("农作物列表");
    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeWidget,SIGNAL(customContextMenuRequested(const QPoint&)),this,SLOT(treemenuclicked(const QPoint&)));
    connect(ui->treeWidget,SIGNAL(itemClicked(QTreeWidgetItem* ,int )),this,SLOT(treeclicked(QTreeWidgetItem* ,int)));
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
    ui->treeWidget->expandAll();//展开
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
    firstree->addAction(addsecond);
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
void MainWindow::firstadd(QStringList name){
    if(operateType==Add){
        bool ok=m_pCreateDb->addfirstsql(name.value(1));
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
    QMessageBox::StandardButton button = QMessageBox::question(this , "提示" ,"确定删除分类？");
    if(button == QMessageBox::Yes){
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
        firstdlg->seteditdata(first);
    }
    firstdlg->activateWindow();
    firstdlg->setWindowTitle("重命名分类");
    firstdlg->exec();
}
void  MainWindow::firstrename(QStringList name){
    if(operateType==Edit){
        qDebug()<<"firstrename "<<name<<endl;
        bool ok=m_pCreateDb->renamefirstsql(name.value(0),name.value(1));
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
void  MainWindow::secondadd(QStringList name){
    if(operateType==Add){
        bool ok=m_pCreateDb->addsecondsql(fnameclicked.value(0),name.value(1));
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
    QTreeWidgetItem* item=ui->treeWidget->currentItem();
    QMessageBox::StandardButton button = QMessageBox::question(this , "提示" ,"确定删除这一条记录？");
    if(button == QMessageBox::Yes){
        QString second=item->text(0);
        bool ok=m_pCreateDb->deletesecondsql(second);
        if(ok){
            QMessageBox::information(this ,"提示" , "删除成功!");
        }
        else{
            QMessageBox::information(this ,"提示" , "删除失败!");
        }
        treeshow();
    }


}
//农作物重命名
void MainWindow::secondrenameclicked(){
    operateType=Edit;
    QTreeWidgetItem* item=ui->treeWidget->currentItem();
    QString second=item->text(0);
    if(second.isEmpty()){
        QMessageBox::information(this, "提示" , "请选中需要重命名的分类");
        return;
    }
    else{
        seconddlg->seteditdata(second);
    }
    seconddlg->activateWindow();
    seconddlg->setWindowTitle("重命名农作物");
    seconddlg->exec();
}
void  MainWindow::secondrename(QStringList name){
    if(operateType==Edit){
        bool ok=m_pCreateDb->renamesecondsql(name.value(0),name.value(1));
        if(ok){
            QMessageBox::information(this ,"提示" , "重命名成功!");
        }
        else{
            QMessageBox::information(this ,"提示" , "重命名失败!");
        }
    }
    treeshow();
}
//右键目录槽函数
void MainWindow::treemenuclicked(const QPoint& p){
    QTreeWidgetItem* item=ui->treeWidget->currentItem();
    qDebug()<<"treemenuclicked"<<endl;
    if(item!=nullptr){
        if(item->parent()==nullptr){
            fnameclicked=m_pCreateDb->treeonedata(item->text(0));
            firstree->exec(QCursor::pos());
        }
        else{
            snameclicked=m_pCreateDb->mainonedata(item->text(0));
            fnameclicked=m_pCreateDb->treeiddata(snameclicked.value(0));
            secondtree->exec(QCursor::pos());
        }
    }

}

      
//addtree 窗口初始化
void MainWindow::firsttreeinit()
{
    firstdlg=new addtree;
    connect(firstdlg,SIGNAL(signalsname(QStringList)),this,SLOT(firstadd(QStringList)));
    connect(firstdlg,SIGNAL(signalsname(QStringList)),this,SLOT(firstrename(QStringList)));

}
void MainWindow::secondtreeinit()
{
    seconddlg=new addtree;
    connect(seconddlg,SIGNAL(signalsname(QStringList)),this,SLOT(secondadd(QStringList)));
    connect(seconddlg,SIGNAL(signalsname(QStringList)),this,SLOT(secondrename(QStringList)));
}

