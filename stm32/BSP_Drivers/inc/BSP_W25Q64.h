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

#define CMD_W25QXX_JEDEC_ID 0x9F
#define CMD_W25QXX_READ_STATUS_REG1 0x05
#define CMD_W25QXX_WRITE_ENABLE 0x06
#define CMD_W25QXX_WRITE_DISABLE 0x04
#define CMD_W25QXX_SECTOR_EARSE 0X20
#define CMD_W25QXX_READ_DATA 0X03
#define CMD_W25QXX_WRITE_PROGRAM 0X02

#define W25Q64XX_STATUS_BUSY 0x01
#define SECTOR_ADDRESS_MSK 0xFFF

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

  // 初始化工作
  bool BSP_W25Qxx_Init(spi_flash_t* init);

  // 获取W25Qxx的JEDEC_ID
  uint32_t BSP_W25Qxx_ID();

  // 获取W25Qxx的第一个寄存器所有值
  uint8_t BSP_W25Qxx_Statue1_Reg();

  // 打开W25Qxx写使能
  void BSP_W25Qxx_Write_Enable();

  // 关闭W25Qxx写使能
  void BSP_W25Qxx_Write_Disable();

  // 等待写入完成
  void BSP_W25Qxx_Wait_For_Write_Complete_Inefficient();
  void BSP_W25Qxx_Wait_For_Write_Complete_Efficient();

  // 扇区擦除
  void BSP_W25Qxx_Sector_Earse(uint32_t sector_address);

  // 按地址读取
  bool BSP_W25Qxx_Read_Data(uint32_t read_address, uint8_t* rbuffer, uint32_t rsize);


#ifdef __cplusplus
}
#endif

#endif
