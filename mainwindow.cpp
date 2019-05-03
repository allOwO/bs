#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("单机版农作物管理系统");
    setWindowState(Qt::WindowMaximized);
//    setMinimumSize(1440,900);

    ui->addbn->setIcon(QIcon(":/icon/plus.png"));
    m_pCreateDb = new CreateDb;
    m_pCreateDb->initDB();
    treeInit();

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::close(){
    QApplication* app;
    app->exit(0);
}

void MainWindow::add(){

}
