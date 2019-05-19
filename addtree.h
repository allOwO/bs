#ifndef ADDTREE_H
#define ADDTREE_H

#include <QDialog>
#include<QtDebug>
namespace Ui {
class addtree;
}

class addtree : public QDialog
{
    Q_OBJECT

public:
    explicit addtree(QWidget *parent = nullptr);
    ~addtree();
    void seteditdata(QString );
    QString oldname;
private:
    void closeEvent(QCloseEvent *event);
private slots:
    void okbnaccepted();
    void celbnrejected();
signals:
    void signalsname(QStringList);
private:
    Ui::addtree *ui;
};

#endif // ADDTREE_H
