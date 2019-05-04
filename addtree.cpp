#include "addtree.h"
#include "ui_addtree.h"

addtree::addtree(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::addtree)
{
    ui->setupUi(this);
    setFixedSize(390,100);
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    connect(ui->okbn,SIGNAL(clicked()),this,SLOT(okbnaccepted()));
    connect(ui->celbn,SIGNAL(clicked()),this,SLOT(celbnrejected()));
}

addtree::~addtree()
{
    delete ui;
}

void addtree::cleardata(){
    ui->lineEdit->clear();
}
void addtree::closeEvent(QCloseEvent *event)
{
    cleardata();
}
//点击完成后接收
void addtree::okbnaccepted(){
    qDebug()<<"okbnaccepted"<<endl;
    QString name=ui->lineEdit->text();
    emit signalsname(name);//传值，槽函数响应
    ui->lineEdit->setEnabled(true);
    close();
}
void addtree::celbnrejected(){

    qDebug()<<"celbnrejected"<<endl;
    ui->lineEdit->setEnabled(true);
    close();
}
void addtree::seteditdata(QString name){
    ui->lineEdit->setText(name);
}
