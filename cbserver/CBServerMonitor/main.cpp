#include <QtGui/QApplication>
#include <QTextCodec>
#include "mainwindow.h"
#include "cbglobal.h"
#include "cbengine.h"

CBEngine* initEngine();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qApp->addLibraryPath(CB_PLUGING_PATH);
    qApp->addLibraryPath("plugins/codecs");

    QTextCodec *tc = QTextCodec::codecForName(CB_DEFAULT_UI_CODED);
    QTextCodec::setCodecForCStrings(tc);
    QTextCodec::setCodecForTr(tc);
    QTextCodec::setCodecForLocale(tc);

    CBEngine *engine = initEngine();

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
