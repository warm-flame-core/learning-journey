#ifndef __BSP_LED_H
#define __BSP_LED_H // 防止头文件多次包含

#ifdef __cplusplus
extern "C" {    // 用C语言编译
#endif

#include <stdbool.h>
#include "stm32f1xx_hal.h"

typedef enum
{
  LED1 = 1,
  LED2,
  LED3,
  LED4,
  ALL
} LED_t;

typedef enum
{
  KEY1 = 1,
  KEY2,
  KEY3,
  KEY4
} KEY_t;



void BSP_LED_On(LED_t LED);
void BSP_LED_Off(LED_t LED);
void LED_Blink(LED_t LED);





#ifdef __cplusplus
}
#endif

#endif