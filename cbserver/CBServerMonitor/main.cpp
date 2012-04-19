#include <QtGui/QApplication>
#include <QTextCodec>
#include "mainwindow.h"
#include "cbengine.h"

CBEngine* initEngine();

int main(int argc, char *argv[])
{
    CBEngine *engine = initEngine();

    QApplication a(argc, argv);

    QTextCodec *tc = QTextCodec::codecForName("utf8");
    QTextCodec::setCodecForCStrings(tc);
    QTextCodec::setCodecForTr(tc);

    MainWindow w;
    w.setEngine(engine);
    w.show();
    
    return a.exec();
}

CBEngine* initEngine()
{
    CBEngine *engine = new CBEngine();
    engine->loadMenuItems(CBSERVERMONITOR_DISHES_DIR);

    return engine;
}
