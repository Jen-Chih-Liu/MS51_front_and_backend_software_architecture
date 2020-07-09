#include "system.h"


typedef struct 
{
    ushort  Times;
    function Function;
}TimerStruct;

#define TimerSum 0x4                            
static byte idata State = 0;                    
static TimerModeEnum idata Mode;          
static TimerStruct idata TimerBlock[TimerSum]; 


void TimerSystickRoutine(void)
{
    byte i = 0, stateBackup;
    if (State == 0x00) 
			return;      					
    stateBackup = State;              					
    while (stateBackup)	
    {
        if ((stateBackup & 0x01) == 1) 			
        {
            if ((--TimerBlock[i].Times) == 0) 			
            {
                if (GetBit(Mode, i))     				                   
                    PostMessage(MessageTimer, (ushort)TimerBlock[i].Function);
                else 
                    (TimerBlock[i].Function)(); 	       
                    
                ResetBit(State, i);     			  	                 
            }
        }
        stateBackup = stateBackup >> 1;
        i++;
    }
}



byte TimerStart(TimerModeEnum mode, ushort times, function registerFunction)
{
    byte i;

    EnterCritical();
    for(i = 0; i < TimerSum; i++) 
    {
        if(!GetBit(State, i)) 
        {			
            TimerBlock[i].Times = times;                               
            TimerBlock[i].Function = registerFunction;          
            if(mode)                                              
                SetBit(Mode, i);
            else 
                ResetBit(Mode, i);
			
            SetBit(State, i);                                         
            ExitCritical();
            return(i);
        }
    }
    ExitCritical();
    return(invalid);
}


void TimerStop(byte id) 
{
    if (id >= TimerSum) return;     
        
    EnterCritical();
	
    ResetBit(State, id);
	
    ExitCritical();
}


