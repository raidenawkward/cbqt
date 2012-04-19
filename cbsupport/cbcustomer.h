#ifndef CBCUSTOMER_H
#define CBCUSTOMER_H

#include "cbid.h"
#include <QString>

#define CBCUSTOMER_STRING_SPLITOR "__"

class CBCustomer
{
public:
    CBCustomer();
    CBCustomer(QString string);

    bool operator == (CBCustomer customer);
    bool operator != (CBCustomer customer);
    bool equals(CBCustomer customer);
    CBCustomer& operator = (CBCustomer &customer);
    QString toString();

    CBId& getId() { return _id; }
    void setId(CBId id) { _id = id; }
    QString getName() { return _name; }
    void setName(QString name) { _name = name; }
    int getNumOfPeople() { return _numOfPeople; }
    void setNumOfPeople(int numOfPeople) { _numOfPeople = numOfPeople; }

private:
    CBId _id;
    QString _name;
    int _numOfPeople;
};

#endif // CBCUSTOMER_H
