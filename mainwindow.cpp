#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("单机版农作物管理系统");
    setWindowState(Qt::WindowMaximized);
    setWindowIcon(QIcon(":/i/nzw.png"));
//    setMinimumSize(1440,900);

    ui->addbn->setIcon(QIcon(":/icon/plus.png"));
    m_pCreateDb = new CreateDb;
    m_pCreateDb->initDB();
    righttreemenuinit();//右键菜单初始化
    operateType = Add;
    firsttreeinit();//addtree窗口初始化
    secondtreeinit();
    treeInit();//初始树并显示，放到后边
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::close(){

}

void MainWindow::add(){

}
