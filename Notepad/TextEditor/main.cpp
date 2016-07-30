#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*让程序支持中文*/
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    MainWindow w;
    w.show();

    return a.exec();
}
