#include "App.h"

config_t gconfig;

static void Config_Daley()
{
    printf("----------------------------------\n");
    printf("-----------打印配置信息------------\n");
    printf("magic:%x\n", gconfig.magic);
    printf("version:%x\n", gconfig.version);
    printf("LED:%d\n", gconfig.LED);
    printf("repact_cnt:%d\n", gconfig.repact_cnt);
    printf("delay_ms:%d\n", gconfig.delay_ms);
    printf("start_ms:%d\n", gconfig.start_ms);
}

static int Request_Input(const char *message)
{
    int chioce = 0;
    printf("%s\n", message);
    if (scanf("%d", &chioce) == 1)
    {
        return chioce;
    }
    printf("输入错误");
    return EOF;
}

void App_Init()
{
    // 获取用户选择
    // 1.修改配置信息   2.使用配置信息
    uint8_t chioce = Request_Input("1.修改配置信息   2.使用配置信息");
    if (chioce == 1)
    {
        gconfig.magic = APP_MAGIC;
        gconfig.version = APP_VERSION;
        gconfig.LED = (uint8_t)Request_Input("选择LED灯[1~4],0表示全选>>");
        gconfig.repact_cnt = (uint8_t)Request_Input("选择LED灯闪烁次数>>");
        gconfig.delay_ms = (uint16_t)Request_Input("选择LED灯闪烁间隔毫秒>>");
        gconfig.start_ms = (uint16_t)Request_Input("选择LED灯闪烁开始延迟>>");

        Config_Daley();

        // 写入到EEPROM
        AT24C02_Write_Page_Data(&gconfig, sizeof(gconfig));
    }
    else if (chioce == 2)
    {
        // 读取EEPROM
        AT24C02_Read_Page_Data(&gconfig, sizeof(gconfig));
    }
    else
    {
        printf("选择无效请重新选择");
    }
}
void App_Run()
{
    if (gconfig.magic == APP_MAGIC && gconfig.version == APP_VERSION)
    {
        printf("%d ms后开始闪灯", (int)gconfig.start_ms);
        HAL_Delay((int)gconfig.start_ms);
        LED_Blink_Version2(gconfig.LED, gconfig.repact_cnt, gconfig.delay_ms);
    }
}