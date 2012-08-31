#ifndef CBLOCATIONSETTINGS_H
#define CBLOCATIONSETTINGS_H

#include "cbsetting.h"
#include "cbglobal.h"
#include "cbsetting.h"
#include "cbxmlreader.h"
#include "cbxmlwriter.h"

class CBLocationSettings : public CBSetting, public CBXmlReaderCallback
{
public:
    CBLocationSettings();
    CBLocationSettings(const QString& path);

    virtual bool load();
    virtual bool save();

    virtual bool onTagDetected(QString tag, QString content, const QXmlStreamAttributes attrs);

    void setTags(const QStringList &tags);
    QStringList getTags();

private:
    QStringList _tags;
};

#endif // CBLOCATIONSETTINGS_H
