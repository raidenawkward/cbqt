#include "cbdeviceappsettings.h"
#include <QDir>
#include <QDebug>

CBDeviceAppSettings::CBDeviceAppSettings()
{
}

CBDeviceAppSettings::CBDeviceAppSettings(const QString &path)
{
    this->setSettingPath(path);
}

bool CBDeviceAppSettings::save()
{
    QString settingFileDir = CBGlobal::getFileDir(this->getSettingPath());
    QDir dir(settingFileDir);

    QString xmlFile = dir.currentPath() + QString(CBPATH_SPLITOR) + this->getSettingPath();
    if (!CBGlobal::mkdir_P(CBGlobal::getFileDir(xmlFile)))
        return false;

    CBXmlWriter writer(xmlFile);
    writer.setCodec(this->getSettingCodec());

    if (!writer.start())
        return false;

    writer.writeStartElement(XML_TAG_SETTINGS);

    QList<QString> keys = _map.keys();
    for (int i = 0; i < keys.count(); ++i)
    {
        QString key = keys.at(i);
        writer.writeStartElement(key);
        writer.writeContent(_map[key]);
        writer.writeEndElement();
    }

    writer.writeEndElement();
    writer.end();

    return true;
}

bool CBDeviceAppSettings::onTagDetected(QString tag, QString content, const QXmlStreamAttributes)
{
    _map[tag] = content;
    return true;
}

bool CBDeviceAppSettings::load()
{
    _map.clear();

    CBXmlReader reader(QDir::currentPath() + QString(CBPATH_SPLITOR) + this->getSettingPath());
    reader.setCallback(this);
    return reader.readAll();
}

void CBDeviceAppSettings::set(const QString &key, const QString &value)
{
    _map.insert(key, value);
}

QString CBDeviceAppSettings::get(const QString &key)
{
    return _map.value(key);
}

void CBDeviceAppSettings::setMap(const QHash<QString, QString> &map)
{
    _map = map;
}

QHash<QString, QString>& CBDeviceAppSettings::getMap()
{
    return _map;
}
