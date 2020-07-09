

#include "system.h"
//#include "app.h"
#include "MS51_16K.H"
typedef void (*MmiFunction)(KeyEnum key);

extern MmiFunction EnterFunction;


typedef enum
{
    WorkState = 1,            
    SetupState = 2,           
    ServiceState = 3          
}StateEnum;

static StateEnum data State = WorkState;

static void WorkStateProcess(KeyEnum key)
{
    printf("key = %c\n", key);
    if (key == '2')
    {
        printf("State = 2:\n");
        State = SetupState;
    }
}

static void SetupStateProcess(KeyEnum key)
{
    printf("key = %c\n", key);
    if (key == '3')
    {
        printf("State = 3:\n");
        State = ServiceState;
    }     
}

static void ServiceStateProcess(KeyEnum key)
{
    printf("key = %c\n", key);
    if (key == '1')
    {
        printf("State = 1:\n");
        State = WorkState;
    }  
}

void KeyProcess(KeyEnum key)
{
    switch (State)
    {
        case WorkState:
            WorkStateProcess(key);
            break;
        case SetupState:
            SetupStateProcess(key);
            break;
        case ServiceState:
            ServiceStateProcess(key);
            break;
    }
}

static void WorkPointerProcess(KeyEnum key);
static void SetupPointerProcess(KeyEnum key);
static void ServicePointerProcess(KeyEnum key);

MmiFunction EnterFunction = WorkPointerProcess;    

static void WorkPointerProcess(KeyEnum key)
{
	ENABLE_UART0_PRINTF;
    printf("get: key = %c\n", key);
    if (key == '2')
    {
        printf("State = 2:\n");
        EnterFunction = SetupPointerProcess;
    }
			DISABLE_UART0_PRINTF;
}

static void SetupPointerProcess(KeyEnum key)
{
	ENABLE_UART0_PRINTF;
    printf("key = %c\n", key);
    if (key == '3')
    {
        printf("State = 3:\n");
        EnterFunction = ServicePointerProcess;
    }    
	DISABLE_UART0_PRINTF;		
}

static void ServicePointerProcess(KeyEnum key)
{
	ENABLE_UART0_PRINTF;
    printf("key = %c\n", key);
    if (key == '1')
    {
        printf("State = 1:n");
        EnterFunction = WorkPointerProcess;
    }  
			DISABLE_UART0_PRINTF;
}


void InitMmi(void)
{
	ENABLE_UART0_PRINTF;
    printf("\nMS Start\n");
    printf("\ndate:2015.1.19\n");
    printf("\nHardware Plat:MCU51Series\n");
    printf("\nAuthor: Wangsw\n");
    printf("\n\n");
	
    printf("1:\n");
    printf("2:\n");
    printf("3:\n");
	
    printf("State = 1:\n");
    printf("Please press 1 , 2 or 3  to select menu\n");
	DISABLE_UART0_PRINTF;
}


void UsartProcess(byte value)
{
	 ENABLE_UART0_PRINTF;
    printf("Usart Receive = %x\n\r", (ushort)value);
	
   DISABLE_UART0_PRINTF;
}
