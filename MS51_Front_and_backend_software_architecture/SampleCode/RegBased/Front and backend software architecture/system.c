#include "system.h"
#include "MS51_16K.H"


#define MessageBufferSum 64                             

struct MessageQueue                                     
{                                                       
    ushort  * Start;                                    
    ushort  * End;                                      
    ushort  * In;                                       
    ushort  * Out;                                      
    byte      Size;                                     
    byte      Entries;                                  
    ushort    Buffer[MessageBufferSum];                 
} ;

static struct MessageQueue idata MessageQueue;



static bool data EaSave;
static byte data CriticalNesting = 0;
byte code HextoAscii[16] = 
{
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
};

void Delay(ushort delayClock)
{
	while(delayClock--);
}

void DelayUs(ushort delayTime)
{
    while(delayTime--);
}

void DelayMs(ushort delayTime)
{
	while(delayTime--)
	{
		DelayUs(1000);
	}
}

byte HexToAscii(byte hex)
{
	Assert(hex < 16);                   
	return HextoAscii[hex];
}


void EnterCritical(void)
{
    if (CriticalNesting == 0)   
        EA = false;
    
    CriticalNesting++;    
}


void ExitCritical(void)
{
    if (CriticalNesting > 0)
    {
        CriticalNesting--;
        if (CriticalNesting == 0)
            EA = true;
    }
}

void InitMessageQueue(void)
{
    MessageQueue.Start = MessageQueue.Buffer;
    MessageQueue.End = MessageQueue.Buffer + MessageBufferSum - 1;
    MessageQueue.In = MessageQueue.Start;
    MessageQueue.Out = MessageQueue.Start;
    MessageQueue.Size = MessageBufferSum;
    MessageQueue.Entries = 0;
}


void PostMessage(MessageEnum message, ushort value)
{
    EnterCritical();         					
    Assert(MessageQueue.Entries <= MessageQueue.Size);

    if(message == MessageTimer)					        
        *MessageQueue.In = value;      					
    else                               					
    {
        UshortToByte1(*MessageQueue.In) = message;	
        UshortToByte0(*MessageQueue.In) = value & 0xFF;	
    }
    
	MessageQueue.In++;                                 
    
    if(MessageQueue.In > MessageQueue.End)        		
        MessageQueue.In = MessageQueue.Start;
    
    MessageQueue.Entries++;                        	
    
	ExitCritical();                                  	
}


ushort PendMessageQueue(void)
{    
    ushort message;
    while(MessageQueue.Entries == 0)    		    
    { 
			set_PCON_IDLE;//for system in idle state
			//set_PCON_PD;
		};										
    
    message = *MessageQueue.Out++;				   
    MessageQueue.Entries--;						  
    
    if (MessageQueue.Out > MessageQueue.End) 	    
        MessageQueue.Out = MessageQueue.Start;
    
    return(message);							    
}



