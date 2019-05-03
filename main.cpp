#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //设置样式
    QFile file("white.qss");
    bool open_ok=file.open(QIODevice::ReadOnly | QIODevice::Text);
    qDebug()<<"file open "<< qApp->applicationDirPath() <<open_ok<<endl;
    if(open_ok)
    {
        QTextStream in(&file);
        QString style = in.readAll();
        file.close();
        qApp->setStyleSheet(style);
    }
//    QFont serifFont("Times", 12, QFont::Thin);
//    a.setFont(serifFont);
    MainWindow w;
    w.show();
    return a.exec();
}



