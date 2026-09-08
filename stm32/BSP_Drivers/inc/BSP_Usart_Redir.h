#ifndef __BSP_USART_REDIR_H
#define __BSP_USART_REDIR_H // 防止头文件多次包含

#ifdef __cplusplus
extern "C" {    // 用C语言编译
#endif

#include <stdio.h>
#include "stm32f1xx_hal.h"

extern UART_HandleTypeDef *ghuart;

void BSP_Usart_Init(UART_HandleTypeDef *huart);



#ifdef __cplusplus
}
#endif

#endif