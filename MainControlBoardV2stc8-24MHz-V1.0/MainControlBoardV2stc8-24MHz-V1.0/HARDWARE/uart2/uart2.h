#ifndef __UART2_H
#define __UART2_H

#include "appconf.h"



#if configUSE_UART2_MODE


void Uart2Init(void);
void Uart2Send(uint8_t dat);
void Uart2SendStr(uint8_t *p);
void Uart2SendStrLen(uint8_t *p,uint8_t length);

#endif

#endif
