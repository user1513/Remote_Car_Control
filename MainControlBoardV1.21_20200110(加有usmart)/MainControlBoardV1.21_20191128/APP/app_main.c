#include "app_main.h"
#include "led.h"
#include "delay.h"
#include "control.h"

long int Motor_A,Motor_B,Motor_C,Motor_D;        //电机PWM变量

int Encoder_A,Encoder_B,Encoder_C,Encoder_D;          //编码器的脉冲计数



long int Position_A,Position_B,Position_C,Position_D,Rate_A,Rate_B,Rate_C,Rate_D; //PID控制相关变量

float Velocity_KP=1,Velocity_KI=0.5;	          		//速度控制PID参数
float Position_KP=80,Position_KI=0,Position_KD=20;	//位置控制PID参数



u8 RemoteControlUsartData[9];      //获取到遥控器的数据
void vSetPwm(uint32_t kp, uint32_t ki)
{
	Velocity_KP = kp/1000.0;
	Velocity_KI = ki/1000.0;
}

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
//			if(RemoteControlUsartData[2]==0x01)//判断是不是cmd （0x01）
//				MotorGoAngle_Func(RemoteControlUsartData[4]);//执行运动命令
		}
	}
}


