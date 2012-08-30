#ifndef CBSETTING_H
#define CBSETTING_H

#include <QString>
#include <QStringList>
#include "cbxmlreader.h"

class CBSetting
{
public:
    CBSetting();

    virtual bool load() = 0;
    virtual bool save() = 0;

    void setSettingPath(const QString &path);
    QString getSettingPath();

    void setSettingCodec(const QString &codec);
    QString getSettingCodec();

protected:
    QString filePath;
    QString fileCodec;
};

class CBLeftButtonSetting : public CBSetting, public CBXmlReaderCallback
{
public:
    CBLeftButtonSetting();
    CBLeftButtonSetting(const QString &path);

    virtual bool load();
    virtual bool save();

    virtual bool onTagDetected(QString tag, QString content, const QXmlStreamAttributes attrs);

    void setTags(const QStringList &tags);
    QStringList getTags();

private:
    QStringList _tags;
};

#endif // CBSETTING_H
