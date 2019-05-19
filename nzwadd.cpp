#include "nzwadd.h"
#include "ui_nzwadd.h"
#include <QDateTime>
#include <QStringList>
#include <QString>
#include <QDebug>
#include<QFileDialog>
nzwadd::nzwadd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::nzwadd)
{
    ui->setupUi(this);
    setWindowTitle("添加图像");
    setWindowIcon(QIcon(":/i/info.png"));
    setFixedSize(315,285);
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    ui->dateedit->setDisplayFormat("yyyy-MM-dd");
    connect(ui->okbn,SIGNAL(clicked()),this,SLOT(okbnaccepted()));
    connect(ui->celbn,SIGNAL(clicked()),this,SLOT(celbnrejected()));
    connect(ui->toolbn,SIGNAL(clicked()),this,SLOT(toolclicked()));
}
nzwadd::~nzwadd()
{
    delete ui;
}
//ok槽函数
void nzwadd::okbnaccepted(){
    qDebug()<<"okbnaccepted"<<endl;
    QVariantMap info;
    QString name=ui->lename->text();
    QString shootime=ui->dateedit->text();
    QString place=ui->leplace->text();
    QString region=ui->leregion->text();
    QString from=ui->lefrom->text();
    QString path=ui->path->text();
    info.insert("name",name);
    info.insert("shootime",shootime);
    info.insert("place",place);
    info.insert("region",region);
    info.insert("from",from);
    info.insert("path",path);
    info.insert("oldname",thisname);
    if(thisaddtime.size()>0)
        info.insert("addtime",thisaddtime);
    emit emitadd(info);//传值，槽函数响应
    close();
}
void nzwadd::celbnrejected(){

    qDebug()<<"celbnrejected"<<endl;
    close();
}
void nzwadd::seteditdata(QVariantMap info){
    ui->lename->setText(info.value("name").toString());
    ui->dateedit->setDateTime(QDateTime::fromString(info.value("shootime").toString(), "yyyy-MM-dd"));
    ui->lefrom->setText(info.value("from").toString());
    ui->lefrom->setEnabled(false);
    ui->lefrom->setStyleSheet("background-color: #BEBEBE;");
    ui->leplace->setText(info.value("place").toString());
    ui->leregion->setText(info.value("region").toString());
    ui->path->setEnabled(false);
    ui->path->setStyleSheet("background-color: #BEBEBE;");//设置样式浅灰色不可选取
    thisaddtime=info.value("addtime").toString();
    thisname=info.value("name").toString();
    ui->toolbn->setDisabled(true);//工具按钮不可点击
}
void nzwadd::setadddata(QVariantMap info){
    ui->lename->setText(info.value("name").toString());
    ui->lefrom->setText(info.value("from").toString());
}

void nzwadd::toolclicked(){
 QString imagepath=QFileDialog::getOpenFileName(this,"打开图像","/","图片(*.png *.jpg *.jpeg *.bmp)");
 ui->path->setText(imagepath);
}

void nzwadd::closeEvent(QCloseEvent *event)
{
     ui->lename->clear();
     ui->dateedit->clear();
     ui->lefrom->clear();
     ui->leplace->clear();
     ui->path->clear();
     ui->leregion->clear();
}
