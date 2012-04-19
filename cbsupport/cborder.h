#ifndef CBORDER_H
#define CBORDER_H

#include <QString>
#include <QDateTime>
#include <QList>
#include "cbid.h"
#include "cbcustomer.h"
#include "cbtagsset.h"
#include "cbmenuitem.h"

enum CBORDER_STATUS
{
    CBORDER_STATUS_UNKNOWN = 0,
    CBORDER_STATUS_ADDING,
    CBORDER_STATUS_EDITING,
    CBORDER_STATUS_CONFIRMED
};

class CBOrderedItem {
public:
    CBOrderedItem() : count(0) {}
    CBOrderedItem(const CBOrderedItem& orderItem)
    {
        CBOrderedItem newOrderItem = orderItem;
        item = newOrderItem.item;
        count = newOrderItem.count;
    }

    CBMenuItem item;
    int count;
};

class CBOrder
{
public:
    CBOrder();
    CBOrder(const CBOrder &order);

    bool addItem(CBMenuItem item, int count = 1);
    bool removeItem(CBMenuItem item);
    bool removeItem(int index);
    bool isItemBeenChecked(CBMenuItem item);
    int getTotalItemCheckedCount();
    int getItemCheckedCount(CBMenuItem item);
    bool isItemDisabled(CBMenuItem item);
    CBTagsSet getConflictedTagsSet(CBMenuItem item);
    int getOrderedItemIndex(CBMenuItem item);
    float getRealSummation();
    void touch();
    void addDisabledTag(QString tag);


    bool operator ==(CBOrder order);
    bool operator !=(CBOrder order);
    CBOrder& operator=(CBOrder order);
    bool equals(CBOrder order);


    CBId& getId() { return _id; }
    void setId(CBId id) { _id = id; }

    QString getLocation() { return _location; }
    void setLocation(QString location) { _location = location; }

    CBCustomer& getCustomer() { return _customer; }
    void setCustomer(CBCustomer customer) { _customer = customer; }

    CBTagsSet& getDisabledTagsSet() { return _disabledTagsSet; }
    void setDisabledTagsSet(CBTagsSet set) { _disabledTagsSet = set; }

    float getDiscount() { return _discount; }
    void setDiscount(float discount) { _discount = discount; }

    float getSummation() { return _summation; }
    void setSummation(float summation) { _summation = summation; }

    QDateTime getCreatedTime() { return _createdTime; }
    void setCreatedTime(QDateTime date) { _createdTime = date; }

    QDateTime getSubmitedTime() { return _submitedTime; }
    void setSubmitedTime(QDateTime date) { _submitedTime = date; }

    QString getMemo() { return _memo; }
    void setMemo(QString memo) { _memo = memo; }

    QString getRecordSavedPath() { return _recordSavedPath; }
    void setRecordSavedPath(QString path) { _recordSavedPath = path; }

    CBORDER_STATUS getStatus() { return _status; }
    void setStatus(CBORDER_STATUS status) { _status = status; }

    QList<CBOrderedItem> getOrderedItemList() { return _orderedItems; }
    void setOrderedItemList(QList<CBOrderedItem> list) { _orderedItems = list; }

private:
    void setOrder(CBOrder order);
    CBOrderedItem* getOrderedItemFromOrderedList(CBMenuItem item);

private:
    CBId _id;
    QString _location;
    CBCustomer _customer;
    CBTagsSet _disabledTagsSet;
    float _discount;
    float _summation;
    QDateTime _createdTime;
    QDateTime _submitedTime;
    QString _memo;
    QString _recordSavedPath;
    CBORDER_STATUS _status;

    QList<CBOrderedItem> _orderedItems;
};

#endif // CBORDER_H
