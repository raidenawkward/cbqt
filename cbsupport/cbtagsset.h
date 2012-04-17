#ifndef CBTAGSSET_H
#define CBTAGSSET_H

#include <cbifsethandler.h>
#include <QString>
#include <QStringList>

class CBTagsSet : public CBIFSetHandler<QString>
{
public:
    CBTagsSet();
    CBTagsSet(const CBTagsSet &set);
    CBTagsSet(CBTagsSet &set);
    CBTagsSet(QStringList list);

    bool add(QString item);
    QString get(int index);
    QString get(QString item);
    bool update(QString item);
    bool update(int index, QString item);
    bool remove(QString item);
    bool remove(int index);
    int getIndexOf(QString item);
    int count();
    bool contains(QString item);

    bool isEmpty();
    int combine(CBTagsSet &set);
    int getIntersection(CBTagsSet set);
    QString toString(const QString spliter);

    CBTagsSet& operator + (CBTagsSet set);
    CBTagsSet& operator - (CBTagsSet set);
    bool operator == (CBTagsSet set);

    QStringList getTagsList();
    void setTagsList(QStringList list);

private:
    QStringList _tagsList;
};

#endif // CBTAGSSET_H
