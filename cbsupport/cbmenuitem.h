#ifndef CBMENUITEM_H
#define CBMENUITEM_H

#include "cbdish.h"
#include "cbtagsset.h"

class CBMenuItem
{
public:
    CBMenuItem();
    CBMenuItem(CBMenuItem& item);
    CBMenuItem(CBDish &dish);

    bool isTagContained(QString tag);
    bool isTagsSetContained(CBTagsSet set);

    bool operator ==(CBMenuItem item);
    bool operator !=(CBMenuItem item);
//    CBMenuItem& operator =(CBMenuItem item);

    CBDish& getDish() { return _dish; }
    void setDish(CBDish dish) { _dish = dish; }
    int getIconId() { return _iconId; }
    void setIconId(int id) { _iconId = id; }

private:
    CBDish _dish;
    int _iconId;
};

#endif // CBMENUITEM_H
