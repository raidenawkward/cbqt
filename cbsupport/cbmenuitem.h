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

    CBDish& getDish();
    void setDish(CBDish dish);
    int getIconId();
    void setIconId(int id);
    QString getRecordDir();
    void setRecordDir(const QString path);
    QString getRecordFile();
    void setRecordFile(const QString file);

private:
    CBDish _dish;
    int _iconId;
    QString _recordDir;
    QString _recordFile;
};

#endif // CBMENUITEM_H
