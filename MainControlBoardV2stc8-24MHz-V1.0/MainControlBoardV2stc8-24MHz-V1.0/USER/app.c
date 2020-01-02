#include "appconf.h"
#define MotorMode P17

uint16_t G_dr16_ch0_value = 0;
uint16_t G_dr16_ch1_value = 0;
uint16_t G_dr16_ch2_value = 0;
uint16_t G_dr16_ch3_value = 0;

extern uint8_t flag;


void Delay1000ms()		//@24.000MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 122;
	j = 193;
	k = 128;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


void main(void)
{
	Uart1Init();
	Timer0Init();
	Uart2Init();
		EA=1;
	Delay1000ms();
	Delay1000ms();
	while(1)
	{
		//vGetAngleInfo();
		if(UsartFlag == Enable && flag==Enable)
		{
			vGetAngleInfo();
			flag = Disable;
			UsartFlag = Disable;
			config_RECEIVE_ENBALE_FLAG;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
		}		
	}
}
