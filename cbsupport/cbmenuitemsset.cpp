#include "cbmenuitemsset.h"

CBMenuItemsSet::CBMenuItemsSet()
{

}

CBMenuItemsSet::CBMenuItemsSet(CBMenuItemsSet &set)
{
    this->_itemList = set.getItemList();
}

CBMenuItemsSet::CBMenuItemsSet(const CBMenuItemsSet &set)
{
    CBMenuItemsSet s = set;
    this->_itemList = s.getItemList();
}

bool CBMenuItemsSet::add(CBMenuItem* item)
{
    if (this->contains(item))
        return false;

    this->_itemList.append(item);
    return true;
}

CBMenuItem* CBMenuItemsSet::get(int index)
{
    if (index < 0 || index >= _itemList.count())
        return NULL;

    CBMenuItem *res = _itemList.at(index);
    return res;
}

CBMenuItem* CBMenuItemsSet::get(CBMenuItem* item)
{
    for (int i = 0; i < _itemList.count(); ++i)
    {
        CBMenuItem *it = _itemList.at(i);
        if (it->getDish().equals(item->getDish()))
        {
            return it;
        }
    }

    return NULL;
}

CBMenuItem* CBMenuItemsSet::get(CBId id)
{
    for (int i = 0; i < _itemList.count(); ++i)
    {
        CBMenuItem *item = _itemList.at(i);
        if (item->getDish().getId().equals(id))
            return item;
    }

    return NULL;
}

bool CBMenuItemsSet::update(CBMenuItem* item)
{
    int index = this->getIndexOf(item);
    return update(index, item);
}

bool CBMenuItemsSet::update(int index, CBMenuItem* item)
{
    if (index < 0 || index >= _itemList.count())
        return false;

    _itemList.replace(index, item);
    return true;
}

bool CBMenuItemsSet::remove(CBMenuItem *item)
{
    int index = this->getIndexOf(item);
    return remove(index);
}

bool CBMenuItemsSet::remove(int index)
{
    if (index < 0 || index >= _itemList.count())
        return false;

    _itemList.removeAt(index);
    return true;
}

int CBMenuItemsSet::getIndexOf(CBMenuItem *item)
{
    for (int i = 0; i < _itemList.count(); ++i)
    {
        CBMenuItem *it = _itemList.at(i);
        if (!it)
            continue;
        if (it->getDish().equals(item->getDish()))
            return i;
    }

    return -1;
}

int CBMenuItemsSet::count()
{
    return _itemList.count();
}

bool CBMenuItemsSet::contains(CBMenuItem* item)
{
    for (int i = 0; i < _itemList.count(); ++i)
    {
        CBMenuItem *it = _itemList.at(i);
        if (!it)
            continue;
        if (it->getDish().equals(item->getDish()))
            return true;
    }
    return false;
}

void CBMenuItemsSet::clear()
{
    _itemList.clear();
}

QList<CBMenuItem*> CBMenuItemsSet::getItemList()
{
    return this->_itemList;
}

CBMenuItemsSet& CBMenuItemsSet::operator =(CBMenuItemsSet set)
{
    this->_itemList = set.getItemList();
    return *this;
}
