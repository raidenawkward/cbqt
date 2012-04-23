#ifndef CBXMLWRITER_H
#define CBXMLWRITER_H

#include <QString>
#include <QFile>
#include <QXmlStreamWriter>

class CBXmlWriter
{
public:
    CBXmlWriter();
    CBXmlWriter(const QString filePath);
    CBXmlWriter(QIODevice *device);
    ~CBXmlWriter();

    void setIODevice(QIODevice *device);
    void setFilePath(const QString filePath);
    void setCodec(const QString codec);

    bool start();
    void end();

    bool writeStartElement(const QString element);
    bool writeAttribute(const QString attr, const QString value);
    bool writeContent(const QString text);
    bool writeEndElement();

protected:
    QXmlStreamWriter *_streamWriter;
    QIODevice *_device;
};

#endif // CBXMLWRITER_H
