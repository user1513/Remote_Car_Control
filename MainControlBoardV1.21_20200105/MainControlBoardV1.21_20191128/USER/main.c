#include "delay.h"
#include "led.h"
#include "usart.h"
#include "motor.h"
#include "encoder.h"
#include "timer.h"
#include "uart4.h"
#include "app_main.h"
#include "dma.h"
#include "ModbusCRC16.h"
#include "ano_tc.h"

long int Target_A,Target_B,Target_C,Target_D,Target;     //���Ŀ��ֵ

typedef enum
{
	Car_STOP = 0,
	Car_Angle_0,
	Car_Angle_45,
	Car_Angle_90,
	Car_Angle_135,
	Car_Angle_180,
	Car_Angle_225,
	Car_Angle_270,
	Car_Angle_315,
	Car_AngleL_360,
	Car_AngleR_360
}eCarMode;

uint8_t ucReceiveGlobal[5];
void vCar_Ation_Mode(uint8_t uiAtion_Mode);
void vCar_Set_PID(uint8_t uiAtion_Mode, uint16_t _Target);
int main(void)
{
//	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); //����AFIOʱ��
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);// �ı�ָ���ܽŵ�ӳ�� 
	delay_init();  	    //��ʼ����ʱ����

//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA, ENABLE);						//ʹ��PB�˿�ʱ��
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;									//LED�˿�����
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;							//�������
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;							//IO���ٶ�Ϊ50MHz
//	GPIO_Init(GPIOA, &GPIO_InitStructure);										//�����趨������ʼ��GPIOB
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;									//LED�˿�����
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;							//�������
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;							//IO���ٶ�Ϊ50MHz
//	GPIO_Init(GPIOB, &GPIO_InitStructure);		
//	GPIO_SetBits(GPIOB,GPIO_Pin_3);	
//	GPIO_SetBits(GPIOA,GPIO_Pin_15);	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	
	LED_Init();
	

	Encoder_Init_TIM2();            //��ʼ���������ӿ�
	Encoder_Init_TIM3();            //��ʼ���������ӿ�
	Encoder_Init_TIM4();            //��ʼ���������ӿ�
	Encoder_Init_TIM5();            //��ʼ���������ӿ�
	
	Motor_PWM_Init(7199,0);   		//=====��ʼ��PWM 10KHZ�������������
	Car_DIR_Stop();
	uart4_init(100000);
	uart_init(115200);
	Uart_ANO_TC__Init();
	Uart_Dma_Init();
	TIM6_Init(100,7199);              //=====��ʱ���ж�
		

	
	while(1)
	{
		if((DMA_UART_STRU.flag & 0x01) == 0x01)	//�ж�DMA���ڽ��ձ�־λ�Ƿ����
		{
			DMA_UART_STRU.flag &= ~0x01; 		//���DMA���ڽ��ձ�־λ
			DMA_UART_RECEIVE_Cmd(DISABLE);		//�ر�DMA���ڽ��չ���
			if(DMA_UART_STRU.uiReceivePack_FH == ((*(DMA_UART_STRU.ucReceivePack)<<8) + *(DMA_UART_STRU.ucReceivePack + 1)) \
				&& DMA_UART_STRU.uiReceivePack_FT == *(DMA_UART_STRU.ucReceivePack + DMA_UART_STRU.ucReceivePack_Length - 1))//������ݰ�֡ͷ,֡β�Ƿ���ȷ
			{
				DMA_UART_STRU.uiCheckReceivePack = \
				(*(DMA_UART_STRU.ucReceivePack + DMA_UART_STRU.ucReceivePack_Length - 2) << 8) \
				+ (*(DMA_UART_STRU.ucReceivePack + DMA_UART_STRU.ucReceivePack_Length - 3));
				if(ModBus_CRC(DMA_UART_STRU.ucReceivePack, 7) == DMA_UART_STRU.uiCheckReceivePack)		//�ж����ݰ��Ǽ���λ�Ƿ���ȷ
				{
					DMA_UART_STRU.flag |= 0x80; 		//����������ݰ��ɹ�
					memcpy(ucReceiveGlobal, DMA_UART_STRU.ucReceivePack + 2, 5);
				}
			}
			if(USART_GetFlagStatus(UART4, USART_FLAG_RXNE) == RESET)
			{
				RestartSetUartReceiveCount(0);	//���¿�ʼ���մ���ָ�����
				DMA_UART_STRU.ucReceivePack = puCcurrent_Receive_Point;
			}
			else
			{
				RestartSetUartReceiveCount(1);	//���¿�ʼ���մ���ָ�����
				DMA_UART_STRU.ucReceivePack = puCcurrent_Receive_Point + 1;
			}

			DMA_UART_RECEIVE_Cmd(ENABLE);	//��DMA���ڽ��չ���
		}
		if(DMA_UART_STRU.flag & 0x80)
		{
			uint16_t pwm_temp = 0;
			DMA_UART_STRU.flag &= ~0x80;
			pwm_temp = ((ucReceiveGlobal[2] & 0x03) << 8) + ucReceiveGlobal[3];
			//pwm_temp = pwm_temp;
			//vCar_Ation_Mode(ucReceiveGlobal[2] >> 2);
			Target = pwm_temp * 3;
			vCar_Set_PID(ucReceiveGlobal[2] >> 2 ,Target );
			
//			 PWMA = pwm_temp * 10;
//			 PWMB = pwm_temp * 10;	
//			 PWMD =	pwm_temp * 10;
//			 PWMC =	pwm_temp * 10;
		}
	}
}

void vCar_Set_PID(uint8_t uiAtion_Mode, uint16_t _Target)
{
	switch(uiAtion_Mode)
	{
		case Car_STOP: 				Target_A = 0; Target_B = 0; Target_C = 0 ;Target_D = 0;break;
		case Car_Angle_0:  		Target_A = _Target; Target_B = - _Target; Target_C = _Target; Target_D = - _Target; break;
		case Car_Angle_45:  	Target_A = _Target; Target_B = 0; Target_C = _Target; Target_D = 0; break;
		case Car_Angle_90:  	Target_A = _Target; Target_B = _Target; Target_C = _Target; Target_D = _Target; break;
		case Car_Angle_135:  	Target_A = 0; Target_B = -_Target; Target_C = 0; Target_D = - _Target; break;
		case Car_Angle_180:  	Target_A = - _Target; Target_B = _Target; Target_C = - _Target; Target_D = _Target; break;
		case Car_Angle_225: 	Target_A = - _Target; Target_B = 0; Target_C = -_Target; Target_D = 0; break;
		case Car_Angle_270:  	Target_A = - _Target; Target_B = - _Target; Target_C = - _Target; Target_D = - _Target; break;
		case Car_Angle_315:  	Target_A = 0; Target_B = - _Target; Target_C = 0; Target_D = -_Target; break;
		case Car_AngleL_360:  	Target_A = - _Target; Target_B = - _Target; Target_C = _Target; Target_D = _Target; break;
		case Car_AngleR_360:  	Target_A = _Target; Target_B = _Target; Target_C = - _Target; Target_D = - _Target; break;
		default:Car_DIR_Stop();break;
	}
}

void vCar_Ation_Mode(uint8_t uiAtion_Mode)
{
	switch(uiAtion_Mode)
	{
		case Car_STOP: Car_DIR_Stop();break;
		case Car_Angle_0: Car_DIR_Right_Forword(); break;
		case Car_Angle_45: Car_DIR_Forword_45(); break;
		case Car_Angle_90: Car_DIR_Forword(); break;
		case Car_Angle_135: Car_DIR_Forword_135(); break;
		case Car_Angle_180: Car_DIR_Lift_Forword(); break;
		case Car_Angle_225: Car_DIR_Forword_225(); break;
		case Car_Angle_270: Car_DIR_Backword(); break;
		case Car_Angle_315: Car_DIR_Forword_315(); break;
		case Car_AngleL_360: Car_DIR_TurnLeft(); break;
		case Car_AngleR_360: Car_DIR_TurnRight(); break;
		default:Car_DIR_Stop();break;
	}
}


