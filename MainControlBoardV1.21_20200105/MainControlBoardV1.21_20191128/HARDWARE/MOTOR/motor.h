#ifndef __MOTOR_H
#define __MOTOR_H
#include <sys.h>	 


//ABCD方向与实物电机贴纸有关,与原理图标号无关
#define PWMA	TIM8->CCR1  //PC6
#define PWMB	TIM8->CCR2	//PC7
#define PWMD	TIM8->CCR3  //PC8
#define PWMC	TIM8->CCR4	//PC9

/*
   A  |车头|  D
      |    |
      |    |
      |    |
   B  |车尾|  C
*/
#define AIN2	PBout(14)
#define AIN1	PBout(15)

#define BIN2	PBout(12)
#define BIN1	PBout(13)

#define CIN2	PCout(2)
#define CIN1	PCout(3)

#define DIN2	PCout(0)
#define DIN1	PCout(1)

///////////////////////////////////////////////////////////////////
#define MotorAForword();		AIN1 = 0;AIN2 = 1;//Left车头
#define MotorABackword();		AIN1 = 1;AIN2 = 0;		
#define MotorAStop();			AIN1 = 0;AIN2 = 0;

#define MotorBForword();		BIN1 = 0;BIN2 = 1;//Left车尾
#define MotorBBackword();		BIN1 = 1;BIN2 = 0;
#define MotorBStop();			BIN1 = 0;BIN2 = 0;

#define MotorCForword();		CIN1 = 1;CIN2 = 0;//Right车尾
#define MotorCBackword();		CIN1 = 0;CIN2 = 1;		
#define MotorCStop();			CIN1 = 0;CIN2 = 0;

#define MotorDForword();		DIN1 = 1;DIN2 = 0;//Right车头
#define MotorDBackword();		DIN1 = 0;DIN2 = 1;
#define MotorDStop();			DIN1 = 0;DIN2 = 0;


#define Car_DIR_Forword()	MotorAForword();MotorBForword();MotorCForword();MotorDForword()//车头方向向前

#define Car_DIR_Backword()	MotorABackword();MotorBBackword();MotorCBackword();MotorDBackword()//车尾方向向前

#define Car_DIR_TurnLeft() 	MotorABackword();MotorBBackword();MotorCForword();MotorDForword()//车头左旋转

#define Car_DIR_TurnRight()	MotorAForword();MotorBForword();MotorCBackword();MotorDBackword()//车头右旋转

#define Car_DIR_Stop()		MotorAStop();MotorBStop();MotorCStop();MotorDStop()//停车

#define Car_DIR_Lift_Forword()	MotorABackword();MotorBForword();MotorCBackword();MotorDForword()//车头前进方向左侧平移

#define Car_DIR_Right_Forword()	MotorAForword();MotorBBackword();MotorCForword();MotorDBackword()//车头前进方向右侧平移

#define Car_DIR_Forword_135()	MotorAStop();MotorBForword();MotorCStop();MotorDForword()//车头前进方向135°移动

#define Car_DIR_Forword_315()	MotorAStop();MotorBBackword();MotorCStop();MotorDBackword()//车头前进方向315°移动

#define Car_DIR_Forword_225()	MotorABackword();MotorBStop();MotorCBackword();MotorDStop()//车头前进方向225°移动

#define Car_DIR_Forword_45()	MotorAForword();MotorBStop();MotorCForword();MotorDStop()//车头前进方向45°移动

void Motor_PWM_Init(u16 arr,u16 psc);

#endif
