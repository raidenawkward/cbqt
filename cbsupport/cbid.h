#ifndef CBID_H
#define CBID_H

#include <QString>

class CBId
{
public:
    CBId();
    CBId(QString id);
    CBId(CBId &id);

    void setId(QString id);
    void setId(CBId id);
    QString& getId();
    QString toString();

    bool operator == (CBId id);
    bool operator != (CBId id);

private:
    QString _id;
};

#endif // CBID_H