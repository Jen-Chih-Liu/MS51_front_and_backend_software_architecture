#ifndef __APP_H
#define __APP_H

typedef void (*MmiFunction)(KeyEnum key);

extern MmiFunction EnterFunction;

extern void InitMmi(void);

extern void UsartProcess(byte value);

extern void KeyProcess(KeyEnum key);

#endif


