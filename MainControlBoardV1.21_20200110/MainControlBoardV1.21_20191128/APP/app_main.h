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


extern long int Motor_A,Motor_B,Motor_C,Motor_D;        //���PWM����
extern int Encoder_A,Encoder_B,Encoder_C,Encoder_D;          //���������������
extern long int Target_A,Target_B,Target_C,Target_D,Target;     //���Ŀ��ֵ
extern long int Position_A,Position_B,Position_C,Position_D,Rate_A,Rate_B,Rate_C,Rate_D; //PID������ر���

extern float VelocityA_KP, VelocityA_KI;	          		//�ٶȿ���PID����
extern float VelocityB_KP, VelocityB_KI;	          		//�ٶȿ���PID����
extern float VelocityC_KP, VelocityC_KI;	          		//�ٶȿ���PID����
extern float VelocityD_KP, VelocityD_KI;	          		//�ٶȿ���PID����
extern float Position_KP,Position_KI,Position_KD;  //λ�ÿ���PID����




extern u8 RemoteControlUsartData[9];      //��ȡ��ң����������



void vSetPwm(uint32_t kp, uint32_t ki);
void app_main(void);

#endif