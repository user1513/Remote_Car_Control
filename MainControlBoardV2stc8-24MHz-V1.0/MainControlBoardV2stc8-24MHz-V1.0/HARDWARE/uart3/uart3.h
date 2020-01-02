#ifndef _UART3_H
#define _UART3_H

#include "appconf.h"

void Uart3Init(void);
void Uart3Send(char dat);
void Uart3SendStr(char *p);
void Uart3SendStrLen(uint8_t *p,uint8_t length);














#endif