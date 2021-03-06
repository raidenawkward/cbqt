#ifndef CBGLOBAL_H
#define CBGLOBAL_H

#include <QString>
#include <QStringList>
#include "cbmenuitem.h"
#include "cbdefine.h"

class CBGlobal
{
public:
    static QString getFileDir(const QString path);
    static QString getFileExt(const QString path);
    static QString getFileName(const QString path);
    static bool copyDir(const QString src, const QString dest, bool override = false);
    static bool copyFile(const QString src, const QString dest, bool override = false);
    static bool rmDir(const QString dir);
    static bool mkdir_P(const QString &dirPath);
    static QString combinePath(const QString dir, const QString file);

    static bool saveMenuItem(CBMenuItem* item);
    static bool updateMenuItem(CBMenuItem* oldItem, CBMenuItem* newItem);
    static bool removeMenuItem(CBMenuItem *item);

    static bool writeMenuItemXml(CBMenuItem* item);

    static QString getCurrentTimeStamp();
};

#endif // CBGLOBAL_H
