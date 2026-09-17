#ifndef __BSP_AT24C02_H
#define __BSP_AT24C02_H

#ifdef __cpluscplus
extern "C"
{
#endif

#include <stdbool.h>
#include "stm32f1xx_hal.h"

#define DEV_ADDRESS (0x50)   // EEPROM地址
#define PAGE_SIZE (8)         // EEPROM页大小
#define SCAN_RETYIES (2)      // 请求次数
#define SCAN_TIME_MS (5)      // 请求间隔毫秒

typedef struct 
{
    I2C_HandleTypeDef * pi2c;   // I2C设备句柄指针
    uint16_t dev_address;        // EEPROM的设备地址
    uint8_t page_size;          // EEPROM的页大小
    bool is_init;
}eeprom_t;


bool BSP_AT24C02_Init(I2C_HandleTypeDef * i2c);
bool AT24C02_Read_Page_Data(void *date_out, uint8_t date_len);
bool AT24C02_Write_Page_Data(void *date_in, uint8_t date_len);
    
#ifdef __cpluscplus
}
#endif

#endif