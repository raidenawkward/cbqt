#include "cbdishesscanner.h"
#include "cbdishparser.h"
#include "cbmenuitem.h"
#include <QDebug>

CBDishesScanner::CBDishesScanner()
{
    _pathWalker.setCallback(this);
}

CBDishesScanner::CBDishesScanner(QString root)
{
    _pathWalker.setCallback(this);
    this->setRoot(root);
}

bool CBDishesScanner::onDirDetected(QFileInfo, int)
{
    return true;
}

bool CBDishesScanner::isValidDishFile(const QString path)
{
    return path.endsWith(".xml");
}

bool CBDishesScanner::onFileDetected(QFileInfo file, int depth)
{
    if (depth <= 0)
        return false;

    if (!file.exists())
        return false;

    if (!isValidDishFile(file.absoluteFilePath()))
        return false;

    CBDishParser parser(file.absoluteFilePath());
    if (!parser.parse())
        return false;

    CBDish dish = parser.getDish();
    CBMenuItem *item = new CBMenuItem(dish);
//    qDebug()<<"id: "<<item->getDish().getId().toString();
//    qDebug()<<"id: "<<item->getDish().getName();
    if (!this->_menuItemSet.add(item))
        return false;
//    qDebug()<<"id+: "<<_menuItemSet.get(0)->getDish().getName();

    return true;
}

void CBDishesScanner::scan()
{
    scan(_root);
}

void CBDishesScanner::scan(const QString root)
{
    _pathWalker.setRoot(root);
    _pathWalker.go();
}

void CBDishesScanner::clear()
{
    this->_menuItemSet.clear();
}
