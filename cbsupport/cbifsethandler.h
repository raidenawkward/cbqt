#ifndef CBIFSETHANDLER_H
#define CBIFSETHANDLER_H

template <class TYPE>
class CBIFSetHandler
{
public:
    virtual bool add(TYPE item) = 0;
    virtual TYPE get(int index) = 0;
    virtual TYPE get(TYPE item) = 0;
    virtual bool update(TYPE item) = 0;
    virtual bool update(int index, TYPE item) = 0;
    virtual bool remove(TYPE item) = 0;
    virtual bool remove(int index) = 0;
    virtual int getIndexOf(TYPE item) = 0;
    virtual int count() = 0;
    virtual bool contains(TYPE item) = 0;
    virtual void clear() = 0;
};

#endif // CBIFSETHANDLER_H
