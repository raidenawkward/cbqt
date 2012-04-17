#include "cbxmlwriter.h"

CBXmlWriter::CBXmlWriter()
{
    _streamWriter = NULL;
}

CBXmlWriter::CBXmlWriter(const QString filePath)
{
    _streamWriter = NULL;
    setFilePath(filePath);
}

CBXmlWriter::CBXmlWriter(QIODevice *device)
{
    _streamWriter = NULL;
    setIODevice(device);
}

CBXmlWriter::~CBXmlWriter()
{
    if (_streamWriter)
        delete _streamWriter;
    if (_device)
        delete _device;
}

void CBXmlWriter::setIODevice(QIODevice *device)
{
    if (!device)
        return;

    if (_streamWriter) {
        delete _streamWriter;
    }

    _device = device;
    if (!_device->open(QFile::WriteOnly | QFile::Text))
        return;

    _streamWriter = new QXmlStreamWriter(device);
}

void CBXmlWriter::setFilePath(const QString filePath)
{
    QFile *file = new QFile(filePath);
    setIODevice(file);
}

bool CBXmlWriter::start()
{
    if(!_streamWriter || !_device)
        return false;

    _streamWriter->setAutoFormatting(true);
    _streamWriter->writeStartDocument();

    return true;
}

void CBXmlWriter::end()
{
    if(!_streamWriter)
        return;

    _streamWriter->writeEndDocument();
    _device->close();
}

bool CBXmlWriter::writeStartElement(const QString element)
{
    if(!_streamWriter)
        return false;

    _streamWriter->writeStartElement(element);

    return true;
}

bool CBXmlWriter::writeAttribute(const QString attr, const QString value)
{
    if(!_streamWriter)
        return false;

    _streamWriter->writeAttribute(attr, value);

    return true;
}

bool CBXmlWriter::writeContent(const QString text)
{
    if(!_streamWriter)
        return false;

    _streamWriter->writeCharacters(text);

    return true;
}

bool CBXmlWriter::writeEndElement()
{
    if(!_streamWriter)
        return false;

    _streamWriter->writeEndElement();

    return true;
}
