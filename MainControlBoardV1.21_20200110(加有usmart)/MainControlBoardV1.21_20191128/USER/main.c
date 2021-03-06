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
#include "usmart.h"
long int Target_A,Target_B,Target_C,Target_D,Target;     //电机目标值

uint8_t uart_data_array[40] = {0xAA,0X05,0XAF,0xF1,32};

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
void vBsp_Init(void);
void vUartReceiveIsOk(void);
void vUart_Cmd_Handler(void);
int main(void)
{
	vBsp_Init();
	while(1)
	{
		vUartReceiveIsOk();
		vUart_Cmd_Handler();
	}
}

void vBsp_Init(void)
{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); //开启AFIO时钟
		GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);// 使能swd关闭jtag接口
		delay_init();  	    //初始化延时函数
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
		LED_Init();
		uart_init(115200);	
		usmart_dev.init(SystemCoreClock/1000000);
		Encoder_Init_TIM2();            //初始化编码器接口
		Encoder_Init_TIM3();            //初始化编码器接口
		Encoder_Init_TIM4();            //初始化编码器接口
		Encoder_Init_TIM5();            //初始化编码器接口
		
		Motor_PWM_Init(7199,0);   		//=====初始化PWM 10KHZ，用于驱动电机
		Car_DIR_Stop();
		uart4_init(100000);
		
		//Uart_ANO_TC__Init();
		Uart_Dma_Init();
		TIM6_Init(100,7199);              //=====定时器中断
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

void vUartReceiveIsOk(void)
{
	if((DMA_UART_STRU.flag & 0x01) == 0x01)	//判断DMA串口接收标志位是否完成
		{
			DMA_UART_STRU.flag &= ~0x01; 		//清除DMA串口接收标志位
			DMA_UART_RECEIVE_Cmd(DISABLE);		//关闭DMA串口接收功能
			if(DMA_UART_STRU.uiReceivePack_FH == ((*(DMA_UART_STRU.ucReceivePack)<<8) + *(DMA_UART_STRU.ucReceivePack + 1)) \
				&& DMA_UART_STRU.uiReceivePack_FT == *(DMA_UART_STRU.ucReceivePack + DMA_UART_STRU.ucReceivePack_Length - 1))//检查数据包帧头,帧尾是否正确
			{
				DMA_UART_STRU.uiCheckReceivePack = \
				(*(DMA_UART_STRU.ucReceivePack + DMA_UART_STRU.ucReceivePack_Length - 2) << 8) \
				+ (*(DMA_UART_STRU.ucReceivePack + DMA_UART_STRU.ucReceivePack_Length - 3));
				if(ModBus_CRC(DMA_UART_STRU.ucReceivePack, 7) == DMA_UART_STRU.uiCheckReceivePack)		//判断数据包是检验位是否正确
				{
					DMA_UART_STRU.flag |= 0x80; 		//检验接收数据包成功
					memcpy(ucReceiveGlobal, DMA_UART_STRU.ucReceivePack + 2, 5);
				}
			}
			if(USART_GetFlagStatus(UART4, USART_FLAG_RXNE) == RESET)
			{
				RestartSetUartReceiveCount(0);	//重新开始接收串口指令个数
				DMA_UART_STRU.ucReceivePack = puCcurrent_Receive_Point;
			}
			else
			{
				RestartSetUartReceiveCount(1);	//重新开始接收串口指令个数
				DMA_UART_STRU.ucReceivePack = puCcurrent_Receive_Point + 1;
			}

			DMA_UART_RECEIVE_Cmd(ENABLE);	//打开DMA串口接收功能
		}
}

void vUart_Cmd_Handler(void)
{
	if(DMA_UART_STRU.flag & 0x80)
		{
			uint16_t pwm_temp = 0;
			uint8_t  ucIsUsePid = 0;
			DMA_UART_STRU.flag &= ~0x80;
			pwm_temp = ((ucReceiveGlobal[2] & 0x03) << 8) + ucReceiveGlobal[3];
			ucIsUsePid = ucReceiveGlobal[4] & 0x03;
			if(ucIsUsePid == 1)
			{
				vCar_Ation_Mode(ucReceiveGlobal[2] >> 2);
				PWMA = pwm_temp * 10;
				PWMB = pwm_temp * 10;	
				PWMD =	pwm_temp * 10;
				PWMC =	pwm_temp * 10;
			}
			else
			{
				Target = pwm_temp * 3;
				vCar_Set_PID(ucReceiveGlobal[2] >> 2 ,Target );
			}
		}
}



