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
*文件名   : device.h
*作用     : 设备总头文件
*创建时间 : 2013.8.17
********************************************************************************
*/

#ifndef __DEVICE_H
#define __DEVICE_H


/*按键根据自己定义来修改*/
typedef enum 
{
    AddKey                  = 0x00,
    AddLongKey              = 0x30,
    
    SubKey                  = 0x04,
    SubLongKey              = 0x34,

    AssistUpKey             = 0x01,
    AssistUpLongKey         = 0x31,

    AssistDownKey           = 0x05,
    AssistDownLongKey       = 0x35,
    
    SaveKey                 = 0x02,
    SaveLongKey             = 0x32,

    TextBoxFocusKey         = 0x06,
    FormFocusLongKey        = 0x36,
    
    StartKey                = 0x03,
    StartLongKey            = 0x33,
    
    StopKey                 = 0x07,
    StopLongKey             = 0x37
}KeyEnum;

typedef enum 
{
    TimerSystick            = 0,        // 系统节拍中处理
    TimerMessage            = 1	        // 大循环消息中处理
}TimerModeEnum;	

typedef struct
{
    byte Second;                        //秒
    byte Minute;                        //分
    byte Hour;                          //时
    ushort Day;                         //天
}RtcStruct;


extern RtcStruct idata RtcEntity;

extern void KeySystickRoutine(void);

extern void RtcSystickRoutine(void);

extern void TimerSystickRoutine(void);


extern void InitRtc(void);

extern void InitUsart(void);

extern void InitSystick(void);



#endif

