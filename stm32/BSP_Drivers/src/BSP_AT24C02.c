#include "BSP_AT24C02.h"

eeprom_t at24c02;

bool BSP_AT24C02_Init(I2C_HandleTypeDef *i2c)
{
    if (!i2c)
        return false;
    at24c02.pi2c = i2c;
    at24c02.dev_address = DEV_ADDRESS << 1; //
    at24c02.page_size = PAGE_SIZE;
    at24c02.is_init = false;
    if (HAL_OK == HAL_I2C_IsDeviceReady(at24c02.pi2c, at24c02.dev_address, SCAN_RETYIES, SCAN_TIME_MS))
        at24c02.is_init = true;
    return true;
}

static bool BSP_AT24C02_Ready()
{
    if(!at24c02.is_init)
        return false;
    return HAL_OK == HAL_I2C_IsDeviceReady(at24c02.pi2c,at24c02.dev_address,POLL_RETYIES,POLL_TIME_MS);
}

bool BSP_AT24C02_Read_Page(uint16_t start_address, void *data_out, uint8_t data_len)
{
    if (!at24c02.is_init || !data_out || data_len == 0)
        return false;
    if (start_address + data_len > DEV_TOTAL_SIZE)
        return false;

    HAL_StatusTypeDef state = HAL_I2C_Mem_Read(at24c02.pi2c, at24c02.dev_address, start_address, I2C_MEMADD_SIZE_8BIT, data_out, data_len, READ_TIMEOUT_MS);
    return state;
}

// 单页内写入
static bool BSP_AT24C02_Write_Page(uint16_t start_address, void *data_in, uint8_t data_len)
{
    if (!at24c02.is_init || !data_in || data_len == 0)
        return false;
    // 检查跨页写入
    uint16_t page_num = start_address / at24c02.page_size;
    uint16_t page_offset = start_address % at24c02.page_size;
    if (page_offset + data_len > at24c02.page_size)
        return false;

    HAL_StatusTypeDef state = HAL_I2C_Mem_Write(at24c02.pi2c, at24c02.dev_address, start_address, I2C_MEMADD_SIZE_8BIT, data_in, data_in, WRITE_TIMEOUT_MS);
    if (state != HAL_OK)
        return false;

    
    return BSP_AT24C02_Ready();
}

// 任意页写入
bool BSP_AT24C02_Write()
{
}