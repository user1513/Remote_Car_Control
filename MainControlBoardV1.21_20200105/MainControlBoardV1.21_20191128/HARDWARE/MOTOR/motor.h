#ifndef __MOTOR_H
#define __MOTOR_H
#include <sys.h>	 


//ABCD������ʵ������ֽ�й�,��ԭ��ͼ����޹�
#define PWMA	TIM8->CCR1  //PC6
#define PWMB	TIM8->CCR2	//PC7
#define PWMD	TIM8->CCR3  //PC8
#define PWMC	TIM8->CCR4	//PC9

/*
   A  |��ͷ|  D
      |    |
      |    |
      |    |
   B  |��β|  C
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
#define MotorAForword();		AIN1 = 0;AIN2 = 1;//Left��ͷ
#define MotorABackword();		AIN1 = 1;AIN2 = 0;		
#define MotorAStop();			AIN1 = 0;AIN2 = 0;

#define MotorBForword();		BIN1 = 0;BIN2 = 1;//Left��β
#define MotorBBackword();		BIN1 = 1;BIN2 = 0;
#define MotorBStop();			BIN1 = 0;BIN2 = 0;

#define MotorCForword();		CIN1 = 1;CIN2 = 0;//Right��β
#define MotorCBackword();		CIN1 = 0;CIN2 = 1;		
#define MotorCStop();			CIN1 = 0;CIN2 = 0;

#define MotorDForword();		DIN1 = 1;DIN2 = 0;//Right��ͷ
#define MotorDBackword();		DIN1 = 0;DIN2 = 1;
#define MotorDStop();			DIN1 = 0;DIN2 = 0;


#define Car_DIR_Forword()	MotorAForword();MotorBForword();MotorCForword();MotorDForword()//��ͷ������ǰ

#define Car_DIR_Backword()	MotorABackword();MotorBBackword();MotorCBackword();MotorDBackword()//��β������ǰ

#define Car_DIR_TurnLeft() 	MotorABackword();MotorBBackword();MotorCForword();MotorDForword()//��ͷ����ת

#define Car_DIR_TurnRight()	MotorAForword();MotorBForword();MotorCBackword();MotorDBackword()//��ͷ����ת

#define Car_DIR_Stop()		MotorAStop();MotorBStop();MotorCStop();MotorDStop()//ͣ��

#define Car_DIR_Lift_Forword()	MotorABackword();MotorBForword();MotorCBackword();MotorDForword()//��ͷǰ���������ƽ��

#define Car_DIR_Right_Forword()	MotorAForword();MotorBBackword();MotorCForword();MotorDBackword()//��ͷǰ�������Ҳ�ƽ��

#define Car_DIR_Forword_135()	MotorAStop();MotorBForword();MotorCStop();MotorDForword()//��ͷǰ������135���ƶ�

#define Car_DIR_Forword_315()	MotorAStop();MotorBBackword();MotorCStop();MotorDBackword()//��ͷǰ������315���ƶ�

#define Car_DIR_Forword_225()	MotorABackword();MotorBStop();MotorCBackword();MotorDStop()//��ͷǰ������225���ƶ�

#define Car_DIR_Forword_45()	MotorAForword();MotorBStop();MotorCForword();MotorDStop()//��ͷǰ������45���ƶ�

void Motor_PWM_Init(u16 arr,u16 psc);

#endif
