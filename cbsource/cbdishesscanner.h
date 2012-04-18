#ifndef CBDISHESSCANNER_H
#define CBDISHESSCANNER_H

#include "cbpathwalker.h"
#include "cbmenuitemsset.h"
#include <QString>

class CBDishesScanner : public CBPathWalkerCallback
{
public:
    CBDishesScanner();
    CBDishesScanner(QString root);

    virtual bool onDirDetected(QFileInfo , int );
    virtual bool onFileDetected(QFileInfo file, int depth);

    void scan();
    void scan(const QString root);
    void clear();

    static bool isValidDishFile(const QString path);

    QString getRoot() { return _root; }
    void setRoot(const QString root) { _root = root; }
    CBMenuItemsSet getMenuItemSet() { return _menuItemSet; }

private:
    CBMenuItemsSet _menuItemSet;
    QString _root;
    CBPathWalker _pathWalker;
};

#endif // CBDISHESSCANNER_H
