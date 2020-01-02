#include "delay.h"
#include "led.h"
#include "usart.h"
#include "motor.h"
#include "encoder.h"
#include "timer.h"
#include "usart4.h"

#include "app_main.h"

int a;
int b;
int c;
int d;
int cv = 2;
int main(void)
{
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);//使能PORTB口时钟、复用引脚PB3引脚
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//关闭JTAG，使能SWD，可以用SWD模式调试,节约资源
		
	delay_init();  	    //初始化延时函数
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	
	LED_Init();
	uart_init(115200);

	Encoder_Init_TIM2();            //初始化编码器接口
	Encoder_Init_TIM3();            //初始化编码器接口
	Encoder_Init_TIM4();            //初始化编码器接口
	Encoder_Init_TIM5();            //初始化编码器接口
	
	Motor_PWM_Init(7199,0);   		//=====初始化PWM 10KHZ，用于驱动电机
	

	TIM6_Init(50,7199);              //=====定时器中断
		
	Usart4_Init(100000);
	
	Car_DIR_Front();
	
//	PWMA = 2000;
//	PWMB = 2000;
//	PWMC = 2000;
//	PWMD = 2000;
//	
//	while(1)
//	{
//		cv ++;
//		
//		a = Read_Encoder(2); 
//		b = Read_Encoder(3); 
//		c = Read_Encoder(4); 
//		d = Read_Encoder(5); 
//		
//		LED_WORK = ~LED_WORK;
//		delay_ms(500);		
//	}
//	
	app_main();


	while(1)
	{
		LED_WORK = ~LED_WORK;
		delay_ms(500);
		;
	}
}
