#include "App_Test.h"
void Test_W25Q64_Driver_Init(SPI_HandleTypeDef* hspi, GPIO_TypeDef* port, uint16_t pin)
{
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
  printf("register1 value id: 0x%x\n", BSP_W25Qxx_Statue1_Reg());
}
