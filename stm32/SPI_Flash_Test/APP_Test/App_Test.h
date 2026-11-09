#ifndef __APP_TEST_H
#define __APP_TEST_H // 防止头文件多次包含

#ifdef __cplusplus
extern "C"
{ // 用C语言编译
#endif

#include "BSP_W25Q64.h"
#include <string.h>
  // 测试初始化
  void Test_W25Q64_Driver_Init(SPI_HandleTypeDef* hspi, GPIO_TypeDef* port, uint16_t pin);

  // 测试读取第一个寄存器
  void Test_W25Q64_Driver_Reg1();

  // 测试读写使能
  void Test_W25Q64_Driver_Write_Enable_Disable();

  // 测试擦除写入
  void Test_W25Q64_Driver_Erase_Read();

  // 测试整片擦除
  void Test_W25Q64_Driver_ChipErase_Any_Read_Write();

#ifdef __cplusplus
}
#endif

#endif
