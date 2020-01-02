#include "appconf.h"


uint16_t G_dr16_ch0_value = 0;
uint16_t G_dr16_ch1_value = 0;
uint16_t G_dr16_ch2_value = 0;
uint16_t G_dr16_ch3_value = 0;

extern uint8_t uSysFlag[2];


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
		
	Delay1000ms();
	uSysFlag[1] = GET_WheelMode_Port;
	Delay1000ms();
	EA=1;
	while(1)
	{
		//vGetAngleInfo();
		if(bDelayTimeFlag == Enable && uSysFlag[0]==Enable)
		{
			vGetAngleInfo();
			uSysFlag[0] = Disable;
			bDelayTimeFlag = Disable;
			config_RECEIVE_ENBALE_FLAG;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
		}		
	}
}
