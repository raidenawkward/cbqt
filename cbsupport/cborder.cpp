#include "cborder.h"

CBOrder::CBOrder()
    :_discount(0.0),_summation(0.0)
{

}

CBOrder::CBOrder(CBOrder &order)
{
    setOrder(order);
}

bool CBOrder::operator ==(CBOrder order)
{
    return getId().equals(order.getId());
}

bool CBOrder::operator !=(CBOrder order)
{
    return getId().equals(order.getId());
}

bool CBOrder::equals(CBOrder order)
{
    return getId().equals(order.getId());
}

CBOrder& CBOrder::operator=(CBOrder order)
{
    setOrder(order);

    return *this;
}

void CBOrder::setOrder(CBOrder order)
{
    setId(order.getId());
    setLocation(order.getLocation());
    setCustomer(order.getCustomer());
    setDisabledTagsSet(order.getDisabledTagsSet());
    setDiscount(order.getDiscount());
    setSummation(order.getSummation());
    setCreatedTime(order.getCreatedTime());
    setSubmitedTime(order.getSubmitedTime());
    setMemo(order.getMemo());
    setRecordSavedPath(order.getRecordSavedPath());
    setStatus(order.getStatus());
}

bool CBOrder::addItem(CBMenuItem item, int count)
{
    if (count <= 0)
        return false;

    CBOrderedItem orderingItem;
    orderingItem.item = item;
    orderingItem.count = count;

    int index = getOrderedItemIndex(item);
    if (index < 0)
    {
        this->_orderedItems.append(orderingItem);
    }
    else
    {
        this->_orderedItems.replace(index, orderingItem);
    }

    return true;
}

CBOrderedItem* CBOrder::getOrderedItemFromOrderedList(CBMenuItem item)
{
    CBOrderedItem* res = NULL;
    for (int i = 0; i < this->_orderedItems.count(); ++i)
    {
        CBOrderedItem orderedItem = _orderedItems.at(i);
        if (orderedItem.item.equals(item))
        {
            res = &orderedItem;
            return res;
        }
    }

    return res;
}

bool CBOrder::removeItem(CBMenuItem item)
{
    int index = this->getOrderedItemIndex(item);
    return removeItem(index);
}

bool CBOrder::removeItem(int index)
{
    if (index < 0 || index >= this->_orderedItems.count())
        return false;

    _orderedItems.removeAt(index);
    return true;
}

bool CBOrder::isItemBeenChecked(CBMenuItem item)
{
    return (getOrderedItemFromOrderedList(item) != NULL);
}

int CBOrder::getTotalItemCheckedCount()
{
    int res = 0;

    for (int i = 0; i < _orderedItems.count(); ++i)
    {
        res += _orderedItems.at(i).count;
    }

    return res;
}

int CBOrder::getItemCheckedCount(CBMenuItem item)
{
    CBOrderedItem *orderedItem = getOrderedItemFromOrderedList(item);
    if (!orderedItem)
        return 0;

    return orderedItem->count;
}

bool CBOrder::isItemDisabled(CBMenuItem item)
{
    CBOrderedItem *orderedItem = getOrderedItemFromOrderedList(item);
    if (!orderedItem)
        return false;

    return (_disabledTagsSet.getIntersection(orderedItem->item.getDish().getTagsSet()) != 0);
}

CBTagsSet CBOrder::getConflictedTagsSet(CBMenuItem item)
{
    CBTagsSet res;
    CBTagsSet dishTags = item.getDish().getTagsSet();

    for (int i = 0; i < dishTags.count(); ++i)
    {
        QString tag = dishTags.get(i);
        if (_disabledTagsSet.contains(tag))
            res.add(tag);
    }

    return res;
}

int CBOrder::getOrderedItemIndex(CBMenuItem item)
{
    for (int i = 0; i < _orderedItems.count(); ++i) {
        CBOrderedItem it = _orderedItems.at(i);
        if (it.item.equals(item))
            return i;
    }

    return -1;
}

float CBOrder::getRealSummation()
{
    float sum = 0.0;
    for (int i = 0; i < _orderedItems.count(); ++i)
    {
        CBOrderedItem oItem = _orderedItems.at(i);
        sum += oItem.item.getDish().getPrice() * (float)oItem.count;
    }

    sum *= this->getDiscount();
    this->_summation = sum;

    return sum;
}

void CBOrder::touch()
{
    this->_submitedTime = QDateTime::currentDateTime();
}

void CBOrder::addDisabledTag(QString tag)
{
    this->_disabledTagsSet.add(tag);
}
