#include "cbxmlreader.h"
#include <QFile>
#include <QDebug>

CBXmlReader::CBXmlReader()
    :_streamReader(NULL),
      _device(NULL),
      _callback(NULL)
{

}

CBXmlReader::CBXmlReader(const QString filePath)
    :_streamReader(NULL),
      _device(NULL),
      _callback(NULL)
{
    setFilePath(filePath);
}

CBXmlReader::CBXmlReader(QIODevice *device)
    :_streamReader(NULL),
      _device(NULL),
      _callback(NULL)
{
    setIODevice(device);
}

CBXmlReader::~CBXmlReader()
{
    if (_streamReader)
        delete _streamReader;
    if (_device)
        delete _device;
}

void CBXmlReader::setIODevice(QIODevice *device)
{
    if (!device)
        return;

    if (_streamReader) {
        delete _streamReader;
    }

    _device = device;
    if (!_device->open(QFile::ReadOnly | QFile::Text))
        return;

    _streamReader = new QXmlStreamReader(device);
}

void CBXmlReader::setFilePath(const QString filePath)
{
    QFile *file = new QFile(filePath);
    setIODevice(file);
}

void CBXmlReader::readAll()
{
    if (!_streamReader)
        return;

    QXmlStreamAttributes attrs;
    QString tag = "";
    QString text = "";

    while(!_streamReader->atEnd()) {

        switch (_streamReader->tokenType())
        {
        case QXmlStreamReader::NoToken:
        case QXmlStreamReader::StartDocument:
        case QXmlStreamReader::EndDocument:
            break;
        case QXmlStreamReader::StartElement:
            tag = _streamReader->name().toString();
            attrs = _streamReader->attributes();
            break;
        case QXmlStreamReader::Characters:
        case QXmlStreamReader::Comment:
            text = _streamReader->text().toString();
            break;
        case QXmlStreamReader::EndElement:
            if (_streamReader->name().toString().compare(tag) != 0)
            {
                goto error;
            }

            if (_callback) {
                if (!_callback->onTagDetected(tag, text, attrs))
                    goto error;
            }
            tag = "";
            text = "";
            attrs.clear();
            break;
        case QXmlStreamReader::Invalid:
            goto error;
        default:
            break;
        }

        _streamReader->readNext();
    }

    return;

error:
    if (_streamReader->hasError()) {
        exit(13);
    }
}

void CBXmlReader::setCallback(CBXmlReaderCallback* callback)
{
    _callback = callback;
}
