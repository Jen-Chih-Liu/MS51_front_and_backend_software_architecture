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
*�ļ���   : device.h
*����     : �豸��ͷ�ļ�
*����ʱ�� : 2013.8.17
********************************************************************************
*/

#ifndef __DEVICE_H
#define __DEVICE_H


/*���������Լ��������޸�*/
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
    TimerSystick            = 0,        // ϵͳ�����д���
    TimerMessage            = 1	        // ��ѭ����Ϣ�д���
}TimerModeEnum;	

typedef struct
{
    byte Second;                        //��
    byte Minute;                        //��
    byte Hour;                          //ʱ
    ushort Day;                         //��
}RtcStruct;


extern RtcStruct idata RtcEntity;

extern void KeySystickRoutine(void);

extern void RtcSystickRoutine(void);

extern void TimerSystickRoutine(void);


extern void InitRtc(void);

extern void InitUsart(void);

extern void InitSystick(void);



#endif

