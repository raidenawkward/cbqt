#include "cbmenuitem.h"

CBMenuItem::CBMenuItem()
    :_iconId(-1)
{
}

CBMenuItem::CBMenuItem(CBDish &dish)
{
    _dish = dish;
}

CBMenuItem::CBMenuItem(const CBMenuItem& item)
{
    _dish = item._dish;
    _iconId = item._iconId;
}

bool CBMenuItem::isTagContained(QString tag)
{
    return _dish.isTagContained(tag);
}

bool CBMenuItem::isTagsSetContained(CBTagsSet set)
{
    return _dish.isTagsSetContained(set);
}

bool CBMenuItem::operator == (CBMenuItem item)
{
    if (getDish() != item.getDish())
        return false;
    if (getIconId() != item.getIconId())
        return false;

    return true;
}

bool CBMenuItem::operator != (CBMenuItem item)
{
    return !(*this == (item));
}

bool CBMenuItem::equals(CBMenuItem item)
{
    if (!getDish().equals(item.getDish()))
        return false;
    if (getIconId() != item.getIconId())
        return false;

    return true;
}

CBDish CBMenuItem::getDish()
{
    return this->_dish;
}

void CBMenuItem::setDish(CBDish dish)
{
    _dish = dish;
}

int CBMenuItem::getIconId()
{
    return _iconId;
}

void CBMenuItem::setIconId(int id)
{
    _iconId = id;
}

//CBMenuItem& CBMenuItem::operator = (CBMenuItem item)
//{
//    _dish = item.getDish();
//    _iconId = item.getIconId();

//    return *this;
//}
