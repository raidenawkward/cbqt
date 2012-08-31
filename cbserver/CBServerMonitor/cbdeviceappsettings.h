#ifndef CBDEVICEAPPSETTINGS_H
#define CBDEVICEAPPSETTINGS_H

#include "cbsetting.h"
#include "cbglobal.h"
#include "cbdefine.h"
#include "cbxmlreader.h"
#include "cbxmlwriter.h"

#include <QHash>

class CBDeviceAppSettings : public CBSetting, public CBXmlReaderCallback
{
public:
    CBDeviceAppSettings();
    CBDeviceAppSettings(const QString& path);

    virtual bool load();
    virtual bool save();

    virtual bool onTagDetected(QString tag, QString content, const QXmlStreamAttributes attrs);

    void set(const QString &key, const QString &value);
    QString get(const QString &key);

    void setMap(const QHash<QString, QString> &map);
    QHash<QString, QString>& getMap();

private:
    QHash<QString, QString> _map;
};

#endif // CBDEVICEAPPSETTINGS_H
