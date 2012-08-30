#include "cbglobal.h"
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QFileInfoList>
#include <QStringList>
#include <QDebug>

#include "cbxmlwriter.h"
#include "cbdish.h"

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

QString CBGlobal::getFileName(const QString path)
{
    int index = path.lastIndexOf(CBPATH_SPLITOR) + 1;

    if (index == -1)
        return path;
    return path.mid(index);
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
            continue;
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

bool CBGlobal::mkdir_P(const QString &dirPath)
{
    QStringList dirs = dirPath.split(CBPATH_SPLITOR);
    QDir dir(dirs.at(0));
    QString current = dir.currentPath();
    for (int i = 0; i < dirs.count(); ++i)
    {
        current += QString(CBPATH_SPLITOR) + dirs.at(i);
        if (!dir.exists())
        {
            if (!dir.mkdir(current))
            {
                return false;
            }
        }
    }

    return true;
}

QString CBGlobal::combinePath(const QString dir, const QString file)
{
    QString res;
    res += dir;
    res += QString(CBPATH_SPLITOR);
    res += file;

    return res;
}

bool CBGlobal::saveMenuItem(CBMenuItem* item)
{
    if (!item)
        return false;

    QDir itemDir(item->getRecordDir());
    if (!itemDir.exists())
    {
        itemDir.mkdir(item->getRecordDir());
    }

    QFile fileThumb(item->getDish().getThumb());
    if (!fileThumb.exists())
        return false;

    if (fileThumb.copy(item->getRecordDir() + QString(CBPATH_SPLITOR) + fileThumb.fileName()))
    {
        item->getDish().setThumb(fileThumb.fileName());
    }
    else
    {
        return false;
    }

    QFile filePicture(item->getDish().getThumb());
    if (!filePicture.exists())
        return false;

    if (filePicture.copy(item->getRecordDir() + QString(CBPATH_SPLITOR) + filePicture.fileName()))
    {
        item->getDish().setThumb(filePicture.fileName());
    }
    else
    {
        return false;
    }

    return writeMenuItemXml(item);
}

bool CBGlobal::updateMenuItem(CBMenuItem* oldItem, CBMenuItem* newItem)
{
    if (!oldItem || !newItem)
        return false;

    QString oldThumb = oldItem->getRecordDir() + QString(CBPATH_SPLITOR) + oldItem->getDish().getThumb();
    QString oldPicture = oldItem->getRecordDir() + QString(CBPATH_SPLITOR) + oldItem->getDish().getPicture();

    QString newThumb = newItem->getDish().getThumb();
    QString newPicture = newItem->getDish().getThumb();

    if (oldThumb != newThumb)
    {
        QFile file(newThumb);
        if (!file.exists())
            return false;
        if (file.copy(newItem->getRecordDir() + QString(CBPATH_SPLITOR) + file.fileName()))
        {
            QFile(oldThumb).remove();
            oldItem->getDish().setThumb(file.fileName());
        }
        else
        {
            return false;
        }
    }

    if (oldPicture != newPicture)
    {
        QFile file(newPicture);
        if (!file.exists())
            return false;
        if (file.copy(newItem->getRecordDir() + QString(CBPATH_SPLITOR) + file.fileName()))
        {
            QFile(oldPicture).remove();
            oldItem->getDish().setPicture(file.fileName());
        }
        else
        {
            return false;
        }
    }

    return writeMenuItemXml(newItem);
}

bool CBGlobal::removeMenuItem(CBMenuItem *item)
{
    if (!item)
        return false;

    return rmDir(item->getRecordDir());
}

bool CBGlobal::writeMenuItemXml(CBMenuItem* item)
{
    if (!item)
        return false;

    qDebug()<<item->getRecordDir() + QString(CBPATH_SPLITOR) + item->getRecordFile();
    CBXmlWriter writer(item->getRecordDir() + QString(CBPATH_SPLITOR) + item->getRecordFile());
    writer.setCodec(CB_DEFAULT_XML_CODED);
    if (!writer.start())
        return false;

    writer.writeStartElement(CBDISH_TAG_DISH);

    writer.writeStartElement(CBDISH_TAG_ID);
    writer.writeContent(item->getDish().getId().toString());
    writer.writeEndElement();

    writer.writeStartElement(CBDISH_TAG_NAME);
    writer.writeContent(item->getDish().getName());
    writer.writeEndElement();

    writer.writeStartElement(CBDISH_TAG_PRICE);
    writer.writeContent(QString::number(item->getDish().getPrice()));
    writer.writeEndElement();

    writer.writeStartElement(CBDISH_TAG_SCORE);
    writer.writeContent(QString::number(item->getDish().getScore()));
    writer.writeEndElement();

    writer.writeStartElement(CBDISH_TAG_TAGS);
    QStringList tags = item->getDish().getTags();
    for (int i = 0; i < tags.count(); ++i)
    {
        writer.writeStartElement(CBDISH_TAG_TAG);
        writer.writeContent(tags.at(i));
        writer.writeEndElement();
    }
    writer.writeEndElement();

    writer.writeStartElement(CBDISH_TAG_SUMMARIZE);
    writer.writeContent(item->getDish().getSummary());
    writer.writeEndElement();

    writer.writeStartElement(CBDISH_TAG_DETAIL);
    writer.writeContent(item->getDish().getDetail());
    writer.writeEndElement();

    writer.writeStartElement(CBDISH_TAG_THUMB);
    writer.writeContent(item->getDish().getThumb());
    writer.writeEndElement();

    writer.writeStartElement(CBDISH_TAG_PICTURE);
    writer.writeContent(item->getDish().getPicture());
    writer.writeEndElement();

    writer.writeEndElement();
    writer.end();

    return true;
}
