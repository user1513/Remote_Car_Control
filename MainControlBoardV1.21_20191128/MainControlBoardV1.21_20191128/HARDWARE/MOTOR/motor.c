#include "motor.h"


void Motor_PWM_IO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);							//使能PC端口时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;		//MOTOR_PWM端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;									//复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;								//IO口速度为50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);											//根据设定参数初始化GPIOC
	GPIO_ResetBits(GPIOC,GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9);				//PC6-9输出低
}

void Motor_IO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);							//使能PB端口时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;	//MOTOR_INA_B端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;								//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;								//IO口速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);											//根据设定参数初始化GPIOB
	GPIO_ResetBits(GPIOB,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);			//PB12-15输出低

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);							//使能PC端口时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;		//MOTOR_INC_D端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;								//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;								//IO口速度为50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);											//根据设定参数初始化GPIOB
	GPIO_ResetBits(GPIOC,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);				//PC0-3输出低
	
	Motor_PWM_IO_Init();
}


void Motor_PWM_Init(u16 arr,u16 psc)
{
	Motor_IO_Init();

	RCC->APB2ENR|=1<<13;       //使能TIM8时钟
	
	TIM8->ARR=arr;             //设定计数器自动重装值 
	TIM8->PSC=psc;             //预分频器不分频
	TIM8->CCMR1|=6<<4;         //CH1 PWM1模式	
	TIM8->CCMR1|=6<<12;        //CH2 PWM1模式	
	TIM8->CCMR2|=6<<4;         //CH3 PWM1模式	
	TIM8->CCMR2|=6<<12;        //CH4 PWM1模式	
	
	TIM8->CCMR1|=1<<3;         //CH1预装载使能	  
	TIM8->CCMR1|=1<<11;        //CH2预装载使能	 
	TIM8->CCMR2|=1<<3;         //CH3预装载使能	  
	TIM8->CCMR2|=1<<11;        //CH4预装载使能	  
	
	TIM8->CCER|=1<<0;			//CH1输出使能	
	TIM8->CCER|=1<<4;			//CH2输出使能	   
	TIM8->CCER|=1<<8;			//CH3输出使能	 
	TIM8->CCER|=1<<12;			//CH4输出使能
	TIM8->BDTR |= 1<<15;		//TIM必须要这句话才能输出PWM
	TIM8->CR1=0x8000;			//ARPE使能 
	TIM8->CR1|=0x01;			//使能定时器


	PWMA = 0;
	PWMB = 0;
	PWMC = 0;
	PWMD = 0;
} 
