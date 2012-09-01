#ifndef CBDEFINE_H
#define CBDEFINE_H

#define CBSERVERMONITOR_ROOT "lacarte"
#define CBSERVERMONITOR_DISHES_DIR "dishes"
#define CB_SETTINGS_SOURCE_DIR_SETTINGS_VAL "settings"

#define CB_PLUGING_PATH "plugins"

#define CB_DEFAULT_UI_CODED "UTF-8"

#ifdef WIN32
    #define CB_DEFAULT_XML_CODED "GB2312"
#else
    #define CB_DEFAULT_XML_CODED "GB2312"
#endif

#ifdef WIN32
    #define CBPATH_SPLITOR "/"
#else
    #define CBPATH_SPLITOR "/"
#endif

#define XML_TAG_LEFT_BUTTON_LIST "LeftButtonList"
#define XML_TAG_LEFT_BUTTON "LeftButton"
#define XML_TAG_ORDER_LOCATION_LIST "OrderLocationList"
#define XML_TAG_ORDER_LOCATION "OrderLocation"

#define XML_TAG_SETTINGS "Settings"
#define CB_SETTINGS_XML_ENCODING "cb.settings.xml.encoding"
#define CB_SETTINGS_SOURCE_DIR "cb.settings.source.dir"
#define CB_SETTINGS_SOURCE_DIR_DISHES "cb.settings.source.dir.dishes"
#define CB_SETTINGS_SOURCE_DIR_ORDERS "cb.settings.source.dir.orders"
#define CB_SETTINGS_SOURCE_DIR_SETTINGS "cb.settings.source.dir.settings"
#define CB_SETTINGS_LEFT_BUTTONS_TAGS_FILE "cb.settings.left.buttons.tags.file"
#define CB_SETTINGS_ORDER_LOCATIONS_FILE "cb.settings.left.locations.file"

#define CB_SETTINGS_LEFT_BUTTON_TEXT_SIZE "cb.settings.left.button.text.size"
#define CB_SETTINGS_GRIDVIEW_COLUMN_COUNT "cb.settings.grid.gridview.column.count"
#define CB_SETTINGS_ORDERING_DIALOG_MAX_ITEM_COUNT "cb.settings.ordering.dialog.max.item.count"

#define CB_SETTINGS_SOURCE_DIR_VAL "/sdcard/lacarte"
#define CB_SETTINGS_SOURCE_DIR_DISHES_VAL "dishes"
#define CB_SETTINGS_SOURCE_DIR_ORDERS_VAL "orders"
// not used yet
#define CB_SETTINGS_LEFT_BUTTONS_TAGS_FILE_VAL "/sdcard/lacarte/settings/left_buttons.xml"
// not used yet
#define CB_SETTINGS_ORDER_LOCATIONS_FILE_VAL "/sdcard/lacarte/settings/order_locations.xml"
#define CB_SETTINGS_XML_ENCODING_VAL "gb2312"
#define CB_SETTINGS_LEFT_BUTTON_TEXT_SIZE_VAL "20"
#define CB_SETTINGS_GRIDVIEW_COLUMN_COUNT_VAL "3"
#define CB_SETTINGS_ORDERING_DIALOG_MAX_ITEM_COUNT_VAL "50"

// not used yet
#define CB_MAX_LEFT_BUTTON_COUNT 10

#define CB_DEVICE_CHARSET_COUNT 2
static const char s_cb_device_charset[2][20] = {
    "gb2312",
    "utf-8",
};

#endif // CBDEFINE_H
