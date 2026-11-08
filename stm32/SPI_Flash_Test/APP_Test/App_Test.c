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

void Test_W25Q64_Driver_Earse_Read()
{
  printf("--------------------------Test_W25Q64_Driver_Earse_Read--------------------------------\n");
  uint32_t start_adderss = 0;
  uint32_t end_adderss = 4096 - 4;
  uint32_t rx_buffer_first = 0;
  uint32_t rx_buffer_last = 0;
  BSP_W25Qxx_Read_Data(start_adderss, (uint8_t*)rx_buffer_first, sizeof(rx_buffer_first));
  BSP_W25Qxx_Read_Data(end_adderss, (uint8_t*)rx_buffer_last, sizeof(rx_buffer_last));
  printf("擦除前: rx_buffer_first: 0x%x, rx_buffer_last: 0x%x", rx_buffer_first, rx_buffer_last);

  BSP_W25Qxx_Sector_Earse(start_adderss);

  rx_buffer_first = 0;
  rx_buffer_last = 0;
  BSP_W25Qxx_Read_Data(start_adderss, (uint8_t*)rx_buffer_first, sizeof(rx_buffer_first));
  BSP_W25Qxx_Read_Data(end_adderss, (uint8_t*)rx_buffer_last, sizeof(rx_buffer_last));
  printf("擦除后: rx_buffer_first: 0x%x, rx_buffer_last: 0x%x", rx_buffer_first, rx_buffer_last);
}
