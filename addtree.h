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
    explicit addtree(QDialog *parent = nullptr);
    ~addtree();
    void seteditdata(QString );
private:
    void closeEvent(QCloseEvent *event);
    void cleardata();
private slots:
    void okbnaccepted();
    void celbnrejected();
signals:
    void signalsname(QString);
private:
    Ui::addtree *ui;
};

#endif // ADDTREE_H
