#ifndef MAINWINDOW_H
#define MAINWINDOW_H
/*2019.5.1 from 刘梓旭
*/
#include <QMainWindow>
#include <QDialog>
#include <QtDebug>
#include <QMessageBox>
#include <QTreeWidget>
#include "createdb.h"
#include "addtree.h"
#pragma execution_character_set("utf-8")
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


    enum OperateType
    {
        Add ,
        Edit
    };
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    CreateDb *m_pCreateDb;
    void DbInit();
    void show_list();
    void DbCreatetable(QString);
    void create_table(QString);
    void treeshow();
    void treeInit();
    void righttreemenuinit();
    void firsttreeinit();
    void secondtreeinit();
private slots:
    void treeclicked(QTreeWidgetItem* ,int);
    void treemainclicked(QTreeWidgetItem* ,int);
    void firstadd(QString);//dialog窗口 返回后处理
    void firstaddclicked();
    void firstdeleteclicked();
    void firstrename(QString);
    void firstrenameclicked();
    void secondadd(QString);
    void secondaddclicked();
    void seconddeleteclicked();
    void secondrename(QString);
    void secondrenameclicked();
    void treemenuclicked(const QPoint&);//右键点SLOT;
    void add();
    void close();
//tree右键菜单
private:
    QMenu *firstree;
    QAction *addfirst;
    QAction *deletefirst;
    QAction *renamefirst;
    QMenu *secondtree;
    QAction *addsecond;
    QAction *deletesecond;
    QAction *renamesecond;
    QMenu *blank;
//  addtree
public:
    QString nameclicked;//被右键选中
private:
    addtree *firstdlg;
    addtree *seconddlg;
    OperateType operateType;

};
#endif // MAINWINDOW_H
