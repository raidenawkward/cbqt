#include "cbtagsset.h"

CBTagsSet::CBTagsSet()
{
}

CBTagsSet::CBTagsSet(const CBTagsSet &set)
{
    CBTagsSet newSet = set;
    _tagsList = newSet.getTagsList();
}

CBTagsSet::CBTagsSet(CBTagsSet &set)
{
    _tagsList = set.getTagsList();
}

CBTagsSet::CBTagsSet(QStringList list)
{
    _tagsList = list;
}

bool CBTagsSet::add(QString item)
{
    _tagsList.append(item);
    return true;
}

QString CBTagsSet::get(int index)
{
    if (index < 0 || index >= _tagsList.count())
        return NULL;

    return _tagsList.at(index);
}

QString CBTagsSet::get(QString item)
{
    int index = this->getIndexOf(item);
    if (index < 0 || index >= _tagsList.count())
        return NULL;

    return _tagsList.at(index);
}

bool CBTagsSet::update(QString item)
{
    int index = this->getIndexOf(item);
    return update(index, item);
}

bool CBTagsSet::update(int index, QString item)
{
    if (index < 0 || index >= _tagsList.count())
        return false;

    this->_tagsList.replace(index, item);
    return true;
}

bool CBTagsSet::remove(QString item)
{
    int index = this->getIndexOf(item);
    return remove(index);
}

bool CBTagsSet::remove(int index)
{
    if (index < 0 || index >= _tagsList.count())
        return false;

    _tagsList.removeAt(index);
    return true;
}

int CBTagsSet::getIndexOf(QString item)
{
    return _tagsList.indexOf(item);
}

int CBTagsSet::count()
{
    return _tagsList.count();
}

bool CBTagsSet::contains(QString item)
{
    return (getIndexOf(item) >= 0);
}

bool CBTagsSet::isEmpty()
{
    return _tagsList.isEmpty();
}

int CBTagsSet::combine(CBTagsSet &set)
{
    int res = 0;
    QStringList targetList = set.getTagsList();

    for (int i = 0; i < _tagsList.count(); ++i)
    {
        QString tag = targetList.at(i);
        if (!_tagsList.contains(tag))
        {
            _tagsList.append(tag);
            ++res;
        }
    }

    return res;
}

int CBTagsSet::getIntersection(CBTagsSet set)
{
    int res = 0;
    QStringList targetList = set.getTagsList();

    for (int i = 0; i < _tagsList.count(); ++i)
    {
        QString tag = targetList.at(i);
        if (_tagsList.contains(tag))
        {
            ++res;
        }
    }

    return res;
}

QString CBTagsSet::toString(const QString spliter)
{
    QString res;

    for (int i = 0; i < _tagsList.count(); ++i)
    {
        res += _tagsList.at(i);
        if (i < _tagsList.count() - 1)
            res += spliter;
    }

    return res;
}

CBTagsSet& CBTagsSet::operator + (CBTagsSet set)
{
    combine(set);
    return *this;
}

CBTagsSet& CBTagsSet::operator - (CBTagsSet set)
{
    QStringList targetList = set.getTagsList();
    for (int i = 0; i < targetList.count(); ++i)
    {
        this->remove(targetList.at(i));
    }

    return *this;
}

bool CBTagsSet::operator == (CBTagsSet set)
{
    return (getIntersection(set) == _tagsList.count());
}

bool CBTagsSet::equals(CBTagsSet set)
{
    return (getIntersection(set) == _tagsList.count());
}

QStringList CBTagsSet::getTagsList()
{
    return this->_tagsList;
}

void CBTagsSet::setTagsList(QStringList list)
{
    this->_tagsList = list;
}
