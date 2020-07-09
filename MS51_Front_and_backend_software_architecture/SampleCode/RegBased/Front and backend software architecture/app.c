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
*�ļ���     : app.c
*����       : Ӧ�ò㣬ϵͳ���
*ԭ��       : ��
********************************************************************************
*�汾     ����            ����            ˵��
*V0.1    Wangsw        2013/09/23       ��ʼ�汾
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
            case MessageKey:            // ������Ϣ����
                EnterFunction(value);   // ����ָ�봦��ʽ
                //KeyProcess(value);    // ״̬������ʽ
                break;
            case MessageUsart:          // ������Ϣ����
                UsartProcess(value);
                break;
            //�������Ϣ��������
            default:                    // �����ʱ����Ϣ����
                Function(message);
                break;
        }
    }
}


