#include "BSP_Usart_Redir.h"

UART_HandleTypeDef *ghuart = NULL;

void BSP_Usart_Init(UART_HandleTypeDef *huart)
{
    ghuart = huart;
}

int fputc(int ch, FILE *fp)
{
    UNUSED(fp); // 用于消除警告的宏
    if (NULL != ghuart)
    {
        if (HAL_UART_Transmit(ghuart, (uint8_t *)&ch, 1, HAL_MAX_DELAY) == HAL_OK)
        {
            return ch;
        }
        return EOF;
    }
    else
    {
        return EOF;
    }
}

int fgetc(FILE *fp)
{
    UNUSED(fp); // 消除警告的宏
    if (NULL != ghuart)
    {
        uint8_t ch = 0;
        while (1)
        {
            if (HAL_UART_Receive(ghuart, &ch, 1, HAL_MAX_DELAY) != HAL_OK)
            {
                return EOF;
            }
            // 到这就一定读取成功了
            if (ch != '\r')
            {
                return (int)ch;
            }
        }
    }
    else
    {
        return EOF;
    }
}