#ifndef CBENGINE_H
#define CBENGINE_H

#include "cbmenuitem.h"
#include "cbmenuitemsset.h"
#include "cbdish.h"
#include "cborder.h"
#include "cbordersset.h"
#include "cbid.h"
#include "cbcustomer.h"

class CBEngine
{
public:
    CBEngine();
    ~CBEngine();

    bool loadMenuItems(const QString path);

    CBMenuItemsSet* getMenuItemsSet();

private:
    CBMenuItemsSet *_menuItemsSet;
};

#endif // CBENGINE_H
