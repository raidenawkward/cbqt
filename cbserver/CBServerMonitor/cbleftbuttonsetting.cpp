#include "cbleftbuttonsetting.h"
#include <QDir>
#include <QDebug>

CBLeftButtonSetting::CBLeftButtonSetting()
{

}

CBLeftButtonSetting::CBLeftButtonSetting(const QString &path)
{
    this->setSettingPath(path);
}

bool CBLeftButtonSetting::save()
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

    writer.writeStartElement(XML_TAG_LEFT_BUTTON_LIST);

    for (int i = 0; i < _tags.count(); ++i)
    {
        writer.writeStartElement(XML_TAG_LEFT_BUTTON);
        writer.writeContent(_tags.at(i));
        writer.writeEndElement();
    }

    writer.writeEndElement();
    writer.end();

    return true;
}

bool CBLeftButtonSetting::onTagDetected(QString tag, QString content, const QXmlStreamAttributes)
{
    if (tag.toLower() == QString(XML_TAG_LEFT_BUTTON).toLower())
    {
        _tags.append(content);
    }
    else if (tag.toLower() == QString(XML_TAG_LEFT_BUTTON_LIST).toLower())
    {
        ;
    }

    return true;
}

bool CBLeftButtonSetting::load()
{
    _tags.clear();
    CBXmlReader reader(QDir::currentPath() + QString(CBPATH_SPLITOR) + this->getSettingPath());
    reader.setCallback(this);
    return reader.readAll();
}

void CBLeftButtonSetting::setTags(const QStringList &tags)
{
    _tags = tags;
}

QStringList CBLeftButtonSetting::getTags()
{
    return _tags;
}
