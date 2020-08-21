//
// Created by YangYongbao on 2017/3/18.
//

#ifndef STX_UART2_H
#define STX_UART2_H

#include <stdarg.h>


void stx_uart2_init(void);

void debug(const char *format, ...);

void stx_shell_init(void);

#endif //STM32F10X_MAKEFILE_FREERTOS_UART_LOG_H
