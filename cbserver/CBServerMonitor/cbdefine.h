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

#endif // CBDEFINE_H
