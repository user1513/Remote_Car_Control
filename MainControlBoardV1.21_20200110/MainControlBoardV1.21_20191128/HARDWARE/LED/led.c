#include "led.h"


void LED_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);						//ʹ��PB�˿�ʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;									//LED�˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;							//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;							//IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);										//�����趨������ʼ��GPIOB
	GPIO_SetBits(GPIOB,GPIO_Pin_9);												//PB9�����
}



