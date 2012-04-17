#include <QtGui/QApplication>
#include <QTextCodec>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec *tc = QTextCodec::codecForName("utf8");
    QTextCodec::setCodecForCStrings(tc);
    QTextCodec::setCodecForTr(tc);

    MainWindow w;
    w.show();
    
    return a.exec();
}
