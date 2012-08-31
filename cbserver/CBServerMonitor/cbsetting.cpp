#include "cbsetting.h"
#include "cbdefine.h"
#include "cbglobal.h"
#include "cbxmlwriter.h"
#include <QDir>
#include <QDebug>

CBSetting::CBSetting()
{
}

void CBSetting::setSettingPath(const QString &path)
{
    filePath = path;
}

QString CBSetting::getSettingPath()
{
    return filePath;
}

void CBSetting::setSettingCodec(const QString &codec)
{
    fileCodec = codec;
}

QString CBSetting::getSettingCodec()
{
    return fileCodec;
}
