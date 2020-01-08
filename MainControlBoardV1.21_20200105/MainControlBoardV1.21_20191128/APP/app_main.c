#include "app_main.h"
#include "led.h"
#include "delay.h"
#include "control.h"

long int Motor_A,Motor_B,Motor_C,Motor_D;        //���PWM����

int Encoder_A,Encoder_B,Encoder_C,Encoder_D;          //���������������



long int Position_A,Position_B,Position_C,Position_D,Rate_A,Rate_B,Rate_C,Rate_D; //PID������ر���

float Velocity_KP=0.5,Velocity_KI=0.5;	          		//�ٶȿ���PID����
float Position_KP=80,Position_KI=0,Position_KD=20;	//λ�ÿ���PID����



u8 RemoteControlUsartData[9];      //��ȡ��ң����������

void app_main(void)
{
	u32 t;
	while(1)
	{
		delay_ms(10);
		
		t++;
		if(t % 20 == 0)
		{
			LED_WORK = ~LED_WORK;
		}
		
		if(RemoteControlUsartData[8]==0XFF)
		{
			RemoteControlUsartData[8]=0X00;
//			if(RemoteControlUsartData[2]==0x01)//�ж��ǲ���cmd ��0x01��
//				MotorGoAngle_Func(RemoteControlUsartData[4]);//ִ���˶�����
		}
	}
}

