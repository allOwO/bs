#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QtDebug>
#include <QMessageBox>
#include <QTreeWidget>
#include <QTreeView>
#include <QContextMenuEvent>
#include "createdb.h"
#include "addtree.h"
#pragma execution_character_set("utf-8")
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

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
private slots:
    void treeclicked(QTreeWidgetItem* ,int);
    void treemainclicked(QTreeWidgetItem* ,int);
    void firstaddclicked();
    void firstdeleteclicked();
    void firstrenameclicked();
    void secondaddclicked();
    void seconddeleteclicked();
    void secondrenameclicked();
    void treemenuclicked(const QPoint&);
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
//  widget
    addtree *adddlg;

};
#endif // MAINWINDOW_H
