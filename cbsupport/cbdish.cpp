#include "cbdish.h"

CBDish::CBDish()
    :_price(0.0),
      _score(0.0)
{
}

CBDish::CBDish(const CBDish &dish)
{
    CBDish newDish = dish;
    setDish(newDish);
}

void CBDish::setDish(CBDish& dish)
{
    setId(dish.getId());
    setName(dish.getName());
    setPrice(dish.getPrice());
    setTagsSet(dish.getTagsSet());
    setScore(dish.getScore());
    setSummary(dish.getSummary());
    setDetail(dish.getDetail());
    setThumb(dish.getThumb());
    setPicture(dish.getPicture());
}

bool CBDish::isTagContained(QString tag)
{
    return this->_tagsSet.contains(tag);
}

bool CBDish::isTagsSetContained(CBTagsSet set)
{
    return !(this->_tagsSet.getIntersection(set) == 0);
}

void CBDish::addTag(QString tag)
{
    _tagsSet.add(tag);
}

void CBDish::addTagsSet(CBTagsSet set)
{
    _tagsSet = _tagsSet + set;
}

QStringList CBDish::getTags()
{
    return _tagsSet.getTagsList();
}

void CBDish::setTags(QStringList list)
{
    _tagsSet.setTagsList(list);
}

bool CBDish::operator == (CBDish dish)
{
    return (getId() == dish.getId());
}

bool CBDish::operator != (CBDish dish)
{
    return !(getId() == dish.getId());
}

bool CBDish::equals(CBDish dish)
{
    return (getId().equals(dish.getId()));
}

bool CBDish::setDishAttr(CBDish &dish, const QString attr, const QString value)
{
    if (attr == CBDISH_TAG_ID)
    {
        CBId id(value);
        dish.setId(id);
    }
    else if (attr == (CBDISH_TAG_NAME))
    {
        dish.setName(value);
    }
    else if (attr == (CBDISH_TAG_PRICE))
    {
        float price = value.toFloat();
        dish.setPrice(price);
    }
    else if (attr == (CBDISH_TAG_TAGS))
    {
        CBTagsSet set;
        QStringList tags = value.split(CBDISH_TAG_TAGS_SPLITER);
        if (tags.count() > 1)
        {
            for (int i = 0; i < tags.count(); ++i)
                set.add(tags[i]);
        }
        dish.setTags(tags);
    }
    else if (attr == (CBDISH_TAG_SCORE))
    {
        float score = value.toFloat();
        dish.setScore(score);
    }
    else if (attr == (CBDISH_TAG_SUMMARIZE))
    {
        dish.setSummary(value);
    }
    else if (attr == (CBDISH_TAG_DETAIL))
    {
        dish.setDetail(value);
    }
    else if (attr == (CBDISH_TAG_THUMB))
    {
        dish.setThumb(value);
    }
    else if (attr == (CBDISH_TAG_PICTURE))
    {
        dish.setPicture(value);
    }
    else
    {
        return false;
    }

    return true;
}
