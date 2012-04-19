#ifndef CBGLOBAL_H
#define CBGLOBAL_H

#include <QString>

#ifdef win32
    #define CBPATH_SPLITOR "\\"
#else
    #define CBPATH_SPLITOR "/"
#endif

QString getFileDir(const QString path);
QString getFileExt(const QString path);

#endif // CBGLOBAL_H
