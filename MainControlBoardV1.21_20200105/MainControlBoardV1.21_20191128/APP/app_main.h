#ifndef __APP_MAIN_H
#define __APP_MAIN_H

#include "stm32f10x.h"

enum
{
	Angle_0,
	Angle_45,
	Angle_90,
	Angle_135,
	Angle_180,
	Angle_225,
	Angle_270,
	Angle_315,
	AngleL_360,
	AngleR_360
};


extern long int Motor_A,Motor_B,Motor_C,Motor_D;        //电机PWM变量
extern int Encoder_A,Encoder_B,Encoder_C,Encoder_D;          //编码器的脉冲计数
extern long int Target_A,Target_B,Target_C,Target_D,Target;     //电机目标值
extern long int Position_A,Position_B,Position_C,Position_D,Rate_A,Rate_B,Rate_C,Rate_D; //PID控制相关变量

extern float Velocity_KP,Velocity_KI;	          //速度控制PID参数
extern float Position_KP,Position_KI,Position_KD;  //位置控制PID参数




extern u8 RemoteControlUsartData[9];      //获取到遥控器的数据




void app_main(void);

#endif
