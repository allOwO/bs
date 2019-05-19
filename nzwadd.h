#ifndef NZWADD_H
#define NZWADD_H

#include <QDialog>
#include <QVariantMap>
namespace Ui {
class nzwadd;
}

class nzwadd : public QDialog
{
    Q_OBJECT
public:
    explicit nzwadd(QWidget *parent = nullptr);
    ~nzwadd();
    void seteditdata(QVariantMap);
    void setadddata(QVariantMap);
    void closeEvent(QCloseEvent *event);
    QString thisaddtime;
    QString thisname;
private:
    void cleardata();
private slots:
    void okbnaccepted();
    void celbnrejected();
    void toolclicked();
signals:
    void emitadd(QVariantMap);
private:
    Ui::nzwadd *ui;
};

#endif // NZWADD_H
