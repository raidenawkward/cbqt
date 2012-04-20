#include "cbglobal.h"
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QFileInfoList>
#include <QDebug>

QString CBGlobal::getFileDir(const QString path)
{
    int index = path.lastIndexOf(CBPATH_SPLITOR) + 1;

    if (index == -1)
        return path;

    return path.mid(0, index);
}

QString CBGlobal::getFileExt(const QString path)
{
    int index = path.lastIndexOf(".");

    if (index == -1)
        return QString();

    return path.mid(index + 1);
}

bool CBGlobal::copyDir(const QString src, const QString dest, bool override)
{
    QDir dirSrc(src);
    QDir dirDest(dest);

    if (!dirDest.exists())
    {
        if (!dirDest.mkdir(dest))
            return false;
    }

    QFileInfoList srcList = dirSrc.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden);
    for (int i = 0; i < srcList.count(); ++i)
    {
        QFileInfo info = srcList.at(i);
        if (info.isDir())
        {
            if (!copyDir(info.absoluteFilePath(), dirDest.filePath(info.fileName()), override))
                return false;
        }

        if (info.isFile() || info.isSymLink())
        {
            if (override && dirDest.exists(info.fileName()))
            {
                dirDest.remove(info.fileName());
            }

            if (!QFile::copy(info.filePath(),
                             dirDest.filePath(info.fileName())))
                return false;
        }
    }

    return true;
}

bool CBGlobal::rmDir(const QString dir)
{
    QDir directory(dir);

    if (!directory.exists())
        return false;

    QFileInfoList infoList = directory.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden);
    for (int i = 0; i < infoList.count(); ++i)
    {
        QFileInfo info = infoList.at(i);

        if (info.isFile() || info.isSymLink())
        {
            QFile::remove(info.absoluteFilePath());
        }

        if (info.isDir())
        {
            if (!rmDir(info.absoluteFilePath()))
                return false;
        }
    }

    return directory.rmdir(QDir::convertSeparators(directory.path()));
}
