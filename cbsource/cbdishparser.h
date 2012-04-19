#ifndef CBDISHPARSER_H
#define CBDISHPARSER_H

#include "cbxmlreader.h"
#include "cbdish.h"
#include <QString>

class CBDishParser : public CBXmlReader, CBXmlReaderCallback
{
public:
    CBDishParser();
    CBDishParser(QString path);

    virtual bool onTagDetected(QString tag, QString content, const QXmlStreamAttributes);

    CBDish& getDish() { return _dish; }
    bool parse();

private:
    CBDish _dish;
};

#endif // CBDISHPARSER_H
