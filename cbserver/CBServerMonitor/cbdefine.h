#ifndef CBDEFINE_H
#define CBDEFINE_H

#define CBSERVERMONITOR_ROOT "lacarte"
#define CBSERVERMONITOR_DISHES_DIR "dishes"
#define CBSERVERMONITOR_SETTINGS_DIR "settings"

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

#define CB_DEFAULT_ITEM_COL 3
#define CB_MAX_LEFT_BUTTON_COUNT 10
#define CB_DEFAULT_LEFT_BUTTON_FONT_SIZE 20
#define CB_DEFAULT_DISH_ITEM_ORDER_MAX_COUNT 50

#define CB_DEFAULT_DEVICE_CHARSET "gb2312"
#define CB_DEVICE_CHARSET_COUNT 2
static const char s_cb_device_charset[2][20] = {
    "gb2312",
    "utf-8",
};

#endif // CBDEFINE_H
