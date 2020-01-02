
#include "uart1.h"

#if configUSE_UART1_MODE

#define FOSC            24000000UL
#define BRT             (65536 - FOSC / 100000 / 4)




void UartIsr() interrupt 4 using 1
{
    if (RI)
    {
        RI = 0;
		DR16DataAnalysis(SBUF);
    }
}

void Uart1Init()
{
    SCON |= 0x50;
    TMOD |= 0x00;
    TL1 = BRT;
    TH1 = BRT >> 8;
    TR1 = 1;
    AUXR |= 0x40;
	ES=1;
	EA=1;
}

void Uart1Send(uint8_t dat)
{
    SBUF = dat;
	while (!TI);
    TI=0;
    
}

void Uart1SendStr(uint8_t *p)
{
    while (*p)
    {
        Uart1Send(*p++);
    }
}

void Uart1SendStrLen(uint8_t *p,uint8_t length)
{
    while (length--)
    {
        Uart1Send(*p++);
    }
}

#endif





