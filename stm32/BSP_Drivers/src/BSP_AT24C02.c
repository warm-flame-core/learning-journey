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
bool AT24C02_Read_Page_Data(uint16_t start_address, void *date_out, uint8_t date_len)
{
    if(!at24c02.is_init || !date_out || date_len == 0)
        return false;
    if(start_address + date_len > DEV_TOTAL_SIZE)
        return false;
    return true;
}
bool AT24C02_Write_Page_Data(void *date_in, uint8_t date_len)
{
    return true;
}