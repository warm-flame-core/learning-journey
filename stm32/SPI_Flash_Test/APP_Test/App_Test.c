#include "App_Test.h"
void Test_W25Q64_Driver_Init(SPI_HandleTypeDef* hspi, GPIO_TypeDef* port, uint16_t pin)
{
  printf("--------------------------Test_W25Q64_Driver_Init--------------------------------\n");
  spi_flash_t init = {.page_size = 256,
                      .sector_page = 256 * 16,
                      .block_size = 256 * 16 * 16,
                      .mem_total_size = 256 * 16 * 16 * 128,
                      .chip_id = 0xEF4017,
                      .hspi = hspi,
                      .gpio_port = port,
                      .nss_pin = pin};
  BSP_W25Qxx_Init(&init);
}

void Test_W25Q64_Driver_Reg1()
{
  printf("--------------------------Test_W25Q64_Driver_Reg1--------------------------------\n");
  printf("register1 value id: 0x%x\n", BSP_W25Qxx_Statue1_Reg());
}

void Test_W25Q64_Driver_Write_Enable_Disable()
{
  printf("--------------------------Test_W25Q64_Driver_Write_Enable_Disable--------------------------------\n");
  uint8_t reg1 = BSP_W25Qxx_Statue1_Reg();
  printf("register1 value id: 0x%x\n", reg1);
  BSP_W25Qxx_Write_Enable();
  reg1 = BSP_W25Qxx_Statue1_Reg();
  printf("register1 value id: 0x%x\n", reg1);
  BSP_W25Qxx_Write_Disable();
  printf("register1 value id: 0x%x\n", reg1);
}
