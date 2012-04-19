#ifndef CBMENUITEM_H
#define CBMENUITEM_H

#include "cbdish.h"
#include "cbtagsset.h"

class CBMenuItem
{
public:
    CBMenuItem();
    CBMenuItem(CBDish &dish);

    bool isTagContained(QString tag);
    bool isTagsSetContained(CBTagsSet set);

    bool operator ==(CBMenuItem item);
    bool operator !=(CBMenuItem item);
    bool equals(CBMenuItem item);
//    CBMenuItem& operator =(CBMenuItem item);

    CBDish getDish();
    void setDish(CBDish dish);
    int getIconId();
    void setIconId(int id);

private:
    CBDish _dish;
    int _iconId;
};

#endif // CBMENUITEM_H
