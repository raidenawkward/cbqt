#ifndef CBMENUITEMSSET_H
#define CBMENUITEMSSET_H

#include "cbmenuitem.h"
#include "cbifsethandler.h"
#include "cbid.h"
#include <QList>

class CBMenuItemsSet : public CBIFSetHandler<CBMenuItem*>
{
public:
    CBMenuItemsSet();
    CBMenuItemsSet(CBMenuItemsSet &set);
    CBMenuItemsSet(const CBMenuItemsSet &set);

    virtual bool add(CBMenuItem* item);
    virtual CBMenuItem* get(int index);
    virtual CBMenuItem* get(CBMenuItem* item);
    virtual bool update(CBMenuItem* item);
    virtual bool update(int index, CBMenuItem* item);
    virtual bool remove(CBMenuItem* item);
    virtual bool remove(int index);
    virtual int getIndexOf(CBMenuItem* item);
    virtual int count();
    virtual bool contains(CBMenuItem* item);

    CBMenuItem* get(CBId id);

    QList<CBMenuItem*> getItemList();

private:
    QList<CBMenuItem*> _itemList;
};

#endif // CBMENUITEMSSET_H
