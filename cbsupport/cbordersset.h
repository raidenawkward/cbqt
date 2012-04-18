#ifndef CBORDERSSET_H
#define CBORDERSSET_H

#include "cborder.h"
#include "cbifsethandler.h"

class CBOrdersSet : public CBIFSetHandler<CBOrder*>
{
public:
    CBOrdersSet();
    CBOrdersSet(CBOrdersSet &set);
    CBOrdersSet(const CBOrdersSet &set);

    virtual bool add(CBOrder* item);
    virtual CBOrder* get(int index);
    virtual CBOrder* get(CBOrder* item);
    virtual bool update(CBOrder* item);
    virtual bool update(int index, CBOrder* item);
    virtual bool remove(CBOrder* item);
    virtual bool remove(int index);
    virtual int getIndexOf(CBOrder* item);
    virtual int count();
    virtual bool contains(CBOrder* item);

    CBOrder* get(CBId id);

    QList<CBOrder*> getItemList();
private:
    QList<CBOrder*> _itemList;
};

#endif // CBORDERSSET_H
