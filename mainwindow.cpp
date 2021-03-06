﻿#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("单机版农作物图像数据库系统");
//    setWindowState(Qt::WindowMaximized);
    setWindowIcon(QIcon(":/i/nzw.png"));
//    setMinimumSize(1440,900);
    setFixedSize(1440,900);
    ui->addbn->setIcon(QIcon(":/icon/plus.png"));
    m_pCreateDb = new CreateDb;
    m_pCreateDb->initDB();
    righttreemenuinit();//右键菜单初始化
    operateType = Add;
    inpath="./";
    outpath="./";
    firsttreeinit();//addtree窗口初始化
    secondtreeinit();
    nzwaddinit();//图像添加窗口初始化
    tableinit();
    findinit();
    treeInit();
    treeshow();//初始树并显示，放到后边
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::treeclicked(QTreeWidgetItem* item,int col){
   qDebug()<<"treeclicked()"<<endl;
   if(item!=nullptr){
       if(item->parent()!=nullptr){
           snameclicked=m_pCreateDb->mainonedata(item->text(0));
           fnameclicked=m_pCreateDb->treeiddata(snameclicked.value(0));
           tableshow(item->text(0));
       }
       else{
           fnameclicked=m_pCreateDb->treeonedata(item->text(0));
       }
   }
}
void MainWindow::tableshow(QString name){
   cleartabledata();
   int num=ui->cbox->currentIndex();
   QString findstr=ui->findline->text();
   QList<tabledata> line;
   if(findstr.size()==0){
        line=m_pCreateDb->tableline(name);
   }
   else{
        line=m_pCreateDb->findline(name,num,findstr);
   }
   if(num==0){
       qSort(line.begin(),line.end(),[](const tabledata &s1,const tabledata &s2){return s1.addtime<s2.addtime;});
   }
   else if(num==1){
       qSort(line.begin(),line.end(),[](const tabledata &s1,const tabledata &s2){return s1.shootime<s2.shootime;});
   }
   else if(num==2){
       qSort(line.begin(),line.end(),[](const tabledata &s1,const tabledata &s2){return s1.place<s2.place;});
   }
   else{
       qSort(line.begin(),line.end(),[](const tabledata &s1,const tabledata &s2){return s1.region<s2.region;});
   }
   tablelinedata=line;//当前列表保存
   if(!line.isEmpty()){
       ui->findbn->setEnabled(true);
       ui->takeout->setEnabled(true);
       ui->changebn->setEnabled(true);
       ui->deletebn->setEnabled(true);
       for(auto it=line.begin();it!=line.end();it++){
                settabledata(*it);
      }
   }
   else{
       ui->findbn->setEnabled(false);
       ui->takeout->setEnabled(false);
       ui->changebn->setEnabled(false);
       ui->deletebn->setEnabled(false);
   }
}
void MainWindow::settabledata(tabledata data){
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);

    QString value1=QString("名称：      %1\n拍摄时间：%2\n拍摄地点：%3\n所属分类：%4\n拍摄角度：%5").arg(data.name).arg(data.shootime).arg(data.place).arg(data.wherefrom).arg(data.region);
    QLabel *label1=new QLabel;
    label1->setText(value1);
    label1->setFont(QFont( "Microsoft YaHei", 12,50));
    ui->tableWidget->setCellWidget(row,0,label1);

    QImage image2,image;
    image2.loadFromData(data.image);
    image=image2.scaled(600,397, Qt::KeepAspectRatio);
//    QPixmap image;
//    image.loadFromData(data.image);
//    QPixmap imagesmall=image.scaled(600,397, Qt::KeepAspectRatio/*, Qt::SmoothTransformation*/);
    QLabel *label2=new QLabel;
    label2->resize(600,400);
    label2->setAlignment(Qt::AlignCenter);
    label2->setPixmap(QPixmap::fromImage(image));
    ui->tableWidget->setCellWidget(row,1,label2);
}
void MainWindow::cleartabledata(){
    int rowCount = ui->tableWidget->rowCount();
    for(int r = rowCount-1 ; r >=0 ; r--)
    {
        ui->tableWidget->removeRow(r);
    }
}
void MainWindow::tableinit(){
    qDebug()<<"tableinit"<<endl;
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() <<"信息" <<"图片");
    ui->tableWidget->horizontalHeader()->resizeSection(0,250);//0列宽度
    ui->tableWidget->verticalHeader()->setVisible(false);//行头不可见
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(400);//0行宽度
    ui->tableWidget->setFrameShape(QFrame::NoFrame); //设置无边框
    ui->tableWidget->setShowGrid(false); //设置不显示格子线
    ui->tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);//不能多选

    ui->tableWidget->resizeRowsToContents();//自适应行宽
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//选一个选一行
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑
    ui->tableWidget->horizontalHeader()->setHighlightSections(false);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    connect(ui->addbn,SIGNAL(clicked()),this,SLOT(addbnclicked()));
    connect(ui->changebn,SIGNAL(clicked()),this,SLOT(changeclicked()));
    connect(ui->takeout,SIGNAL(clicked()),this,SLOT(takeoutclicked()));
    connect(ui->deletebn,SIGNAL(clicked()),this,SLOT(deleteclicked())); 
    connect(ui->tableWidget,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(imageclick()));
    connect(ui->inpathaction,SIGNAL(triggered()),this,SLOT(inpathclicked()));
    connect(ui->outpathaction,SIGNAL(triggered()),this,SLOT(outpathclicked()));
}
void MainWindow::findinit(){
    qDebug()<<"findinit"<<endl;
    ui->cbox->addItem("添加时间");
    ui->cbox->addItem("拍摄时间");
    ui->cbox->addItem("地点");
    ui->cbox->addItem("拍摄角度");
    connect(ui->findbn,SIGNAL(clicked()),this,SLOT(findclicked()));
}
void MainWindow::nzwaddinit(){
    nzwadddlg=new nzwadd;
    connect(nzwadddlg,SIGNAL(emitadd(QVariantMap)),this,SLOT(addimage(QVariantMap)));
    connect(nzwadddlg,SIGNAL(emitadd(QVariantMap)),this,SLOT(changeimage(QVariantMap)));
}

//增加按钮点击槽函数
void MainWindow::addbnclicked(){ 
    nzwtype=Add;
    if(nzwadddlg){
        QVariantMap info;
        info.insert("name",snameclicked.value(1));
        info.insert("from",fnameclicked.value(1));
        nzwadddlg->setadddata(info);
        nzwadddlg->activateWindow();
        nzwadddlg->setWindowTitle("添加图像信息");
        nzwadddlg->exec();

    }
}
//修改按钮点击槽函数
void MainWindow::changeclicked(){
    nzwtype=Edit;
    tabledata thislinedata=getrowdata();
    if (thislinedata.name.size()==0){
          QMessageBox::information(this,"提示","请选择需要编辑的指针");
          return ;
    }
    else{
         QVariantMap info=tabledataturnMap(thislinedata);
         nzwadddlg->seteditdata(info);
    }
    nzwadddlg->activateWindow();
    nzwadddlg->setWindowTitle("修改图像信息");
    nzwadddlg->exec();

}
//得到当前行数据
tabledata MainWindow::getrowdata(){
    tabledata data;
    int row =ui->tableWidget->currentRow();
    if(row>=0){
        data=tablelinedata[row];
    }
    return data;
}
void MainWindow::deleteclicked(){
    tabledata thislinedata=getrowdata();
    if (thislinedata.name.size()==0){
          QMessageBox::information(this,"提示","请选择需要编辑的指针");
          return ;
    }
    QMessageBox::StandardButton button = QMessageBox::question(this , "提示" ,"确定删除这一条记录？");
    if(button == QMessageBox::Yes){
        m_pCreateDb->deletenzwimage(tabledataturnMap(thislinedata));
    }
    treeshow();
    tableshow(thislinedata.name);
}
//tabledata转换成Map
QVariantMap MainWindow::tabledataturnMap(tabledata data){
    QVariantMap info;
    info.insert("name",data.name);
    info.insert("shootime",data.shootime);
    info.insert("addtime",data.addtime);
    info.insert("place",data.place);
    info.insert("region",data.region);
    info.insert("from",data.wherefrom);
    info.insert("image",data.image);
    info.insert("imagesuffix",data.imagesuffix);
    return info;
}
void MainWindow::takeoutclicked(){
    if(tablelinedata.isEmpty()==false){
        QString savefilepath=QFileDialog::getExistingDirectory(this,"选择保存路径",outpath);
        if(savefilepath.size()==0){
            return ;
        }
        bool ok=false;
        auto it=tablelinedata.begin();
        for(;it!=tablelinedata.end();it++)
        {
            QImage image;
            image.loadFromData((*it).image);
            //路径中不能有冒号
            QString path=QString("%1/%2%3-%4.%5").arg(savefilepath).arg((*it).shootime).arg((*it).name).arg((*it).addtime.replace(" ","").replace(":","")).arg((*it).imagesuffix);
            qDebug()<<"takeout2"<<(*it).imagesuffix<<path<<endl;
            ok=image.save(path);
            if(!ok){
                QMessageBox::information(this,"提示","导出失败");
                return;
            }
        }
        if(ok){
            QMessageBox::information(this,"提示","导出成功");
        }

    }
}
//添加窗口返回后处理
void MainWindow::addimage(QVariantMap info){
    if(nzwtype==Add){
        bool ok= m_pCreateDb->addnzwimage(info);
        if(ok){
            QMessageBox::information(this,"提示","添加成功");
        }
        else{
            QMessageBox::information(this,"提示","添加失败");
        }
    }
    treeshow();
    tableshow(info.value("name").toString());
}
//修改窗口返回后处理
void MainWindow::changeimage(QVariantMap info){
    qDebug()<<"changeimage "<<endl;
    if(nzwtype==Edit){
        bool ok= m_pCreateDb->changenzwimage(info);
        if(ok){
            QMessageBox::information(this,"提示","修改成功");
        }
        else{
            QMessageBox::information(this,"提示","修改失败");
        }
    }
    treeshow();
    tableshow(info.value("name").toString());
}
void MainWindow::findclicked(){
    tableshow(snameclicked.value(1));
}
void MainWindow::imageclick(){
    qDebug()<<"imageclick"<<endl;
    tabledata thislinedata=getrowdata();
    if(tablelinedata.isEmpty()==false){
        QString imagename=QString("%1%2-%3.%4").arg(thislinedata.name).arg(thislinedata.shootime).arg(thislinedata.addtime.replace(" ","").replace(":","")).arg(thislinedata.imagesuffix);
        QString savefilepath=QFileDialog::getSaveFileName(this,"选择保存路径",outpath+"/"+imagename,"*."+thislinedata.imagesuffix);
        if(savefilepath.size()==0){
            return;
        }
        bool ok=false;
        auto it=tablelinedata.begin();
        for(;it!=tablelinedata.end();it++)
        {
            QImage image;
            image.loadFromData(thislinedata.image);
            //路径中不能有冒号
            qDebug()<<"takeout2"<<(*it).imagesuffix<<savefilepath<<endl;
            ok=image.save(savefilepath);
            if(!ok){
                QMessageBox::information(this,"提示","导出失败");
                return;
            }
        }
        if(ok){
            QMessageBox::information(this,"提示","导出成功");
        }

    }
}
void MainWindow::inpathclicked(){
    QString savefilepath=QFileDialog::getExistingDirectory(this,"选择保存路径",inpath);
    if(savefilepath.size()!=0){
        inpath=savefilepath;
        QFile file("inpath.txt");
        file.open(QIODevice::WriteOnly);
        QTextStream in(&file);
        in<<inpath;
        file.close();
    }
}
void MainWindow::outpathclicked(){
    QString savefilepath=QFileDialog::getExistingDirectory(this,"选择保存路径",outpath);
    if(savefilepath.size()!=0){
        outpath=savefilepath;
        QFile file("outpath.txt");
        file.open(QIODevice::WriteOnly);
        QTextStream in(&file);
        in<<outpath;
        file.close();
    }
}
