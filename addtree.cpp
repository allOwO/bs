#include "addtree.h"
#include "ui_addtree.h"

addtree::addtree(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addtree)
{
    ui->setupUi(this);
    setFixedSize(390,92);
     setWindowIcon(QIcon(":/i/info2.png"));
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    connect(ui->okbn,SIGNAL(clicked()),this,SLOT(okbnaccepted()));
    connect(ui->celbn,SIGNAL(clicked()),this,SLOT(celbnrejected()));
}

addtree::~addtree()
{
    delete ui;
}

void addtree::closeEvent(QCloseEvent *event)
{
    ui->lineEdit->clear();
}
//点击完成后接收
void addtree::okbnaccepted(){
    QStringList name;
    name.append(oldname);
    name.append(ui->lineEdit->text());
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
    oldname=name;
}
