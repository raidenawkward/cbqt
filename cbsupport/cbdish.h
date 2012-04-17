#ifndef CBDISH_H
#define CBDISH_H

#include "cbid.h"
#include "cbtagsset.h"
#include <QString>

#define CBDISH_TAG_ID "id"
#define CBDISH_TAG_NAME "name"
#define CBDISH_TAG_PRICE "price"
#define CBDISH_TAG_TAGS "tags"
#define CBDISH_TAG_TAGS_SPLITER ","
#define CBDISH_TAG_SCORE "score"
#define CBDISH_TAG_SUMMARIZE "summary"
#define CBDISH_TAG_DETAIL "detail"
#define CBDISH_TAG_THUMB "thumb"
#define CBDISH_TAG_PICTURE "picture"

class CBDish
{
public:
    CBDish();
    CBDish(const CBDish &dish);
    CBDish(CBDish &dish);

    static bool setDishAttr(CBDish &dish, const QString attr, const QString value);

    bool isTagContained(QString tag);
    bool isTagsSetContained(CBTagsSet set);
    void addTag(QString tag);
    void addTagsSet(CBTagsSet set);
    QStringList getTags();
    void setTags(QStringList list);

    bool operator ==(CBDish dish);
    bool operator !=(CBDish dish);

    CBId& getId() { return _id; }
    void setId(CBId id) { _id = id; }
    QString getName() { return _name; }
    void setName(QString name) { _name = name; }
    float getPrice() { return _price; }
    void setPrice(float price) { _price = price; }
    CBTagsSet& getTagsSet() { return _tagsSet; }
    void setTagsSet(CBTagsSet set) { _tagsSet = set; }
    float getScore() { return _score; }
    void setScore(float score) { _score = score; }
    QString getSummary() { return _summary; }
    void setSummary(QString summary) { _summary = summary; }
    QString getDetail() { return _detail; }
    void setDetail(QString detail) { _detail = detail; }
    QString getThumb() { return _thumb; }
    void setThumb(QString thumb) { _thumb = thumb; }
    QString getPicture() { return _picture; }
    void setPicture(QString picture) { _picture = picture; }

private:
    void setDish(CBDish &dish);

private:
    CBId _id;
    QString _name;
    float _price;
    CBTagsSet _tagsSet;
    float _score;
    QString _summary;
    QString _detail;
    QString _thumb;
    QString _picture;
};

#endif // CBDISH_H
