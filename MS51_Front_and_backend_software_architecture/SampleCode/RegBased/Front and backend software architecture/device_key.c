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
*文件名   : device_key.c
*作用     : 按键设备
*创建时间 : 2013.8.17
********************************************************************************
*/


#include "system.h"


#define ShortInterval       2		            // 短按按键间隔 >= 2
#define LongInterval        40		            // 长按按键间隔
#define DoubleHitInterval   20		            // 防按键双击误动间隔

static byte idata ScanFirstData = invalid;      // 第一次采集按键值
static byte idata ScanSecondData = invalid;     // 第二次采集按键值

static byte idata ScanCounter = 0;              // 按下按键计数器
static byte idata DoubleHitCounter = 0;         // 防按键双击误动计数器

/*******************************************************************************
* 函数名	: RemapKey
* 描述	    : 短按键映射
* 输入参数  : scanValue:扫描值
* 返回参数  : 短按按键映射值
********************************************************************************
*版本     作者            日期            说明
*V0.1    Wangsw        2013/09/27       初始版本
*******************************************************************************/
static byte RemapKey(byte scanValue) 
{
    switch(scanValue)
    {
        case 0x77: return(0);
        case 0x7B: return(1);
        case 0x7D: return(2);
        case 0x7E: return(3);
        case 0xB7: return(4);
        case 0xBB: return(5);
        case 0xBD: return(6);
        case 0xBE: return(7);
        case 0xD7: return(8);
        case 0xDB: return(9);
        case 0xDD: return(10);
        case 0xDE: return(11);
        case 0xE7: return(12);
        case 0xEB: return(13);
        case 0xED: return(14);
        case 0xEE: return(15);
        default  : return(invalid);
    }
}



/*******************************************************************************
* 函数名	: RemapLongKey
* 描述	    : 长按按键映射
* 输入参数  : scanValue 扫描值
* 返回参数  : 长按按键映射值
********************************************************************************
*版本     作者            日期            说明
*V0.1    Wangsw        2013/09/27       初始版本
*******************************************************************************/
static byte RemapLongKey(byte scanValue) 
{
    switch(scanValue)
    {
        case 0x77: return(0x30);
        case 0x7B: return(0x31);
        case 0x7D: return(0x32);
        case 0x7E: return(0x33);
        case 0xB7: return(0x34);
        case 0xBB: return(0x35);
        case 0xBD: return(0x36);
        case 0xBE: return(0x37);
        case 0xD7: return(0x38);
        case 0xDB: return(0x39);
        case 0xDD: return(0x3A);
        case 0xDE: return(0x3B);
        case 0xE7: return(0x3C);
        case 0xEB: return(0x3D);
        case 0xED: return(0x3E);
        case 0xEE: return(0x3F);
        default  : return(invalid);
    }	
}

/*****************************************************************************
* 函数名	: ScanPin
* 描述	    : P1口4*4矩阵按键扫描
* 输入参数  : 无
* 返回参数  : byte类型按键扫描值
*****************************************************************************/
static byte ScanPin(void)
{
    byte scan;
	
    P1 = 0x0F; Delay(1);            // P1.7~P1.4置0，延时，等待电路稳定
    scan = P1;                      // 读取低4位扫描值
    P1 = 0xF0; Delay(1);            // P1.3~P1.0置0，延时，等待电路稳定
    scan = scan | P1 ;              // 读取高四位扫描值并与低四位合并
	
    return(scan);                   // 返回值
}
/*******************************************************************************
* 函数名	: KeySystickRoutine
* 描述	    : 按键扫描服务程序，间隔10mS一次扫描获取按键信息
* 输入参数  : 无
* 返回参数  : 抛出长短两种按键值消息
********************************************************************************
*版本     作者            日期            说明
*V0.1    Wangsw        2013/09/27       初始版本
*******************************************************************************/
void KeySystickRoutine(void) 
{
    byte scan, key;

    scan = ScanPin();                                   // 获取扫描码
	
    if (scan != invalid)                                // 判断是否有按键按下
    {
        ScanCounter++;
		
        if (ScanCounter == 1)                           // 保存第一次扫描码
            ScanFirstData = scan;
        else if(ScanCounter == 2)                       // 保存第二次扫描码
            ScanSecondData = scan;
        else if (ScanCounter > LongInterval)            // 防止计数器循环
            ScanCounter = LongInterval;
    }
    else
	{
        if(DoubleHitCounter)                            // 防止连续双击按键
        {
            DoubleHitCounter--;
            ScanCounter = 0;
            return;
        }
        
        if (ScanCounter == 0)                           // 若没有扫描码，退出
            return;
        
        if ((ScanFirstData == invalid) || (ScanFirstData != ScanSecondData))
        {
            ScanCounter = 0;                            // 判断扫描码是否正确
            return;
        }

        if (ScanCounter == LongInterval)                // 判断是否为长按键
            key = RemapLongKey(ScanFirstData);          // 通过扫描码获取长按键值
        else if (ScanCounter >= ShortInterval)          // 判断是否为短按键
            key = RemapKey(ScanFirstData);              // 通过扫描码获取短按键值
        else
            key = invalid;                              // 误操作，无效
        
        if (key != invalid)                 
        {
            PostMessage(MessageKey, key);               // 发送按键
            DoubleHitCounter = DoubleHitInterval;       // 设定二次连击计数器
        }
        ScanFirstData = invalid;                        // 按键设备复位
        ScanSecondData = invalid;
        ScanCounter = 0;
	} 
}



