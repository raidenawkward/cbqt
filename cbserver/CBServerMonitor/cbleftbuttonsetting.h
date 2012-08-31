#ifndef CBLEFTBUTTONSETTING_H
#define CBLEFTBUTTONSETTING_H

#include "cbsetting.h"
#include "cbglobal.h"
#include "cbdefine.h"
#include "cbxmlreader.h"
#include "cbxmlwriter.h"

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

#endif // CBLEFTBUTTONSETTING_H
