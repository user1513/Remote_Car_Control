#ifndef _ANO_TC_H
#define _ANO_TC_H

#include "sys.h"

//////////////////////////////////////////////////////////////////////////
/*
使用匿名上位机软件
在调用串口dma时需要使能对应串口dma功能
USART_DMACmd(USART1, USART_DMAReq_Tx|USART_DMAReq_Rx,  ENABLE);	
	uart4_init(100000);
	Uart_Dma_Init();
*/
/////////////////////////////////////////////////////////////////////////
#define config_USE_ANO_TC_ENABLE  1  		//配置DMA模式使能

#define config_USE_ANO_TC_UART_RECEIVE 1	//配置匿名上位机串口接收模式使能
#define config_USE_ANO_TC_UART_SEND 1		//配置匿名上位机串口发送模式使能

#define config_ANO_TC_UART_RECEIVE_NVIC 1	//配置匿名上位机串口接收模式中断使能
#define config_ANO_TC_UART_SEND_NVIC 1		//配置匿名上位机串口发送模式中断使能


#define config_USE_ANO_TC_RECEIVE_SIZE 30	//配置匿名上位机串口接收总大小
#define config_USE_ANO_TC_SEND_SIZE 60		//配置匿名上位机串口发送总大小

#define config_ANO_TC_SOURCE_ADDER 			0X05		//本地源地址
#define config_ANO_TC_DESTINATION_ADDER 	0XAF		//目的地地址
#define config_ANO_TC_DATAPACK_FH 			0XAA		//匿名上位机数据包帧头
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
如果更改了串口只需要更改下面宏定义部分的参数
*/
#define _ANO_TC_RCC_AHBPeriph_DMAx RCC_AHBPeriph_DMA1 		//匿名上位机dma配置时钟线
#define _ANO_TC_DMAx_RECEIVE_ITStatus DMA1_IT_TC5			//重新定义匿名上位机接收串口dma中断状态
#define _ANO_TC_DMAx_SEND_ITStatus DMA1_IT_TC4				//重新定义匿名上位机发送串口dma中断状态

#define _ANO_TC_UART_RECEIVE_DMAx_Channelx 	DMA1_Channel5	//重新定义匿名上位机DMA通道号
#define _ANO_TC_UART_SEND_DMAx_Channelx 	DMA1_Channel4	//重新定义匿名上位机DMA通道号

#define _ANO_TC_UART_RX_Channelx 		USART1				//重新定义匿名上位机串口源地址通道号
#define _ANO_TC_UART_TX_Channelx 		USART1				//重新定义匿名上位机串口源地址通道号

#define _ANO_TC_UART_RECEIVE_DMAx_Channelx_IRQn	 DMA1_Channel5_IRQn//重新定义匿名上位机DMA串口接收中断线通道号
#define _ANO_TC_UART_SEND_DMAx_Channelx_IRQn	 DMA1_Channel4_IRQn//重新定义匿名上位机DMA串口发送中断线通道号
//DMA1_Channel5_IRQHandler
#define _ANO_TC_UART_RECEIVE_DMAx_Channelx_IRQHandler DMA1_Channel5_IRQHandler	//重新定义匿名上位机DMA串口接收完成中断处理函数
#define _ANO_TC_UART_SEND_DMAx_Channelx_IRQHandler 	  DMA1_Channel4_IRQHandler		//重新定义匿名上位机DMA串口发送完成中断处理函数
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//#if config_USE_DMA_ENABLE
//typedef struct _DMA_UART_STRUCTURE
//{
//	#if config_USE_DMA_UART_RECEIVE
//	uint16_t uiReceivePack_FH;			//接收数据包帧头
//	uint8_t  uiReceivePack_FT;			//接收数据包帧尾
//	uint8_t ucReceivePack_Length; 		//接收数据包长度
//	uint8_t *ucReceivePack;				//接收数据包内容存放指针地址
//	uint16_t uiCheckReceivePack;		//接收数据包校验值
//	#endif
//	#if config_USE_DMA_UART_SEND
//	uint16_t uiSendPack_FH;			//发送数据包帧头
//	uint8_t  uiSendPack_FT;			//发送数据包帧尾
//	uint8_t ucSendPack_Length; 		//发送数据包长度
//	uint8_t *ucSendPack;				//发送数据包内容存放指针地址
//	uint16_t uiCheckSendPack;			//接收数据包校验值
//	#endif
//	uint8_t flag;
//}t_DMA_UART_STRUCTURE;
//#endif

#define _ANO_TC_UART_RECEIVE_Cmd(x) DMA_Cmd(_ANO_TC_UART_RECEIVE_DMAx_Channelx, x) //匿名上位机dma串口接收使能宏定义

#define RestartSet_ANO_TC_UartReceiveCount(x) DMA_SetCurrDataCounter(_ANO_TC_UART_RECEIVE_DMAx_Channelx, config_USE_ANO_TC_RECEIVE_SIZE + x)//匿名上位机dma串口接收个数重新设定宏定义

//extern t_DMA_UART_STRUCTURE DMA_UART_STRU;

//extern uint8_t *puCcurrent_Receive_Point;

void Uart_ANO_TC__Init(void);			//初始化匿名上位机dma接口
		
void vANO_TC_UART_SEND(void);			//发送config_USE_ANO_TC_SEND_SIZE固定长度

uint8_t * puiGet_ANO_TC_SendArray(void);			//获取发送ANO_TC_SendArra

uint8_t * puiGet_ANO_TC_ReceiveArray(void);			//获取接收ANO_TC_SendArra

/* *putData数据包格式:"功能字1byte"	"数据长度1byte"	"数据N byte" */

void vANO_TC_Send(uint8_t *putData);					//数据发送

#endif

