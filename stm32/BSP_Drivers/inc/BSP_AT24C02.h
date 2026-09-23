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
#define DEV_TOTAL_SIZE (256)    // EEPROM的块大小
#define READ_TIMEOUT_MS (50)    // 读取的时候的阻塞时间
#define WRITE_TIMEOUT_MS (50)   // 写入的时候的阻塞时间

typedef struct 
{
    I2C_HandleTypeDef * pi2c;   // I2C设备句柄指针
    uint16_t dev_address;        // EEPROM的设备地址
    uint8_t page_size;          // EEPROM的页大小
    bool is_init;
}eeprom_t;


bool BSP_AT24C02_Init(I2C_HandleTypeDef * i2c);
bool BSP_AT24C02_Read_Page(uint16_t start_address, void *data_out, uint8_t data_len);
bool BSP_AT24C02_Write_Page(void *data_in, uint8_t data_len);
    
#ifdef __cpluscplus
}
#endif

#endif