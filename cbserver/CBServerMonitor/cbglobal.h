#ifndef CBGLOBAL_H
#define CBGLOBAL_H

#include <QString>
#include "cbmenuitem.h"

#define CBSERVERMONITOR_DISHES_DIR "dishes"

#define CB_DEFAULT_UI_CODED "utf8"

#ifdef WIN32
    #define CB_DEFAULT_XML_CODED "gb2312"
#else
    #define CB_DEFAULT_XML_CODED "gb2312"
#endif

#ifdef WIN32
    #define CBPATH_SPLITOR "/"
#else
    #define CBPATH_SPLITOR "/"
#endif

class CBGlobal
{
public:
    static QString getFileDir(const QString path);
    static QString getFileExt(const QString path);
    static QString getFileName(const QString path);
    static bool copyDir(const QString src, const QString dest, bool override = false);
    static bool rmDir(const QString dir);
    static QString combinePath(const QString dir, const QString file);

    static bool saveMenuItem(CBMenuItem* item);
    static bool updateMenuItem(CBMenuItem* oldItem, CBMenuItem* newItem);
    static bool removeMenuItem(CBMenuItem *item);

    static bool writeMenuItemXml(CBMenuItem* item);
};

#endif // CBGLOBAL_H
