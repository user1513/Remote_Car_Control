#include "uart2.h"

#if configUSE_UART2_MODE
#define FOSC            24000000UL
#define BRT             (65536 - FOSC / 100000 / 4)


void Uart2Isr() interrupt 8 
{
    if (S2CON & 0x01)
    {
        S2CON &= ~0x01;
		
    }
}

void Uart2Init()
{
	S2CON |= 0x50;
    T2L = BRT;
    T2H = BRT >> 8;
    AUXR |= 0x14;

}

void Uart2Send(uint8_t dat)
{
	S2BUF = dat;
    while ((S2CON & 0x02)!=0x02);
    S2CON &= ~0x02; 
}

void Uart2SendStr(uint8_t *p)
{
    while (*p)
    {
        Uart2Send(*p++);
    }
}

void Uart2SendStrLen(uint8_t *p,uint8_t length)
{
    while (length--)
    {
        Uart2Send(*p++);
    }
}

#endif
