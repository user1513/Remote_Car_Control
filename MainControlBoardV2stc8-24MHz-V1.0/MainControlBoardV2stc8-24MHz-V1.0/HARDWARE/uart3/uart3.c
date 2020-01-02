#include "uart3.h"

#if configUSE_UART3_MODE
#define FOSC            24000000UL
#define BRT3             (65536 - FOSC / 100000 / 4)

void UART3_Isr() interrupt 17
{
    if (S3CON & 0x01)
    {
        S3CON &= ~0x01;                         //���жϱ�־
    }
}

void Uart3Init(void)		//9600bps@24.000MHz
{

	
	S3CON = 0x10;		//8λ����,�ɱ䲨����
	S3CON |= 0x40;		//����3ѡ��ʱ��3Ϊ�����ʷ�����
	T4T3M |= 0x02;		//��ʱ��3ʱ��ΪFosc,��1T
	T3L = BRT3;
    T3H = BRT3 >> 8;
	T4T3M |= 0x08;		//������ʱ��3
    IE2 |= ES3;                                  //ʹ�ܴ����ж�
 //   EA = 1;
}

void Uart3Send(char dat)
{
	S3BUF = dat;
    while ((S3CON & 0x02)!=0x02);
    S3CON &= ~0x02; 
}

void Uart3SendStr(char *p)
{
    while (*p!='\0')
    {
        Uart3Send(*p++);
    }
}

void Uart3SendStrLen(uint8_t *p,uint8_t length)
{
    while (length--)
    {
        Uart3Send(*p++);
    }
}
#endif
