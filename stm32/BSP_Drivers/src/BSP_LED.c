#include "BSP_LED.h"

// 关于灯的函数
// ture：点亮，false：熄灭
void BSP_LED_Control(LED_t LED, bool flag)
{
  GPIO_PinState state = flag ? GPIO_PIN_RESET : GPIO_PIN_SET;
  switch (LED)
  {
  case LED1:
    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_8, state);
    break;
  case LED2:
    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_9, state);
    break;
  case LED3:
    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_10, state);
    break;
  case LED4:
    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_11, state);
    break;
  default:
    break;
  }
}

void BSP_LED_On(LED_t LED)
{
  BSP_LED_Control(LED, true);
}
void BSP_LED_Off(LED_t LED)
{
  BSP_LED_Control(LED, false);
}

// 关于按键的函数
bool BSP_KEY_IsPressd_v1(KEY_t KEY)
{
  bool ret = false;
  switch (KEY)
  {
  case KEY1: // PG10
    ret = (HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_10) == GPIO_PIN_RESET);
    break;
  case KEY2: // PG6
    ret = (HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_6) == GPIO_PIN_RESET);
    break;
  case KEY3: // PG8
    ret = (HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_8) == GPIO_PIN_RESET);
    break;
  case KEY4: // PG7
    ret = (HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_7) == GPIO_PIN_RESET);
    break;
  default:
    break;
  }
  return ret;
}

void LED_Blink(LED_t LED)
{
  if (LED == ALL)
  {
    LED_t LEDs[4] = {LED1, LED2, LED3, LED4};
    int led_num = sizeof(LEDs) / sizeof(LEDs[0]);
    int cnt = 3;
    do
    {
      for (int i = 0; i < led_num; i++)
      {
        BSP_LED_On(LEDs[i]);
        HAL_Delay(500);
      }
      for (int i = 0; i < led_num; i++)
      {
        BSP_LED_Off(LEDs[i]);
        HAL_Delay(500);
      }
    } while (cnt--);
  }
  else
  {
    for (int i = 0; i < 3; i++)
    {
      BSP_LED_On(LED);
      HAL_Delay(500);

      BSP_LED_Off(LED);
      HAL_Delay(500);
    }
  }
}