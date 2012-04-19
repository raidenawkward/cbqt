#include "cbglobal.h"

QString getFileDir(const QString path)
{
    int index = path.lastIndexOf(CBPATH_SPLITOR) + 1;

    if (index == -1)
        return path;

    return path.mid(0, index);
}

QString getFileExt(const QString path)
{
    int index = path.lastIndexOf(".");

    if (index == -1)
        return QString();

    return path.mid(index + 1);
}
