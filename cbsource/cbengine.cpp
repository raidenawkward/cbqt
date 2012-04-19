#include "cbengine.h"
#include "cbdishesscanner.h"

CBEngine::CBEngine()
    : _menuItemsSet(NULL)
{
}

CBEngine::~CBEngine()
{
    if (_menuItemsSet)
        delete _menuItemsSet;
}

bool CBEngine::loadMenuItems(const QString path)
{
    if (_menuItemsSet)
        delete _menuItemsSet;

    CBDishesScanner scanner(path);
    scanner.scan();

    CBMenuItemsSet *set = scanner.getMenuItemSet();
    _menuItemsSet = set;

    return true;
}

CBMenuItemsSet* CBEngine::getMenuItemsSet()
{
    return _menuItemsSet;
}
