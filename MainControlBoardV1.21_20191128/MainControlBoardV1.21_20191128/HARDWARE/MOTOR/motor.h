#ifndef __MOTOR_H
#define __MOTOR_H
#include <sys.h>	 

#define PWMA	TIM8->CCR1  //PC6
#define PWMB	TIM8->CCR2	//PC7
#define PWMC	TIM8->CCR3  //PC8
#define PWMD	TIM8->CCR4	//PC9

#define AIN2	PBout(12)
#define AIN1	PBout(13)
#define BIN2	PBout(14)
#define BIN1	PBout(15)
#define CIN2	PCout(0)
#define CIN1	PCout(1)
#define DIN2	PCout(2)
#define DIN1	PCout(3)

#define MotorAFront();		AIN1 = 1;AIN2 = 0;//Left
#define MotorAAfter();		AIN1 = 0;AIN2 = 1;		
#define MotorAStop();		AIN1 = 0;AIN2 = 0;

#define MotorBFront();		BIN1 = 1;BIN2 = 0;//Right
#define MotorBAfter();		BIN1 = 0;BIN2 = 1;
#define MotorBStop();		BIN1 = 0;BIN2 = 0;

#define MotorCFront();		CIN1 = 1;CIN2 = 0;//Left
#define MotorCAfter();		CIN1 = 0;CIN2 = 1;		
#define MotorCStop();		CIN1 = 0;CIN2 = 0;

#define MotorDFront();		DIN1 = 1;DIN2 = 0;//Right
#define MotorDAfter();		DIN1 = 0;DIN2 = 1;
#define MotorDStop();		DIN1 = 0;DIN2 = 0;

//反转
#define Car_DIR_Front();	MotorAAfter();MotorBAfter();MotorCFront();MotorDFront();
//正转
#define Car_DIR_Back();		MotorAFront();MotorBFront();MotorCAfter();MotorDAfter();

#define Car_DIR_TurnLeft()
#define Car_DIR_TurnRight()
#define Car_DIR_Stop();		MotorAStop();MotorBStop();MotorCStop();MotorDStop();


void Motor_PWM_Init(u16 arr,u16 psc);

#endif
