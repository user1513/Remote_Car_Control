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
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);//ʹ��PORTB��ʱ�ӡ���������PB3����
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//�ر�JTAG��ʹ��SWD��������SWDģʽ����,��Լ��Դ
		
	delay_init();  	    //��ʼ����ʱ����
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	
	LED_Init();
	uart_init(115200);

	Encoder_Init_TIM2();            //��ʼ���������ӿ�
	Encoder_Init_TIM3();            //��ʼ���������ӿ�
	Encoder_Init_TIM4();            //��ʼ���������ӿ�
	Encoder_Init_TIM5();            //��ʼ���������ӿ�
	
	Motor_PWM_Init(7199,0);   		//=====��ʼ��PWM 10KHZ�������������
	

	TIM6_Init(50,7199);              //=====��ʱ���ж�
		
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
