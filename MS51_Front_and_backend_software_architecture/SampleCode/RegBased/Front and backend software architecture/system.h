/*
********************************************************************************
*                              ʵ�õ�Ƭ��ϵͳ
*                                    MS
*
*                               ��оƬ:MCU51
*                           ��������οƼ����޹�˾
*
*                                ����:����ΰ
*                                ����:������
*                                ��ʶ:Wangsw
*
*                                QQ:26033613
*                               QQȺ:291235815
*                      ��̳:http://gongkong.eefocus.com/bbs/
********************************************************************************
*�ļ���   : system.h
*����     : ϵͳ��ȫ��ͷ�ļ�
*����ʱ�� : 2013.8.17
********************************************************************************
*/


#ifndef __SYSTEM_H
#define __SYSTEM_H


#include <string.h>
#include <stdio.h>
//#include "reg52x2.h"
//#include "MS51_16K.H"
/*
1�����Ͷ������C#����������C#��׼�����õ�Ϊint
2��char��C#��Ϊ16bit��unicode��keil C��Ϊ8bit
*/
//8bit���ֽ�
//typedef signed char         sbyte;
typedef unsigned char       byte;

//16bit˫�ֽ�
//typedef signed short        short         Ĭ�ϣ�����Ҫ����
typedef unsigned short      ushort;

//32bit���ֽ�
//typedef signed long         long;         Ĭ�ϣ�����Ҫ����
typedef unsigned long       ulong;

//�ַ���
typedef signed char *       string;

//��������
typedef unsigned char       bool;

typedef void (*function)(void);
#define Function(address)   (*((function)address))()






/*���峣��*/
#define true                1
#define false               0
#define null                ((void *) 0)
#define invalid             0xFF
#define MainClock           22118400        //MCUϵͳʱ��

#define SetBit(data, offset)     data |= 1 << offset     //��λĳλΪ1
#define ResetBit(data, offset)   data &= ~(1 << offset)  //��λĳλΪ0
#define GetBit(data, offset)     ((data >> offset) &0x01) //��ȡĳλ

#define UshortToByte1(data)     ((byte *)(&data))[0]//��ȡushort�������ݸ�λ     
#define UshortToByte0(data)     ((byte *)(&data))[1]//��ȡushort�������ݵ�λ

#define GetMessageType(message)            UshortToByte1(message)
#define GetMessageData(message)            UshortToByte0(message)

#define Assert(express)  if (!(express)){ENABLE_UART0_PRINTF; printf("\nAssert: " #express "\n");while(1);}   //(void)0


typedef enum
{
    MessageKey      = 0xFF,         //������Ϣ����
    MessageUsart    = 0xFE,         //������Ϣ���� 
    MessageInt0     = 0xFD,         //�ⲿ�ж�0��Ϣ����
    MessageInt1     = 0xFC,         //�ⲿ�ж�1��Ϣ����
    //���������
    MessageTimer    = 0xF0          //��Сֵ,��������������С����
}MessageEnum;


#include "device.h"

extern void EnterCritical(void);
extern void ExitCritical(void);

extern void InitMessageQueue(void);
extern void PostMessage(MessageEnum message, ushort value);
extern ushort PendMessageQueue(void);

extern void Delay(ushort delayClock);

extern void DelayUs(ushort delayTime);

extern void DelayMs(ushort delayTime);


extern byte HexToAscii(byte hex);

extern void PutByte(byte byte);
extern void PutString(string string, byte sum);

extern bool TimerStart(TimerModeEnum mode, ushort times, function registerFunction);
extern void TimerStop(byte id);

#endif
