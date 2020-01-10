#include "dma.h"





#if config_USE_DMA_ENABLE



#if config_USE_DMA_UART_RECEIVE
uint8_t *puCcurrent_Receive_Point = (void*)0;
uint8_t ucDma_Receive[config_USE_DMA_RECEIVE_SIZE * 2];
#endif


#if config_USE_DMA_UART_SEND
uint8_t ucDma_Send[config_USE_DMA_SEND_SIZE * 2];
#endif

t_DMA_UART_STRUCTURE DMA_UART_STRU;

static void vDMA_UART_STRU_Init(void)					//初始化vDMA_UART_STRU_Init();
{
	#if config_USE_DMA_UART_RECEIVE
	DMA_UART_STRU.ucReceivePack = ucDma_Receive;
	puCcurrent_Receive_Point = ucDma_Receive;
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
	DMA_UART_STRU.flag = 0;
}

void Uart_Dma_Init(void)
{
    DMA_InitTypeDef DMA_Init_Reg;
	NVIC_InitTypeDef NVIC_InitType;
	
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMAx, ENABLE);
	
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
    DMA_Init_Reg.DMA_Mode = DMA_Mode_Normal;
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
    //DMA_Cmd(UART_SEND_DMAx_Channelx, ENABLE);
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

void UART_RECEIVE_DMAx_Channelx_IRQHandler(void)
{
	if(DMA_GetITStatus(DMAx_RECEIVE_ITStatus))
	{
		/*
		可以在这里写串口接收完成后处理函数
		*/
		DMA_UART_STRU.flag |= 0x01;
		DMA_ClearITPendingBit(DMAx_RECEIVE_ITStatus);
	}
}

void UART_SEND_DMAx_Channelx_IRQHandler(void)
{
	if(DMA_GetITStatus(DMAx_SEND_ITStatus))
	{
		/*
		可以在这里写串口发送完成后处理函数
		*/
		DMA_UART_STRU.flag |= 0x02;
		DMA_ClearITPendingBit(DMAx_SEND_ITStatus);
	}
}

#if config_USE_DMA_UART_SEND
uint8_t * puiGetSendArray(void)
{
	uint8_t * pucTemp = (void *)(0);
	pucTemp = ucDma_Send;
	return pucTemp;
}
#endif

#if config_USE_DMA_UART_RECEIVE
uint8_t * puiGetReceiveArray(void)
{
	uint8_t * pucTemp = (void *)(0);
	pucTemp = ucDma_Receive;
	return pucTemp;
}
#endif


#endif
