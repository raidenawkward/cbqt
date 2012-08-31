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

#endif // CBSETTING_H
