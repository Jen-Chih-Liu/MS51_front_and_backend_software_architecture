#include "system.h"

RtcStruct data Rtc;            

void RtcSystickRoutine(void) 
{
    static byte data Counter = 0;
    
    if (++Counter == 100)
    {
        Counter = 0;
        //printf("t\n\r");
        if (Rtc.Second < 59)        
            Rtc.Second++;
        else
        {
            Rtc.Second = 0;
            if(Rtc.Minute < 59)    
                Rtc.Minute++;
            else
            {
                Rtc.Minute = 0;
                if(Rtc.Hour < 23)   
                    Rtc.Hour++;
                else
                {
                    Rtc.Hour = 0;
                    Rtc.Day++;
                } 
            }
        }
    }	
}

void InitRtc(void) 
{
    Rtc.Second = 0;
    Rtc.Minute = 0;
    Rtc.Hour = 0;
    Rtc.Day = 0;
}

