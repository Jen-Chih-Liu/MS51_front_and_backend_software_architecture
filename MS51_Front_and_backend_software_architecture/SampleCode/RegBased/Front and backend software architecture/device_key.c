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
*�ļ���   : device_key.c
*����     : �����豸
*����ʱ�� : 2013.8.17
********************************************************************************
*/


#include "system.h"


#define ShortInterval       2		            // �̰�������� >= 2
#define LongInterval        40		            // �����������
#define DoubleHitInterval   20		            // ������˫���󶯼��

static byte idata ScanFirstData = invalid;      // ��һ�βɼ�����ֵ
static byte idata ScanSecondData = invalid;     // �ڶ��βɼ�����ֵ

static byte idata ScanCounter = 0;              // ���°���������
static byte idata DoubleHitCounter = 0;         // ������˫���󶯼�����

/*******************************************************************************
* ������	: RemapKey
* ����	    : �̰���ӳ��
* �������  : scanValue:ɨ��ֵ
* ���ز���  : �̰�����ӳ��ֵ
********************************************************************************
*�汾     ����            ����            ˵��
*V0.1    Wangsw        2013/09/27       ��ʼ�汾
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
* ������	: RemapLongKey
* ����	    : ��������ӳ��
* �������  : scanValue ɨ��ֵ
* ���ز���  : ��������ӳ��ֵ
********************************************************************************
*�汾     ����            ����            ˵��
*V0.1    Wangsw        2013/09/27       ��ʼ�汾
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
* ������	: ScanPin
* ����	    : P1��4*4���󰴼�ɨ��
* �������  : ��
* ���ز���  : byte���Ͱ���ɨ��ֵ
*****************************************************************************/
static byte ScanPin(void)
{
    byte scan;
	
    P1 = 0x0F; Delay(1);            // P1.7~P1.4��0����ʱ���ȴ���·�ȶ�
    scan = P1;                      // ��ȡ��4λɨ��ֵ
    P1 = 0xF0; Delay(1);            // P1.3~P1.0��0����ʱ���ȴ���·�ȶ�
    scan = scan | P1 ;              // ��ȡ����λɨ��ֵ�������λ�ϲ�
	
    return(scan);                   // ����ֵ
}
/*******************************************************************************
* ������	: KeySystickRoutine
* ����	    : ����ɨ�������򣬼��10mSһ��ɨ���ȡ������Ϣ
* �������  : ��
* ���ز���  : �׳��������ְ���ֵ��Ϣ
********************************************************************************
*�汾     ����            ����            ˵��
*V0.1    Wangsw        2013/09/27       ��ʼ�汾
*******************************************************************************/
void KeySystickRoutine(void) 
{
    byte scan, key;

    scan = ScanPin();                                   // ��ȡɨ����
	
    if (scan != invalid)                                // �ж��Ƿ��а�������
    {
        ScanCounter++;
		
        if (ScanCounter == 1)                           // �����һ��ɨ����
            ScanFirstData = scan;
        else if(ScanCounter == 2)                       // ����ڶ���ɨ����
            ScanSecondData = scan;
        else if (ScanCounter > LongInterval)            // ��ֹ������ѭ��
            ScanCounter = LongInterval;
    }
    else
	{
        if(DoubleHitCounter)                            // ��ֹ����˫������
        {
            DoubleHitCounter--;
            ScanCounter = 0;
            return;
        }
        
        if (ScanCounter == 0)                           // ��û��ɨ���룬�˳�
            return;
        
        if ((ScanFirstData == invalid) || (ScanFirstData != ScanSecondData))
        {
            ScanCounter = 0;                            // �ж�ɨ�����Ƿ���ȷ
            return;
        }

        if (ScanCounter == LongInterval)                // �ж��Ƿ�Ϊ������
            key = RemapLongKey(ScanFirstData);          // ͨ��ɨ�����ȡ������ֵ
        else if (ScanCounter >= ShortInterval)          // �ж��Ƿ�Ϊ�̰���
            key = RemapKey(ScanFirstData);              // ͨ��ɨ�����ȡ�̰���ֵ
        else
            key = invalid;                              // ���������Ч
        
        if (key != invalid)                 
        {
            PostMessage(MessageKey, key);               // ���Ͱ���
            DoubleHitCounter = DoubleHitInterval;       // �趨��������������
        }
        ScanFirstData = invalid;                        // �����豸��λ
        ScanSecondData = invalid;
        ScanCounter = 0;
	} 
}



