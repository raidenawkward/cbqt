#ifndef CBXMLREADER_H
#define CBXMLREADER_H

#include <QString>
#include <QIODevice>
#include <QXmlStreamReader>
#include <QXmlStreamAttributes>

class CBXmlReaderCallback
{
public:
    virtual bool onTagDetected(QString tag, QString content, const QXmlStreamAttributes attrs) = 0;
};

class CBXmlReader
{
public:
    CBXmlReader();
    CBXmlReader(const QString filePath);
    CBXmlReader(QIODevice *device);
    ~CBXmlReader();

    void setIODevice(QIODevice *device);
    void setFilePath(const QString filePath);

    bool readAll();

    void setCallback(CBXmlReaderCallback* callback);

protected:
    QXmlStreamReader *_streamReader;
    QIODevice *_device;
    CBXmlReaderCallback *_callback;
};

#endif // CBXMLREADER_H
