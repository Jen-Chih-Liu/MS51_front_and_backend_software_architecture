#include "system.h"
#include "MS51_16K.H"
extern void InitMmi(void);
typedef void (*MmiFunction)(KeyEnum key);
extern void UsartProcess(byte value);
extern MmiFunction EnterFunction;
/************************************************************************************************************
*    Timer2 interrupt subroutine
************************************************************************************************************/
void Timer2_ISR (void) interrupt 5
{
    _push_(SFRS);     
    clr_T2CON_TF2;                                //Clear Timer2 Interrupt Flag
    TimerSystickRoutine();   
	  RtcSystickRoutine();   
    _pop_(SFRS);
}	
extern RtcStruct data Rtc;            
 
void TimerCallBack(void)
{
P04=P04^1;
	ENABLE_UART0_PRINTF;
	printf("hour = %bd:%bd:%bd\n\r",Rtc.Hour, Rtc.Minute, Rtc.Second);
	DISABLE_UART0_PRINTF;
TimerStart(TimerSystick, 100, TimerCallBack);	
}
bit PRINTFG = 0;
void Serial_ISR(void) interrupt 4
{
    _push_(SFRS);
  
    if (RI)
    {
			  PostMessage(MessageUsart,SBUF);
        //PostMessage(MessageKey,SBUF);
        clr_SCON_RI;                                         // Clear RI (Receive Interrupt).
    }
		#if 1
    if (TI)
    {
        if (!PRINTFG)
        
            TI = 0;
        
    }
		#endif
    _pop_(SFRS);
}	

void UART_Open(unsigned long u32SysClock, unsigned char u8UARTPort,unsigned long u32Baudrate)
{
  switch(u8UARTPort)
  {
    case UART0_Timer1:
          SCON = 0x50;       //UART0 Mode1,REN=1,TI=1
          TMOD |= 0x20;      //Timer1 Mode1
          set_PCON_SMOD;          //UART0 Double Rate Enable
          set_CKCON_T1M;
          clr_T3CON_BRCK;          //Serial port 0 baud rate clock source = Timer1
          TH1 = 256 - (u32SysClock/16/u32Baudrate);
          set_TCON_TR1;
      break;
      
      case UART0_Timer3:
          SCON = 0x50;     //UART0 Mode1,REN=1,TI=1
          set_PCON_SMOD;        //UART0 Double Rate Enable
          T3CON &= 0xF8;   //T3PS2=0,T3PS1=0,T3PS0=0(Prescale=1)
          set_T3CON_BRCK;        //UART0 baud rate clock source = Timer3
          RH3    = HIBYTE(65536 - (u32SysClock/16/u32Baudrate));  
          RL3    = LOBYTE(65536 - (u32SysClock/16/u32Baudrate));  
          set_T3CON_TR3;         //Trigger Timer3
      break;
      
      case UART1_Timer3:
          SCON_1 = 0x50;     //UART1 Mode1,REN_1=1,TI_1=1
          T3CON = 0x80;     //T3PS2=0,T3PS1=0,T3PS0=0(Prescale=1), UART1 in MODE 1
          RH3    = HIBYTE(65536 - (u32SysClock/16/u32Baudrate));  
          RL3    = LOBYTE(65536 - (u32SysClock/16/u32Baudrate));     
          set_T3CON_TR3;             //Trigger Timer3                                                             
      break; 
  }
}

/************************************************************************************************************
*    Main function 
************************************************************************************************************/
void main (void)
{
	    ushort  message;
    byte  type, value;
	  MODIFY_HIRC(HIRC_24);
    ALL_GPIO_QUASI_MODE;
  
	
	//TIMER 2 initial for systick 10ms@24mhz
    TIMER2_DIV_512;
    TIMER2_Auto_Reload_Delay_Mode;
  
    RCMP2H = 0XFE;
    RCMP2L = 0x2B;

    TH2 = 0XFE;
    TL2 =0x2B;

    set_EIE_ET2;                                    // Enable Timer2 interrupt
    set_IE_EA;
    set_T2CON_TR2;                                    // Timer2 run
    P06_QUASI_MODE;
	  UART_Open(24000000,UART0_Timer3,115200);
		ENABLE_UART0_INTERRUPT; 
		//ENABLE_UART0_PRINTF; 
		InitMmi();
	  InitMessageQueue();
    TimerCallBack();
		InitRtc();
    while(1)
    {
        message = PendMessageQueue();
        type = GetMessageType(message);
        value = GetMessageData(message);
        switch(type)						
        {
            case MessageKey:           
                EnterFunction(value);
								//KeyProcess(value);						
                break;
            case MessageUsart:          
                UsartProcess(value);
                break;
            default:              
									Function(message);  							

                break;
        }
    }

}
