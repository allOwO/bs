#include "addtree.h"
#include "ui_addtree.h"

addtree::addtree(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addtree)
{
    ui->setupUi(this);
    setFixedSize(440,120);
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
    clearData();
}
void addtree::okbnaccepted(){
    QString name=ui->lineEdit->text();
    emit signalname(name);
    ui->lineEdit->setEnabled(true);
}
void addtree::celbnrejected(){
    ui->lineEdit->setEnabled(true);
    close();
}
void addtree::seteditdata(QString name){
    ui->lineEdit->setText(name);
}
