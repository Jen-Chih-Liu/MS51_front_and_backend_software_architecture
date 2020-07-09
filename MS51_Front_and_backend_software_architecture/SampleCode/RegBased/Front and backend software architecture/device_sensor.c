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
*�ļ���     : device_sensor.c
*����       : �����ⲿ�������ж�����
*ԭ��       : 
********************************************************************************
*�汾     ����            ����            ˵��
*V0.1    Wangsw        2013/09/29       ��ʼ�汾
********************************************************************************
*/

#include "system.h"


/*******************************************************************************
* ������	: InitInterrupt0
* ����	    : ��ʼ���ⲿ�ж�0
* �������  : enable ��������,ʹ���ⲿ�жϣ�edge �������������ش���
* ���ز���  : 
********************************************************************************
*�汾     ����            ����            ˵��
*V0.1    Wangsw        2013/09/29       ��ʼ�汾
*******************************************************************************/
void InitInterrupt0(bool enable, bool edge)
{
    IE0 = 0;						
    IT0 = edge;
    EX0 = enable;
}

/*******************************************************************************
* ������	: Interrupt0Handler
* ����	    : �ⲿ�ж�0��������
* �������  : ��
* ���ز���  : ��
********************************************************************************
*�汾     ����            ����            ˵��
*V0.1    Wangsw        2013/09/29       ��ʼ�汾
*******************************************************************************/
void Interrupt0Handler(void) interrupt 0
{
    //PostMessage(Int0MessageType, 0); 
    //IE0 = 0;
}

/*******************************************************************************
* ������	: InitInterrupt1
* ����	    : ��ʼ���ⲿ�ж�1
* �������  : enable ��������,ʹ���ⲿ�жϣ�edge �������������ش���
* ���ز���  : 
********************************************************************************
*�汾     ����            ����            ˵��
*V0.1    Wangsw        2013/09/29       ��ʼ�汾
*******************************************************************************/
void InitInterrupt1(bool enable, bool edge)
{
    IE1 = 0;						
    IT1 = edge;
    EX1 = enable;
}

/*******************************************************************************
* ������	: ExternInterrupt1Handler
* ����	    : �ⲿ�ж�1��������
* �������  : ��
* ���ز���  : ��
********************************************************************************
*�汾     ����            ����            ˵��
*V0.1    Wangsw        2013/09/29       ��ʼ�汾
*******************************************************************************/
void Interrupt1Handler(void) interrupt 2
{
    //PostMessage(Int1MessageType, 0);
    //IE1 = 0;
}