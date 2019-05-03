#ifndef ADDTREE_H
#define ADDTREE_H

#include <QWidget>

namespace Ui {
class addtree;
}

class addtree : public QWidget
{
    Q_OBJECT

public:
    explicit addtree(QWidget *parent = nullptr);
    ~addtree();
    void seteditdata(QString name);
private:
    void closeEvent(QCloseEvent *event);
    void cleardata();
private slots;
    void okbnaccepted();
    void celbnrejected();


signals:
    void signalname(QString name);
private:
    Ui::addtree *ui;
};

#endif // ADDTREE_H
