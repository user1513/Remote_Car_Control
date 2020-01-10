#include "timer.h"
/**************************************************************************
函数功能：定时器3通道3输入捕获初始化
入口参数：入口参数：arr：自动重装值  psc：时钟预分频数 
返回  值：无
**************************************************************************/
void TIM6_Init(u16 arr,u16 psc)	
{	 
	RCC->APB1ENR|=1<<4;	//TIM6时钟使能    
 	TIM6->ARR=arr;  	//设定计数器自动重装值 
	TIM6->PSC=psc;  	//预分频器设置
	TIM6->DIER|=1<<0;   //允许更新中断				
	TIM6->CR1|=0x01;    //使能定时器3
	MY_NVIC_Init(2,1,TIM6_IRQn,2);//抢占，子优先级，组
}
