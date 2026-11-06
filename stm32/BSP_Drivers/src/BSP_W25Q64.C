#include "BSP_W25Q64.h"
spi_flash_t g_wq25xx;
static bool g_is_init = false;
const int8_t dummy = 0x00;

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
  do
  {
    HAL_SPI_TransmitReceive(g_wq25xx.hspi, &dummy, &reg1, sizeof(dummy), HAL_MAX_DELAY);
  } while (reg1 & W25Q64XX_STATUS_BUSY);

EXIT:
  BSP_W25Qxx_CS_Disable();
}

void BSP_W25Qxx_Sector_Earse(uint32_t sector_address)
{
  if (!g_is_init)
    return;
  if (sector_address & SECTOR_ADDRESS_MSK)
  {
    printf("BSP_W25Qxx_Sector_Earse error, address 0x%x not sector aligned\n", sector_address);
    return;
  }
  if (sector_address >= g_wq25xx.mem_total_size)
  {
    printf("BSP_W25Qxx_Sector_Earse error, address 0x%x out of range flash size\n", sector_address);
    return;
  }
  uint8_t cmd[4] = {CMD_W25QXX_SECTOR_EARSE, (uint8_t)(sector_address >> 16), (uint8_t)(sector_address >> 8), (uint8_t)(sector_address >> 0)};
  BSP_W25Qxx_CS_Enable();
  HAL_StatusTypeDef state = HAL_SPI_Transmit(g_wq25xx.hspi, cmd, sizeof(cmd) / sizeof(cmd[0]), HAL_MAX_DELAY);
  if (state != HAL_OK)
  {
    printf("BSP_W25Qxx_Sector_Earse HAL_SPI_Transmit ID error , cmd is :0x%x, state :0x%x\n", cmd[0], state);
    goto EXIT;
  }
EXIT:
  BSP_W25Qxx_CS_Disable();
  if (state == HAL_OK)
  {
    BSP_W25Qxx_Wait_For_Write_Complete_Efficient();
  }
}
