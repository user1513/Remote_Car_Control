#ifndef __UART1_H
#define __UART1_H

#include "appconf.h"

#if configUSE_UART1_MODE

void Uart1Init();
void Uart1Send(uint8_t dat);
void Uart1SendStr(uint8_t *p);
void Uart1SendStrLen(uint8_t *p,uint8_t length);
#endif

#endif
