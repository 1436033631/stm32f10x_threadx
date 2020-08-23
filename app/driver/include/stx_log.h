#ifndef STX_LOG_H
#define STX_LOG_H
#include "stx_uart2.h"
#include "tx_api.h"

#define STX_NG        1
#define STX_OK        0
#define STX_SHELL_GTE_TIME tx_time_get()

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
        debug( ESC_START COLOR_INFO "[%8d]-[INFO]-[%s]-[%d]:" format ESC_END, STX_SHELL_GTE_TIME, __FUNCTION__ , __LINE__, ##args);\
    }\
}while(0)

#define Stx_Msg_Debug(format, args...) do{\
    if(debug_level <= T_DEBUG){\
        debug( ESC_START COLOR_DEBUG "[%8d]-[DEBUG]-[%s]-[%d]:" format ESC_END, STX_SHELL_GTE_TIME, __FUNCTION__ , __LINE__, ##args);\
    }\
    }while(0)

#define Stx_Msg_Warn(format, args...) do{\
    if(debug_level <= T_WARNNING){\
        debug( ESC_START COLOR_WARN "[%8d]-[WARNNING]-[%s]-[%d]:" format ESC_END, STX_SHELL_GTE_TIME, __FUNCTION__ , __LINE__, ##args);\
    }\
    }while(0)

#define Stx_Msg_Err(format, args...) do{\
    if(debug_level <= T_ERROR){\
        debug( ESC_START COLOR_ERROR "[%8d]-[ERROR]-[%s]-[%d]:" format ESC_END, STX_SHELL_GTE_TIME, __FUNCTION__ , __LINE__, ##args);\
    }\
    }while(0)

#endif

