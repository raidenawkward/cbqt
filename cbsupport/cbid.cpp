#include "cbid.h"

CBId::CBId()
{
}

CBId::CBId(QString id)
{
    setId(id);
}

CBId::CBId(CBId &id)
{
    setId(id);
}

void CBId::setId(QString id)
{
    _id = id;
}

void CBId::setId(CBId id)
{
    _id = id.getId();
}

QString& CBId::getId()
{
    return _id;
}

QString CBId::toString()
{
    return _id;
}

bool CBId::operator == (CBId id)
{
    return (_id.compare(id.getId()) == 0);
}

bool CBId::operator != (CBId id)
{
    return !(_id.compare(id.getId()) == 0);
}

//CBId& CBId::operator = (CBId id)
//{
//    setId(id);
//    return *this;
//}
