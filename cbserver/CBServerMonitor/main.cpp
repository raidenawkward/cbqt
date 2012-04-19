#include <QtGui/QApplication>
#include <QTextCodec>
#include "mainwindow.h"
#include "cbengine.h"

#define CB_DEFAULT_CODED "utf8"

CBEngine* initEngine();

int main(int argc, char *argv[])
{
    CBEngine *engine = initEngine();

    QApplication a(argc, argv);

    QTextCodec *tc = QTextCodec::codecForName(CB_DEFAULT_CODED);
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
