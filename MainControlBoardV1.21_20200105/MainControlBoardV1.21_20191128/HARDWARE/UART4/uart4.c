#include "uart4.h"
 
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板
//串口3驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2014/3/29
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

//串口3中断服务函数
void USART4_IRQHandler(void)
{
	u8 res;	      
	if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)//接收到数据
	{	 
		res =USART_ReceiveData(UART4);		 
	}  				 											 
}   


//初始化IO 串口3
//pclk1:PCLK1时钟频率(Mhz)
//bound:波特率	  
void uart4_init(u32 bound)
{  

//	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	                       //GPIOB时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);                          //串口3时钟使能

 	USART_DeInit(UART4);  //复位串口3
	//USART3_TX   PB10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;                                     //PB10
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	                               //复用推挽输出
    GPIO_Init(GPIOC, &GPIO_InitStructure);                                         //初始化PB10
   
    //USART3_RX	  PB11
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;                          //浮空输入
    GPIO_Init(GPIOC, &GPIO_InitStructure);                                         //初始化PB11
	
	USART_InitStructure.USART_BaudRate = bound;                                    //波特率一般设置为9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;                    //字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;                         //一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;                            //无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	               //收发模式
  
	USART_Init(UART4, &USART_InitStructure);       //初始化串口3
  
	USART_DMACmd(UART4, USART_DMAReq_Tx|USART_DMAReq_Rx,  ENABLE);	
	
	USART_Cmd(UART4, ENABLE);                      //使能串口 
	
	//使能接收中断
 //   USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);  //开启中断   
	
	//设置中断优先级
//	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;//抢占优先级3
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
//	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	
}

void Uart4_Send_Byte(u8 data)
{
	UART4->SR;
	UART4->DR=data;
	while((UART4->SR&0x40)==0);
	UART4->SR &=~0X40;
}

void Uart4_String_Send(u8 *data)
{
    while(*data!='\0')
	{
		Uart4_Send_Byte(*data);
		data++;
	}
}

void Uart4_String_Send_Length(u8 *data,u8 length)
{
    while(length--)
	{
		Uart4_Send_Byte(*data);
		data++;
	}
}
