#ifndef STX_LOG_H
#define STX_LOG_H
#include "stx_uart2.h"

#define ESC_START     "\033["
#define ESC_END       "\033[0m"
#define COLOR_FATAL   "31;40;5m"
#define COLOR_ALERT   "31;40;1m"
#define COLOR_CRIT    "31;40;1m"
#define COLOR_ERROR   "31;40;1m"
#define COLOR_WARN    "33;40;1m"
#define COLOR_NOTICE  "34;40;1m"
#define COLOR_INFO    "32;40;1m"
#define COLOR_DEBUG   "36;40;1m"
#define COLOR_TRACE   "37;40;1m"

enum{
    T_INFO = 0,
    T_DEBUG,
    T_WARNNING,
    T_ERROR,
};
static unsigned int debug_level = T_INFO;

#define Stx_Msg_Info(format, args...) do{\
    if(debug_level <= T_INFO){\
        debug( ESC_START COLOR_INFO "[INFO]-[%s]-[%d]:" format ESC_END, __FUNCTION__ , __LINE__, ##args);\
    }\
}while(0)

#define Stx_Msg_Debug(format, args...) do{\
    if(debug_level <= T_DEBUG){\
        debug( ESC_START COLOR_DEBUG "[DEBUG]-[%s]-[%d]:" format ESC_END, __FUNCTION__ , __LINE__, ##args);\
    }\
    }while(0)

#define Stx_Msg_Warn(format, args...) do{\
    if(debug_level <= T_WARNNING){\
        debug( ESC_START COLOR_WARN "[WARNNING]-[%s]-[%d]:" format ESC_END, __FUNCTION__ , __LINE__, ##args);\
    }\
    }while(0)

#define Stx_Msg_Err(format, args...) do{\
    if(debug_level <= T_ERROR){\
        debug( ESC_START COLOR_ERROR "[ERROR]-[%s]-[%d]:" format ESC_END, __FUNCTION__ , __LINE__, ##args);\
    }\
    }while(0)

#endif

