#include "cblocationsettings.h"
#include <QDir>

CBLocationSettings::CBLocationSettings()
{
}

CBLocationSettings::CBLocationSettings(const QString &path)
{
    this->setSettingPath(path);
}

bool CBLocationSettings::save()
{
    QString settingFileDir = CBGlobal::getFileDir(this->getSettingPath());
    if (!CBGlobal::mkdir_P(settingFileDir))
        return false;

    CBXmlWriter writer(QDir::currentPath() + QString(CBPATH_SPLITOR) + this->getSettingPath());
    writer.setCodec(this->getSettingCodec());

    if (!writer.start())
        return false;

    writer.writeStartElement(XML_TAG_ORDER_LOCATION_LIST);

    for (int i = 0; i < _tags.count(); ++i)
    {
        writer.writeStartElement(XML_TAG_ORDER_LOCATION);
        writer.writeContent(_tags.at(i));
        writer.writeEndElement();
    }

    writer.writeEndElement();
    writer.end();

    return true;
}

bool CBLocationSettings::onTagDetected(QString tag, QString content, const QXmlStreamAttributes)
{
    if (tag.toLower() == QString(XML_TAG_ORDER_LOCATION).toLower())
    {
        _tags.append(content);
    }
    else if (tag.toLower() == QString(XML_TAG_ORDER_LOCATION_LIST).toLower())
    {
        ;
    }

    return true;
}

bool CBLocationSettings::load()
{
    _tags.clear();
    CBXmlReader reader(QDir::currentPath() + QString(CBPATH_SPLITOR) + this->getSettingPath());
    reader.setCallback(this);
    return reader.readAll();
}

void CBLocationSettings::setTags(const QStringList &tags)
{
    _tags = tags;
}

QStringList CBLocationSettings::getTags()
{
    return _tags;
}
