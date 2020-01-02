#include "motor.h"


void Motor_PWM_IO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);							//ʹ��PC�˿�ʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;		//MOTOR_PWM�˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;									//�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;								//IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);											//�����趨������ʼ��GPIOC
	GPIO_ResetBits(GPIOC,GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9);				//PC6-9�����
}

void Motor_IO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);							//ʹ��PB�˿�ʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;	//MOTOR_INA_B�˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;								//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;								//IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);											//�����趨������ʼ��GPIOB
	GPIO_ResetBits(GPIOB,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);			//PB12-15�����

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);							//ʹ��PC�˿�ʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;		//MOTOR_INC_D�˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;								//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;								//IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);											//�����趨������ʼ��GPIOB
	GPIO_ResetBits(GPIOC,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);				//PC0-3�����
	
	Motor_PWM_IO_Init();
}


void Motor_PWM_Init(u16 arr,u16 psc)
{
	Motor_IO_Init();

	RCC->APB2ENR|=1<<13;       //ʹ��TIM8ʱ��
	
	TIM8->ARR=arr;             //�趨�������Զ���װֵ 
	TIM8->PSC=psc;             //Ԥ��Ƶ������Ƶ
	TIM8->CCMR1|=6<<4;         //CH1 PWM1ģʽ	
	TIM8->CCMR1|=6<<12;        //CH2 PWM1ģʽ	
	TIM8->CCMR2|=6<<4;         //CH3 PWM1ģʽ	
	TIM8->CCMR2|=6<<12;        //CH4 PWM1ģʽ	
	
	TIM8->CCMR1|=1<<3;         //CH1Ԥװ��ʹ��	  
	TIM8->CCMR1|=1<<11;        //CH2Ԥװ��ʹ��	 
	TIM8->CCMR2|=1<<3;         //CH3Ԥװ��ʹ��	  
	TIM8->CCMR2|=1<<11;        //CH4Ԥװ��ʹ��	  
	
	TIM8->CCER|=1<<0;			//CH1���ʹ��	
	TIM8->CCER|=1<<4;			//CH2���ʹ��	   
	TIM8->CCER|=1<<8;			//CH3���ʹ��	 
	TIM8->CCER|=1<<12;			//CH4���ʹ��
	TIM8->BDTR |= 1<<15;		//TIM����Ҫ��仰�������PWM
	TIM8->CR1=0x8000;			//ARPEʹ�� 
	TIM8->CR1|=0x01;			//ʹ�ܶ�ʱ��


	PWMA = 0;
	PWMB = 0;
	PWMC = 0;
	PWMD = 0;
} 
