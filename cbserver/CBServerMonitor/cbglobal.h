#ifndef CBGLOBAL_H
#define CBGLOBAL_H

#include <QString>

#ifdef win32
    #define CBPATH_SPLITOR "\\"
#else
    #define CBPATH_SPLITOR "/"
#endif

class CBGlobal
{
public:
    static QString getFileDir(const QString path);
    static QString getFileExt(const QString path);
    static bool copyDir(const QString src, const QString dest, bool override = false);
    static bool rmDir(const QString dir);
};

#endif // CBGLOBAL_H
