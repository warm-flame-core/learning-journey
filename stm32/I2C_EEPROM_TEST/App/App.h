#ifndef __APP_H
#define __APP_H

#ifdef __cpluscplus
extern "C"
{
#endif

#include <stdint.h>
#include "BSP_AT24C02.h"
#include "BSP_LED.h"
#include "BSP_Usart_Redir.h"

#define APP_MAGIC 0x35
#define APP_VERSION 0x01

typedef struct _config_t
{
    uint8_t magic;          // 魔数，参考不同类型的文件分辨方法
    uint8_t version;        // 配置文件版本
    uint8_t LED;            // 闪哪个灯
    uint8_t repact_cnt;     // 闪灯次数
    uint16_t delay_ms;      // 闪灯中间停止多久，单位：ms
    uint16_t start_ms       // 开始闪灯的时间，单位：ms
}config_t;



    void App_Init();
    void App_Run();

#ifdef __cpluscplus
}
#endif

#endif