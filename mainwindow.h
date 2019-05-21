#ifndef MAINWINDOW_H
#define MAINWINDOW_H
/*2019.5.1 from 刘梓旭
*/
#include <QMainWindow>
#include <QDialog>
#include <QtDebug>
#include <QMessageBox>
#include <QTreeWidget>
#include <QPixmap>
#include <QLabel>
#include <QComboBox>
#include<QFileDialog>
#include <QBuffer>
#include "createdb.h"
#include "addtree.h"
#include "nzwadd.h"
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
    QVariantMap tabledataturnMap(tabledata);
private:
    Ui::MainWindow *ui;
    CreateDb *m_pCreateDb;
    void DbInit();
    void show_list();
    void DbCreatetable(QString);
    void create_table(QString);
    void treeshow();
    void tableshow(QString);
    void settabledata(tabledata);
    void cleartabledata();
    tabledata getrowdata();

    void treeInit();
    void righttreemenuinit();
    void firsttreeinit();
    void secondtreeinit(); 
    void tableinit();
    void findinit();
    void nzwaddinit();
private slots:
    void treeclicked(QTreeWidgetItem* ,int);

    void firstadd(QStringList);//dialog窗口 返回后处理
    void firstaddclicked();
    void firstdeleteclicked();
    void firstrename(QStringList);
    void firstrenameclicked();

    void secondadd(QStringList);
    void secondaddclicked();
    void seconddeleteclicked();
    void secondrename(QStringList);
    void secondrenameclicked();

    void treemenuclicked(const QPoint&);//右键点SLOT;
    void addbnclicked();
    void changeclicked();
    void deleteclicked();
    void takeoutclicked();
    void addimage(QVariantMap);
    void changeimage(QVariantMap);
    void findclicked();
    void imageclick();

    void outpathclicked();
    void inpathclicked();
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
    QStringList fnameclicked,snameclicked;//被右键选中
    QList<tabledata> tablelinedata;
    QString inpath,outpath;
private:
    addtree *firstdlg;
    addtree *seconddlg;
    nzwadd *nzwadddlg;
    OperateType operateType;
    OperateType nzwtype;

};
#endif // MAINWINDOW_H
class ClickLabel :public QLabel{
    Q_OBJECT
public:
    explicit ClickLabel(QWidget * parent = 0);
    ~ClickLabel();
private:
    void mouseReleaseEvent(QMouseEvent *e);
signals:
    void clicked();
};
