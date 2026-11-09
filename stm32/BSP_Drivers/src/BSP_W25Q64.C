#include "BSP_W25Q64.h"
spi_flash_t g_wq25xx;
static bool g_is_init = false;
const uint8_t dummy = 0x00;

// 使能与取消使能
static void BSP_W25Qxx_CS_Enable()
{
  if (!g_is_init)
    return;
  HAL_GPIO_WritePin(g_wq25xx.gpio_port, g_wq25xx.nss_pin, GPIO_PIN_RESET);
}
static void BSP_W25Qxx_CS_Disable()
{
  if (!g_is_init)
    return;
  HAL_GPIO_WritePin(g_wq25xx.gpio_port, g_wq25xx.nss_pin, GPIO_PIN_SET);
}

// 检测标志位是否在忙
static bool BSP_W25Qxx_Is_Busy()
{
  return BSP_W25Qxx_Statue1_Reg() & W25Q64XX_STATUS_BUSY;
}

// 检测WEL是否被设置
static bool BSP_W25Qxx_Is_Wel_Enable()
{
  return BSP_W25Qxx_Statue1_Reg() & W25Q64XX_STATUS_WEL;
}

bool BSP_W25Qxx_Init(spi_flash_t* init)
{
  if (init == NULL)
  {
    return g_is_init;
  }
  g_wq25xx.block_size = init->block_size;
  g_wq25xx.chip_id = init->chip_id;
  g_wq25xx.gpio_port = init->gpio_port;
  g_wq25xx.hspi = init->hspi;
  g_wq25xx.mem_total_size = init->mem_total_size;
  g_wq25xx.nss_pin = init->nss_pin;
  g_wq25xx.page_size = init->page_size;
  g_wq25xx.sector_page = init->sector_page;
  g_is_init = true;
  uint32_t id = BSP_W25Qxx_ID();
  if (g_wq25xx.chip_id != id)
  {
    g_is_init = false;
    printf("ID error ,set id is 0x%x, current id is 0x%x\n", g_wq25xx.chip_id, id);
  }
  printf("BSP_W25Qxx_Init success!\nid is 0x%x\n", id);
  return true;
}

uint32_t BSP_W25Qxx_ID()
{
  if (!g_is_init)
    return 0x0;
  BSP_W25Qxx_CS_Enable();
  uint8_t cmd = CMD_W25QXX_JEDEC_ID;

  HAL_StatusTypeDef state = HAL_SPI_Transmit(g_wq25xx.hspi, &cmd, sizeof(cmd), HAL_MAX_DELAY);
  if (state != HAL_OK)
  {
    printf("BSP_W25Qxx_ID HAL_SPI_Transmit ID error , cmd is :0x%x, state :0x%x\n", cmd, state);
    goto EXIT;
  }
  uint8_t id[3] = {0};

  state = HAL_SPI_Receive(g_wq25xx.hspi, id, sizeof(id) / sizeof(id[0]), HAL_MAX_DELAY);
  if (state != HAL_OK)
  {
    printf("BSP_W25Qxx_ID HAL_SPI_Receive ID error , cmd is :0x%x, state :0x%x\n", cmd, state);
    goto EXIT;
  }
EXIT:
  BSP_W25Qxx_CS_Disable();
  return ((id[0] << 16) | (id[1] << 8) | (id[2] << 0));
}

uint8_t BSP_W25Qxx_Statue1_Reg()
{
  if (!g_is_init)
    return 0x0;
  BSP_W25Qxx_CS_Enable();
  uint8_t cmd = CMD_W25QXX_READ_STATUS_REG1;
  uint8_t status_reg = 0xFF;

  HAL_StatusTypeDef state = HAL_SPI_Transmit(g_wq25xx.hspi, &cmd, sizeof(cmd), HAL_MAX_DELAY);
  if (state != HAL_OK)
  {
    printf("BSP_W25Qxx_Statue1_Reg HAL_SPI_Transmit  error , cmd is :0x%x, state :0x%x\n", cmd, state);
    goto EXIT;
  }

  state = HAL_SPI_Receive(g_wq25xx.hspi, &status_reg, sizeof(status_reg), HAL_MAX_DELAY);
  if (state != HAL_OK)
  {
    printf("BSP_W25Qxx_Statue1_Reg HAL_SPI_Receive error , cmd is :0x%x, state :0x%x\n", cmd, state);
    goto EXIT;
  }
EXIT:
  BSP_W25Qxx_CS_Disable();
  return status_reg;
}

void BSP_W25Qxx_Write_Enable()
{
  if (!g_is_init)
    return;
  BSP_W25Qxx_CS_Enable();
  uint8_t cmd = CMD_W25QXX_WRITE_ENABLE;

  HAL_StatusTypeDef state = HAL_SPI_Transmit(g_wq25xx.hspi, &cmd, sizeof(cmd), HAL_MAX_DELAY);
  if (state != HAL_OK)
  {
    printf("BSP_W25Qxx_Write_Enable HAL_SPI_Transmit Enable error , cmd is :0x%x, state :0x%x\n", cmd, state);
  }
  BSP_W25Qxx_CS_Disable();
}

void BSP_W25Qxx_Write_Disable()
{
  if (!g_is_init)
    return;
  BSP_W25Qxx_CS_Enable();
  uint8_t cmd = CMD_W25QXX_WRITE_DISABLE;

  HAL_StatusTypeDef state = HAL_SPI_Transmit(g_wq25xx.hspi, &cmd, sizeof(cmd), HAL_MAX_DELAY);
  if (state != HAL_OK)
  {
    printf("BSP_W25Qxx_Write_Disable HAL_SPI_Transmit Disable error , cmd is :0x%x, state :0x%x\n", cmd, state);
  }
  BSP_W25Qxx_CS_Disable();
}

void BSP_W25Qxx_Wait_For_Write_Complete_Inefficient()
{
  if (!g_is_init)
    return;
  // BSP_W25Qxx_Statue1_Reg内部不断拉低再拉高很浪费时间
  while (BSP_W25Qxx_Statue1_Reg() & W25Q64XX_STATUS_BUSY)
  {
  };
}

void BSP_W25Qxx_Wait_For_Write_Complete_Efficient()
{
  if (!g_is_init)
    return;
  BSP_W25Qxx_CS_Enable();
  uint8_t cmd = CMD_W25QXX_READ_STATUS_REG1;

  HAL_StatusTypeDef state = HAL_SPI_Transmit(g_wq25xx.hspi, &cmd, sizeof(cmd), HAL_MAX_DELAY);
  if (state != HAL_OK)
  {
    printf("BSP_W25Qxx_Wait_For_Write_Complete_Efficient HAL_SPI_Transmit Read error , cmd is :0x%x, state :0x%x\n", cmd, state);
    goto EXIT;
  }
  uint8_t reg1 = 0xFF;

  // 在发起读取寄存器之后会自动一直返回，所以只需要给dummy数据过去就可以了，然后一直换回来做检验，直到校验里按位与是0时结束循环
  do
  {
    HAL_SPI_TransmitReceive(g_wq25xx.hspi, &dummy, &reg1, sizeof(dummy), HAL_MAX_DELAY);
  } while (reg1 & W25Q64XX_STATUS_BUSY);


EXIT:
  BSP_W25Qxx_CS_Disable();
}

void BSP_W25Qxx_Sector_Erase(uint32_t sector_address)
{
  if (!g_is_init)
    return;
  // 擦除必须扇区对齐
  if (sector_address & SECTOR_ADDRESS_MSK)
  {
    printf("BSP_W25Qxx_Sector_Erase error, address 0x%x not sector aligned\n", sector_address);
    return;
  }
  // 擦除地址不能超过总大小地址
  if (sector_address >= g_wq25xx.mem_total_size)
  {
    printf("BSP_W25Qxx_Sector_Erase error, address 0x%x out of range flash size\n", sector_address);
    return;
  }
  uint8_t cmd[4] = {CMD_W25QXX_SECTOR_ERASE, (uint8_t)(sector_address >> 16), (uint8_t)(sector_address >> 8), (uint8_t)(sector_address >> 0)};

  // 需要关闭禁止写入标志位
  if (!(BSP_W25Qxx_Is_Wel_Enable()))
  {
    BSP_W25Qxx_Write_Enable();
  }
  BSP_W25Qxx_CS_Enable();

  HAL_StatusTypeDef state = HAL_SPI_Transmit(g_wq25xx.hspi, cmd, sizeof(cmd) / sizeof(cmd[0]), HAL_MAX_DELAY);
  if (state != HAL_OK)
  {
    printf("BSP_W25Qxx_Sector_Erase HAL_SPI_Transmit error , cmd is :0x%x, state :0x%x\n", cmd[0], state);
    goto EXIT;
  }

EXIT:
  BSP_W25Qxx_CS_Disable();
  if (state == HAL_OK)
  {
    BSP_W25Qxx_Wait_For_Write_Complete_Efficient();
  }
  printf("BSP_W25Qxx_Sector_Erase success , cmd is :0x%x, state :0x%x\n", cmd[0], state);
}

void BSP_W25Qxx_Chip_Erase()
{
  if (!g_is_init)
    return;

  // 需要关闭禁止写入标志位
  if (!(BSP_W25Qxx_Is_Wel_Enable()))
  {
    BSP_W25Qxx_Write_Enable();
  }

  uint8_t cmd = CMD_W25QXX_CHIP_ERASE;
  BSP_W25Qxx_CS_Enable();
  HAL_StatusTypeDef state = HAL_SPI_Transmit(g_wq25xx.hspi, &cmd, sizeof(cmd), HAL_MAX_DELAY);
  if (state != HAL_OK)
  {
    printf("BSP_W25Qxx_Chip_Erase HAL_SPI_Transmit error,cmd is :0x%x, state :0x%x\n", cmd, state);
  }
  BSP_W25Qxx_CS_Disable();
  if (state == HAL_OK)
  {
    BSP_W25Qxx_Wait_For_Write_Complete_Efficient();
  }
}

bool BSP_W25Qxx_Read_Data(uint32_t read_address, uint8_t* rbuffer, uint32_t rsize)
{
  if (!g_is_init)
    return false;
  // 地址不能空，不能读取0个字节
  if (rbuffer == NULL || rsize == 0)
    return false;
  // 读取的地址不能超过总大小
  if (read_address + rsize > g_wq25xx.mem_total_size)
    return false;
  if (BSP_W25Qxx_Is_Busy())
  {
    BSP_W25Qxx_Wait_For_Write_Complete_Efficient();
  }
  bool ret = true;

  uint8_t cmd[4] = {CMD_W25QXX_READ_DATA, (uint8_t)(read_address >> 16), (uint8_t)(read_address >> 8), (uint8_t)(read_address >> 0)};
  BSP_W25Qxx_CS_Enable();
  HAL_StatusTypeDef state = HAL_SPI_Transmit(g_wq25xx.hspi, cmd, sizeof(cmd) / sizeof(cmd[0]), HAL_MAX_DELAY);
  if (state != HAL_OK)
  {
    printf("BSP_W25Qxx_Read_Data HAL_SPI_Transmit  error , cmd is :0x%x, state :0x%x\n", cmd[0], state);
    ret = false;
    goto EXIT;
  }

  state = HAL_SPI_Receive(g_wq25xx.hspi, rbuffer, rsize, HAL_MAX_DELAY);
  if (state != HAL_OK)
  {
    printf("BSP_W25Qxx_Read_Data HAL_SPI_Receive error , cmd is :0x%x, state :0x%x\n", cmd[0], state);
    ret = false;
    goto EXIT;
  }
  printf("BSP_W25Qxx_Read_Data success , cmd is :0x%x, state :0x%x\n", cmd[0], state);

EXIT:
  BSP_W25Qxx_CS_Disable();
  return ret;
}

bool BSP_W25Qxx_Page_Program(uint32_t page_address, uint16_t page_inner_offset, uint8_t* wbuffer, uint32_t wsize)
{
  if (!g_is_init)
    return false;
  if (wbuffer == NULL || wsize == 0)
    return false;
  // 不能超过一页大小
  if (page_inner_offset + wsize > g_wq25xx.page_size)
    return false;
  // 需要关闭禁止写入标志位
  if (!(BSP_W25Qxx_Is_Wel_Enable()))
  {
    BSP_W25Qxx_Write_Enable();
  }

  BSP_W25Qxx_CS_Enable();
  uint32_t write_page = page_address * g_wq25xx.page_size + page_inner_offset;
  uint8_t cmd[4] = {CMD_W25QXX_PAGE_PROGRAM, (uint8_t)(write_page >> 16), (uint8_t)(write_page >> 8), (uint8_t)(write_page >> 0)};
  bool ret = true;

  HAL_StatusTypeDef state = HAL_SPI_Transmit(g_wq25xx.hspi, cmd, sizeof(cmd) / sizeof(cmd[0]), HAL_MAX_DELAY);
  if (state != HAL_OK)
  {
    printf("BSP_W25Qxx_Page_Program HAL_SPI_Transmit  error , cmd is :0x%x, state :0x%x\n", cmd[0], state);
    ret = false;
    goto EXIT;
  }

  state = HAL_SPI_Transmit(g_wq25xx.hspi, wbuffer, wsize, HAL_MAX_DELAY);
  if (state != HAL_OK)
  {
    printf("BSP_W25Qxx_Page_Program HAL_SPI_Transmit error , cmd is :0x%x, state :0x%x\n", cmd[0], state);
    ret = false;
    goto EXIT;
  }
  printf("BSP_W25Qxx_Page_Program success , cmd is :0x%x, state :0x%x\n", cmd[0], state);

EXIT:
  BSP_W25Qxx_CS_Disable();
  if (state == HAL_OK)
  {
    BSP_W25Qxx_Wait_For_Write_Complete_Efficient();
  }
  printf("BSP_W25Qxx_Page_Program success , cmd is :0x%x, state :0x%x\n", cmd[0], state);
  return ret;
}

bool BSP_W25Qxx_Write_Data(uint32_t write_address, uint8_t* wbuffer, uint16_t wsize)
{
  if (!g_is_init)
    return false;
  if (wbuffer == NULL || wsize == 0)
    return false;
  if (write_address + wsize > g_wq25xx.mem_total_size)
  {
    printf("BSP_W25Qxx_Write_Data error, address out of range\n");
    return false;
  }
  uint32_t writen_bytes = 0;
  while (writen_bytes < wsize)
  {
    // 剩余数据
    uint32_t remaining_data = wsize - writen_bytes;

    // 计算页号
    uint16_t page_number = write_address / g_wq25xx.page_size;

    // 计算页内偏移
    uint16_t page_inner_offset = write_address % g_wq25xx.page_size;

    // 页内剩余空间
    uint16_t remaining_space = g_wq25xx.page_size - page_inner_offset;

    // 本次写入的数据量
    uint16_t to_writen = remaining_data > remaining_space ? remaining_space : remaining_data;

    if (!BSP_W25Qxx_Page_Program(page_number, page_inner_offset, &wbuffer[writen_bytes], to_writen))
    {
      printf("BSP_W25Qxx_Write_Data -> BSP_W25Qxx_Page_Program error\n");
      return false;
    }

    // 更新数据
    writen_bytes += to_writen;
    write_address += to_writen;
  }
  return true;
}
