#ifndef _DMA_H
#define _DMA_H

#include "sys.h"

//////////////////////////////////////////////////////////////////////////
/*
在调用串口dma时需要使能对应串口dma功能
USART_DMACmd(USART1, USART_DMAReq_Tx|USART_DMAReq_Rx,  ENABLE);	
	uart4_init(100000);
	Uart_Dma_Init();
*/
/////////////////////////////////////////////////////////////////////////
#define config_USE_DMA_ENABLE  1  		//配置DMA模式使能

#define config_USE_DMA_UART_RECEIVE 1	//配置DMA串口接收模式使能
#define config_USE_DMA_UART_SEND 0		//配置DMA串口发送模式使能

#define config_DMA_UART_RECEIVE_NVIC 1	//配置DMA串口接收模式中断使能
#define config_DMA_UART_SEND_NVIC 0		//配置DMA串口发送模式中断使能


#define config_USE_DMA_RECEIVE_SIZE 10	//配置DMA串口接收总大小
#define config_USE_DMA_SEND_SIZE 10		//配置DMA串口发送总大小

#define config_RECEIVE_FH 	0X55AA		//配置接收数据包帧头
#define config_RECEIVE_FT 	0XFF		//配置接收数据包帧尾
#define config_SEND_FH	 	0X55AA		//配置发送数据包帧头
#define config_SEND_FT 		0XFF		//配置发送数据包帧尾

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
如果更改了串口只需要更改下面宏定义部分的参数
*/
#define RCC_AHBPeriph_DMAx RCC_AHBPeriph_DMA2 		//dma配置时钟线
#define DMAx_RECEIVE_ITStatus DMA2_IT_TC3			//重新定义接收串口dma中断状态
#define DMAx_SEND_ITStatus DMA2_IT_TC5				//重新定义发送串口dma中断状态

#define UART_RECEIVE_DMAx_Channelx 	DMA2_Channel3	//重新定义DMA通道号
#define UART_SEND_DMAx_Channelx 	DMA2_Channel5	//重新定义DMA通道号

#define UART_RX_Channelx 		UART4				//重新定义串口源地址通道号
#define UART_TX_Channelx 		UART4				//重新定义串口源地址通道号

#define UART_RECEIVE_DMAx_Channelx_IRQn	 DMA2_Channel3_IRQn//重新定义DMA串口接收中断线通道号
#define UART_SEND_DMAx_Channelx_IRQn	 DMA2_Channel4_5_IRQn//重新定义DMA串口发送中断线通道号

#define UART_RECEIVE_DMAx_Channelx_IRQHandler DMA2_Channel3_IRQHandler	//重新定义DMA串口接收完成中断处理函数
#define UART_SEND_DMAx_Channelx_IRQHandler DMA2_Channel4_5_IRQHandler		//重新定义DMA串口发送完成中断处理函数
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if config_USE_DMA_ENABLE
typedef struct _DMA_UART_STRUCTURE
{
	#if config_USE_DMA_UART_RECEIVE
	uint16_t uiReceivePack_FH;			//接收数据包帧头
	uint8_t  uiReceivePack_FT;			//接收数据包帧尾
	uint8_t ucReceivePack_Length; 		//接收数据包长度
	uint8_t *ucReceivePack;				//接收数据包内容存放指针地址
	uint16_t uiCheckReceivePack;		//接收数据包校验值
	#endif
	#if config_USE_DMA_UART_SEND
	uint16_t uiSendPack_FH;			//发送数据包帧头
	uint8_t  uiSendPack_FT;			//发送数据包帧尾
	uint8_t ucSendPack_Length; 		//发送数据包长度
	uint8_t *ucSendPack;				//发送数据包内容存放指针地址
	uint16_t uiCheckSendPack;			//接收数据包校验值
	#endif
	uint8_t flag;
}t_DMA_UART_STRUCTURE;
#endif

#define DMA_UART_RECEIVE_Cmd(x) DMA_Cmd(UART_RECEIVE_DMAx_Channelx, x) //dma串口接收使能宏定义


#define RestartSetUartReceiveCount(x) DMA_SetCurrDataCounter(UART_RECEIVE_DMAx_Channelx, config_USE_DMA_RECEIVE_SIZE + x)

extern t_DMA_UART_STRUCTURE DMA_UART_STRU;

extern uint8_t *puCcurrent_Receive_Point;
void Uart_Dma_Init(void);

void vDMA_UART_SEND(void);

uint8_t * puiGetSendArray(void);

uint8_t * puiGetReceiveArray(void);



#endif

