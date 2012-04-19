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
    CBMenuItem newItem = item;
    _dish = newItem.getDish();
    _iconId = newItem.getIconId();
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

//CBMenuItem& CBMenuItem::operator = (CBMenuItem item)
//{
//    _dish = item.getDish();
//    _iconId = item.getIconId();

//    return *this;
//}
