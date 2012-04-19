#include "cbdishparser.h"
#include "cbid.h"
#include <QStringList>
#include <QDebug>

CBDishParser::CBDishParser()
    : CBXmlReader()
{
    setCallback(this);
}

CBDishParser::CBDishParser(QString path)
    : CBXmlReader(path)
{
    setCallback(this);
}

bool CBDishParser::onTagDetected(QString tag, QString content, const QXmlStreamAttributes)
{
    if (tag.toLower() == CBDISH_TAG_ID)
    {
        CBId id(content);
        _dish.setId(id);
    }
    else if (tag.toLower() == CBDISH_TAG_NAME)
    {
        _dish.setName(content);
    }
    else if (tag.toLower() == CBDISH_TAG_PRICE)
    {
        float price = content.toFloat();
        _dish.setPrice(price);
    }
#if 0
    else if (tag.toLower() == CBDISH_TAG_TAGS)
    {
        QStringList list = content.split(CBDISH_TAG_TAGS_SPLITER);
        for (int i = 0; i < list.count(); ++i)
            _dish.addTag(list.at(i));
    }
#endif
    else if (tag.toLower() == CBDISH_TAG_TAG)
    {
        _dish.addTag(content);
    }
    else if (tag.toLower() == CBDISH_TAG_SCORE)
    {
        float score = content.toFloat();
        _dish.setScore(score);
    }
    else if (tag.toLower() == CBDISH_TAG_SUMMARIZE)
    {
        _dish.setSummary(content);
    }
    else if (tag.toLower() == CBDISH_TAG_DETAIL)
    {
        _dish.setDetail(content);
    }
    else if (tag.toLower() == CBDISH_TAG_THUMB)
    {
        _dish.setThumb(content);
    }
    else if (tag.toLower() == CBDISH_TAG_PICTURE)
    {
        _dish.setPicture(content);
    }
    else
    {

    }

    return true;
}

bool CBDishParser::parse()
{
    return this->readAll();
}
