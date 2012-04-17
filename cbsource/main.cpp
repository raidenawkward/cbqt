#include <stdio.h>
#include <QDebug>
#include "cbxmlwriter.h"
#include "cbxmlreader.h"

#define TEST_XML "/tmp/test.xml"

class ReaderCallback : public CBXmlReaderCallback
{
    virtual bool onTagDetected(QString tag, QString content, const QXmlStreamAttributes attrs)
    {
        qDebug()<<"* Tag detected: "<<tag;
        qDebug()<<"content: "<<content;
        for (int i = 0; i < attrs.count(); ++i)
        {
            qDebug()<<"attr "<<i<<": "<<attrs.at(i).name()<<"="<<attrs.at(i).value();
        }
        return true;
    }
};

int main()
{
    CBXmlWriter writer(TEST_XML);

    writer.start();

    writer.writeStartElement("tests");

    writer.writeStartElement("tag1");
    writer.writeAttribute("a", "b");
    writer.writeContent("aaa");
    writer.writeEndElement();

    writer.writeStartElement("tag2");
    writer.writeAttribute("a", "b");
    writer.writeAttribute("c", "d");
    writer.writeContent("bbb");
    writer.writeEndElement();

    writer.writeEndElement();
    writer.end();

    CBXmlReader reader(TEST_XML);
    ReaderCallback *callback = new ReaderCallback();
    reader.setCallback(callback);
    reader.readAll();

    return 0;
}
