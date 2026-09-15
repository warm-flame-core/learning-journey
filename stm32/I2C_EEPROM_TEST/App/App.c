#include "App.h"

config_t gconfig;

static void Config_Daley()
{
    printf("----------------------------------\n");
    printf("-----------打印配置信息------------\n");
    printf("magic:%x\n",gconfig.magic);
    printf("version:%x\n",gconfig.version);
    printf("LED:%d\n",gconfig.LED);
    printf("repact_cnt:%d\n",gconfig.repact_cnt);
    printf("delay_ms:%d\n",gconfig.delay_ms);
    printf("start_ms:%d\n",gconfig.start_ms);
}



static int Request_Input(const char *message)
{
    int chioce = 0;
    printf("%s\n",message);
    if(scanf("%d",&chioce) == 1)
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
    if(chioce == 1)
    {
        gconfig.magic = APP_MAGIC;
        gconfig.version = APP_VERSION;
        gconfig.LED = (uint8_t)Request_Input("选择LED灯[1~4],0表示全选>>");
        gconfig.repact_cnt = (uint8_t)Request_Input("选择LED灯闪烁次数>>");
        gconfig.delay_ms = (uint8_t)Request_Input("选择LED灯闪烁间隔毫秒[0~255]>>");
        gconfig.start_ms = (uint8_t)Request_Input("选择LED灯闪烁开始延迟[0~255]>>");

        Config_Daley();

        // 写入到EEPROM
    }
    else if(chioce == 2)
    {

    }
    else
    {

    }

}
void App_Run()
{
    printf("app_run\n");
}