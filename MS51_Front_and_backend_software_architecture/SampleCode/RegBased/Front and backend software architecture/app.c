/*
********************************************************************************
*                              实用单片机系统
*                                    MS
*
*                               主芯片:MCU51
*                           深圳市雨滴科技有限公司
*
*                                作者:王绍伟
*                                网名:凤舞天
*                                标识:Wangsw
*
*                                QQ:26033613
*                               QQ群:291235815
*                      论坛:http://gongkong.eefocus.com/bbs/
********************************************************************************
*文件名     : app.c
*作用       : 应用层，系统入口
*原理       : 无
********************************************************************************
*版本     作者            日期            说明
*V0.1    Wangsw        2013/09/23       初始版本
********************************************************************************
*/



#include "system.h"
#include "app.h"


void Init(void)
{			
    InitRtc();
    
    InitUsart();

    InitMmi();

    InitMessageQueue();

    InitSystick();
}

int main(void)
{
    ushort idata message;
    byte idata type, value;
    
    Init();

    while(true)
    {
        message = PendMessageQueue();
        type = GetMessageType(message);
        value = GetMessageData(message);
        switch(type)						
        {
            case MessageKey:            // 按键消息处理
                EnterFunction(value);   // 函数指针处理方式
                //KeyProcess(value);    // 状态机处理方式
                break;
            case MessageUsart:          // 串口消息处理
                UsartProcess(value);
                break;
            //请填充消息及处理函数
            default:                    // 软件定时器消息处理
                Function(message);
                break;
        }
    }
}


