#ifndef __BSP_W25Q64_H
#define __BSP_W25Q64_H // 防止头文件多次包含

#ifdef __cplusplus
extern "C"
{ // 用C语言编译
#endif
#include "stm32f1xx_hal.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
  typedef struct
  {
    uint32_t page_size;      // 页大小
    uint32_t sector_page;    // 扇区大小
    uint32_t block_size;     // 块大小
    uint32_t mem_total_size; // 总大小
    uint32_t chip_id;        // 芯片ID
    SPI_HandleTypeDef* hspi; // spi句柄
    GPIO_TypeDef* gpio_port; // 片选引脚端口
    uint16_t nss_pin;        // 片选针脚
  } spi_flash_t;

  bool BSP_W25Qxx_Init(spi_flash_t* init);
#ifdef __cplusplus
}
#endif

#endif
