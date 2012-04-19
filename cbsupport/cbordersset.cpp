#include "cbordersset.h"

CBOrdersSet::CBOrdersSet()
{
}

bool CBOrdersSet::add(CBOrder* item)
{
    if (this->contains(item))
        return false;

    this->_itemList.append(item);
    return true;
}

CBOrder* CBOrdersSet::get(int index)
{
    if (index < 0 || index >= _itemList.count())
        return NULL;

    CBOrder *res = _itemList.at(index);
    return res;
}

CBOrder* CBOrdersSet::get(CBOrder* item)
{
    for (int i = 0; i < _itemList.count(); ++i)
    {
        CBOrder *it = _itemList.at(i);
        if (it->getId().equals(item->getId()))
        {
            return it;
        }
    }

    return NULL;
}

bool CBOrdersSet::update(CBOrder* item)
{
    int index = this->getIndexOf(item);
    return update(index, item);
}

bool CBOrdersSet::update(int index, CBOrder* item)
{
    if (index < 0 || index >= _itemList.count())
        return false;

    _itemList.replace(index, item);
    return true;
}

bool CBOrdersSet::remove(CBOrder* item)
{
    int index = getIndexOf(item);
    return remove(index);
}

bool CBOrdersSet::remove(int index)
{
    if (index < 0 || index >= _itemList.count())
        return false;

    _itemList.removeAt(index);
    return true;
}

int CBOrdersSet::getIndexOf(CBOrder* item)
{
    if (!item)
        return -1;

    for (int i = 0; i < _itemList.count(); ++i)
    {
        CBOrder *it = _itemList.at(i);
        if (!it)
            continue;
        if (it->getId().equals(item->getId()))
            return i;
    }

    return -1;
}

int CBOrdersSet::count()
{
    return _itemList.count();
}

bool CBOrdersSet::contains(CBOrder* item)
{
    if (!item)
        return -1;

    for (int i = 0; i < _itemList.count(); ++i)
    {
        CBOrder *it = _itemList.at(i);
        if (!it)
            continue;
        if (it->getId().equals(item->getId()))
            return true;
    }

    return false;
}

CBOrder* CBOrdersSet::get(CBId id)
{
    for (int i = 0; i < _itemList.count(); ++i)
    {
        CBOrder *it = _itemList.at(i);
        if (!it)
            continue;
        if (it->getId().equals(id))
            return it;
    }
    return NULL;
}

void CBOrdersSet::clear()
{
    _itemList.clear();
}

QList<CBOrder*> CBOrdersSet::getItemList()
{
    return _itemList;
}
