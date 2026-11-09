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

void Test_W25Q64_Driver_Erase_Read()
{
  printf("--------------------------Test_W25Q64_Driver_Erase_Read--------------------------------\n");
  uint32_t start_adderss = 0;
  uint32_t end_adderss = 4096 - 4;
  uint32_t rx_buffer_first = 0;
  uint32_t rx_buffer_last = 0;

  uint32_t data = 0;
  BSP_W25Qxx_Page_Program(0, 0, (uint8_t*)&data, sizeof(data));

  BSP_W25Qxx_Read_Data(start_adderss, (uint8_t*)&rx_buffer_first, sizeof(rx_buffer_first));
  BSP_W25Qxx_Read_Data(end_adderss, (uint8_t*)&rx_buffer_last, sizeof(rx_buffer_last));
  printf("擦除前: rx_buffer_first: 0x%x, rx_buffer_last: 0x%x\n", rx_buffer_first, rx_buffer_last);

  BSP_W25Qxx_Sector_Erase(start_adderss);

  rx_buffer_first = 0;
  rx_buffer_last = 0;
  BSP_W25Qxx_Read_Data(start_adderss, (uint8_t*)&rx_buffer_first, sizeof(rx_buffer_first));
  BSP_W25Qxx_Read_Data(end_adderss, (uint8_t*)&rx_buffer_last, sizeof(rx_buffer_last));
  printf("擦除后: rx_buffer_first: 0x%x, rx_buffer_last: 0x%x\n", rx_buffer_first, rx_buffer_last);
}


uint8_t buffer[4096 * 2];

static void PrintData(int step)
{
  printf("------------------Step: %d-------------\n", step);
  // 先打印前8个字节
  for (int i = 0; i < 8; i++)
    printf("0x%x ", buffer[i]);
  printf("\n");
  // 先打印后8个字节
  for (int i = 4096 * 2 - 8; i < 4096 * 2; i++)
    printf("0x%x ", buffer[i]);
  printf("\n");
}

void Test_W25Q64_Driver_ChipErase_Any_Read_Write()
{
  printf("--------------------------Test_W25Q64_Driver_ChipErase_Any_Read_Write--------------------------------\n");
  // 1. 确定两个sector
  uint32_t start_address = 0x0;
  uint16_t size = 4096 * 2;
  // 2. 先读取
  BSP_W25Qxx_Read_Data(start_address, buffer, size);

  // 3. 挑选若干数据
  PrintData(1);

  // 4. 擦除两页
  BSP_W25Qxx_Sector_Erase(0);
  BSP_W25Qxx_Sector_Erase(4096);
  BSP_W25Qxx_Read_Data(start_address, buffer, size);
  PrintData(2);

  // 5. 写入数据
  memset(buffer, 0, sizeof(buffer));
  BSP_W25Qxx_Write_Data(start_address, buffer, size);
  BSP_W25Qxx_Read_Data(start_address, buffer, size);
  PrintData(3);

  // 6. 整盘擦除
  BSP_W25Qxx_Chip_Erase();

  // 7. 读取
  BSP_W25Qxx_Read_Data(start_address, buffer, size);
  PrintData(4);
}
