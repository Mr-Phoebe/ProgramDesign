#include <QApplication>
#include <QFont>
#include <vector>
#include <QTimer>
#include <QDateTime>
#include <QTextCodec>
#include "mainWindow.h"
#include "io.h"
#include "log.h"

MainWindow* w;

int main(int argc, char* argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf8"));
    QApplication a(argc, argv);
    QFont font("Microsoft YaHei", 10);
    a.setFont(font);
    w = new MainWindow();
    w->show();
    return a.exec();
}
