#include "dma.h"



//////////////////////////////////////////////////////////////////////////
/*
在调用串口dma时需要使能对应串口dma功能
USART_DMACmd(USART1, USART_DMAReq_Tx|USART_DMAReq_Rx,  ENABLE);	
*/
/////////////////////////////////////////////////////////////////////////
#define config_USE_DMA_ENABLE  1  		//配置DMA模式使能

#define config_USE_DMA_UART_RECEIVE 1	//配置DMA串口接收模式使能
#define config_USE_DMA_UART_SEND 1		//配置DMA串口发送模式使能

#define config_DMA_UART_RECEIVE_NVIC 1	//配置DMA串口接收模式中断使能
#define config_DMA_UART_SEND_NVIC 1		//配置DMA串口发送模式中断使能


#define config_USE_DMA_RECEIVE_SIZE 10	//配置DMA串口接收总大小
#define config_USE_DMA_SEND_SIZE 10		//配置DMA串口发送总大小

#define config_RECEIVE_FH 	0X55AA		//配置接收数据包帧头
#define config_RECEIVE_FT 	0XFF		//配置接收数据包帧尾
#define config_SEND_FH	 	0X55AA		//配置发送数据包帧头
#define config_SEND_FT 		0XFF		//配置发送数据包帧尾


#define UART_RECEIVE_DMAx_Channelx 	DMA1_Channel6 	//重新定义DMA通道号
#define UART_SEND_DMAx_Channelx 	DMA1_Channel7	//重新定义DMA通道号

#define UART_RX_Channelx 		USART2				//重新定义串口源地址通道号
#define UART_TX_Channelx 		USART2				//重新定义串口源地址通道号

#define UART_RECEIVE_DMAx_Channelx_IRQn	 DMA1_Channel6_IRQn//重新定义DMA串口接收中断线通道号
#define UART_SEND_DMAx_Channelx_IRQn	 DMA1_Channel7_IRQn//重新定义DMA串口发送中断线通道号

#define UART_RECEIVE_DMAx_Channelx_IRQHandler DMA1_Channel6_IRQHandler	//重新定义DMA串口接收完成中断处理函数
#define UART_SEND_DMAx_Channelx_IRQHandler DMA1_Channel7_IRQHandler		//重新定义DMA串口发送完成中断处理函数

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
}t_DMA_UART_STRUCTURE;

#if config_USE_DMA_UART_RECEIVE
uint8_t ucDma_Receive[config_USE_DMA_RECEIVE_SIZE];
#endif

#if config_USE_DMA_UART_SEND
uint8_t ucDma_Send[config_USE_DMA_SEND_SIZE];
#endif

t_DMA_UART_STRUCTURE DMA_UART_STRU;

static void vDMA_UART_STRU_Init(void)					//初始化vDMA_UART_STRU_Init();
{
	#if config_USE_DMA_UART_RECEIVE
	DMA_UART_STRU.ucReceivePack = ucDma_Receive;
	DMA_UART_STRU.ucReceivePack_Length = config_USE_DMA_RECEIVE_SIZE;
	DMA_UART_STRU.uiCheckReceivePack =	0;
	DMA_UART_STRU.uiReceivePack_FH = config_RECEIVE_FH;		//
	DMA_UART_STRU.uiReceivePack_FT = config_RECEIVE_FT;
	#endif
	#if config_USE_DMA_UART_SEND
	DMA_UART_STRU.ucSendPack_Length = config_USE_DMA_SEND_SIZE - 5;
	DMA_UART_STRU.ucSendPack = ucDma_Send;
	DMA_UART_STRU.uiCheckSendPack = 0;
	DMA_UART_STRU.uiSendPack_FH = config_SEND_FH;
	DMA_UART_STRU.uiSendPack_FT = config_SEND_FT;
	
	*(DMA_UART_STRU.ucSendPack) = DMA_UART_STRU.uiSendPack_FH >> 8;
	*(DMA_UART_STRU.ucSendPack + 1) = DMA_UART_STRU.uiSendPack_FH;
	*(DMA_UART_STRU.ucSendPack + config_USE_DMA_SEND_SIZE - 1) = DMA_UART_STRU.uiSendPack_FT;
	#endif
}

void Uart_Dma_Init(void)
{
    DMA_InitTypeDef DMA_Init_Reg;
	NVIC_InitTypeDef NVIC_InitType;
	
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
    vDMA_UART_STRU_Init();
    #if config_USE_DMA_UART_SEND
    DMA_Init_Reg.DMA_BufferSize = config_USE_DMA_SEND_SIZE;
    DMA_Init_Reg.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_Init_Reg.DMA_M2M = DMA_M2M_Disable;
    DMA_Init_Reg.DMA_MemoryBaseAddr = (uint32_t)ucDma_Send;
    DMA_Init_Reg.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_Init_Reg.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_Init_Reg.DMA_Mode = DMA_Mode_Normal;
    DMA_Init_Reg.DMA_PeripheralBaseAddr = (uint32_t)&UART_TX_Channelx->DR;
    DMA_Init_Reg.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_Init_Reg.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_Init_Reg.DMA_Priority = DMA_Priority_High;
    
    DMA_Init(UART_SEND_DMAx_Channelx, &DMA_Init_Reg);
	
		#if config_DMA_UART_SEND_NVIC
		NVIC_InitType.NVIC_IRQChannel = UART_SEND_DMAx_Channelx_IRQn;//DMA串口发送中断线
		NVIC_InitType.NVIC_IRQChannelPreemptionPriority = 2;
		NVIC_InitType.NVIC_IRQChannelSubPriority = 1;
		NVIC_InitType.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitType);
		
		DMA_ITConfig(UART_SEND_DMAx_Channelx,DMA_IT_TC,ENABLE);//设置dma中断类型
		#endif
	#endif
	
	#if config_USE_DMA_UART_RECEIVE
	DMA_Init_Reg.DMA_BufferSize = config_USE_DMA_RECEIVE_SIZE;
    DMA_Init_Reg.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_Init_Reg.DMA_M2M = DMA_M2M_Disable;
    DMA_Init_Reg.DMA_MemoryBaseAddr = (uint32_t)ucDma_Receive;
    DMA_Init_Reg.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_Init_Reg.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_Init_Reg.DMA_Mode = DMA_Mode_Circular;
    DMA_Init_Reg.DMA_PeripheralBaseAddr = (uint32_t)&UART_RX_Channelx->DR;
    DMA_Init_Reg.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_Init_Reg.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_Init_Reg.DMA_Priority = DMA_Priority_High;
    
    DMA_Init(UART_RECEIVE_DMAx_Channelx, &DMA_Init_Reg);
	
		#if config_DMA_UART_RECEIVE_NVIC
		NVIC_InitType.NVIC_IRQChannel = UART_RECEIVE_DMAx_Channelx_IRQn;//DMA串口接收中断线
		NVIC_InitType.NVIC_IRQChannelPreemptionPriority = 2;
		NVIC_InitType.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitType.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitType);
		
		DMA_ITConfig(UART_RECEIVE_DMAx_Channelx,DMA_IT_TC,ENABLE);//设置dma中断类型
		#endif
	#endif 	
	
	#if config_USE_DMA_UART_RECEIVE
    DMA_Cmd(UART_RECEIVE_DMAx_Channelx, ENABLE);
	#endif
	
	#if config_USE_DMA_UART_SEND
    DMA_Cmd(UART_SEND_DMAx_Channelx, ENABLE);
	#endif
}

#if config_USE_DMA_UART_SEND
void vDMA_UART_SEND(void)
{
	DMA_Cmd(UART_SEND_DMAx_Channelx, DISABLE);
	DMA_SetCurrDataCounter(UART_SEND_DMAx_Channelx, config_USE_DMA_SEND_SIZE);
	DMA_Cmd(UART_SEND_DMAx_Channelx, ENABLE);	
}
#endif

uint8_t flag = 0;
uint8_t flag1 = 0;
void UART_RECEIVE_DMAx_Channelx_IRQHandler(void)
{
	if(DMA_GetITStatus(DMA1_IT_TC6))
	{
		flag = ~flag;
		DMA_ClearITPendingBit(DMA1_IT_TC6);
	}
}

void UART_SEND_DMAx_Channelx_IRQHandler(void)
{
	if(DMA_GetITStatus(DMA1_IT_TC7))
	{
		flag1 = ~flag1;
		DMA_ClearITPendingBit(DMA1_IT_TC7);
	}
}

uint8_t * puiGetSendArray(void)
{
	uint8_t * pucTemp = (void *)(0);
	pucTemp = ucDma_Send;
	return pucTemp;
}
uint8_t * puiGetReceiveArray(void)
{
	uint8_t * pucTemp = (void *)(0);
	pucTemp = ucDma_Receive;
	return pucTemp;
}
//#define ADC_CHANNEL_NUM 2

//uint16_t uAdc_Channel[ADC_CHANNEL_NUM];

//void Adc_Dma_Init(void)
//{
//    DMA_InitTypeDef DMA_Init_Reg;

//    DMA_Init_Reg.DMA_BufferSize = ADC_CHANNEL_NUM;
//    DMA_Init_Reg.DMA_DIR = DMA_DIR_PeripheralSRC;
//    DMA_Init_Reg.DMA_M2M = DMA_M2M_Disable;
//    DMA_Init_Reg.DMA_MemoryBaseAddr = (uint32_t)uAdc_Channel;
//    DMA_Init_Reg.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
//    DMA_Init_Reg.DMA_MemoryInc = DMA_MemoryInc_Enable;
//    DMA_Init_Reg.DMA_Mode = DMA_Mode_Circular;
//    DMA_Init_Reg.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;
//    DMA_Init_Reg.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
//    DMA_Init_Reg.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
//    DMA_Init_Reg.DMA_Priority = DMA_Priority_Medium;
//    
//	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

//    DMA_Init(DMA1_Channel1, &DMA_Init_Reg);
//}

//uint16_t num, num1;



#endif
