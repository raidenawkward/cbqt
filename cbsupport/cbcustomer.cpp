#include "cbcustomer.h"
#include <QStringList>

CBCustomer::CBCustomer()
    :_numOfPeople(0)
{
}

CBCustomer::CBCustomer(QString string)
{
    QStringList list = string.split(CBCUSTOMER_STRING_SPLITOR);
    if (list.count() < 3)
        return;

    CBId id(list[0]);
    this->setId(id);
    this->setName(list[1]);
    this->setNumOfPeople(QString(list[2]).toInt());
}

bool CBCustomer::operator == (CBCustomer customer)
{
    return (getId().equals(customer.getId()));
}

bool CBCustomer::operator != (CBCustomer customer)
{
    return !(getId().equals(customer.getId()));
}

bool CBCustomer::equals(CBCustomer customer)
{
    return (getId().equals(customer.getId()));
}

CBCustomer& CBCustomer::operator = (CBCustomer customer)
{
    _id = customer.getId();
    _name = customer.getName();
    _numOfPeople = customer.getNumOfPeople();

    return *this;
}

QString CBCustomer::toString()
{
    QString res;
    res += _id.toString();
    res += CBCUSTOMER_STRING_SPLITOR;
    res += _name;
    res += CBCUSTOMER_STRING_SPLITOR;
    res += QString::number(this->_numOfPeople);

    return res;
}
