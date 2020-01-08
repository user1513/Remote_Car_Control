#include "ano_tc.h"





#if config_USE_ANO_TC_ENABLE

static uint8_t utAdd8_Check(uint8_t *putData, uint8_t utLength);
static void vANO_TC_UART_SEND_LENGTH(uint8_t utLength);
static void vData_Pack_Create(void);						//将初始数据写入
static uint8_t * putData_Pack_Data_Updata(uint8_t *putData, uint8_t utLength);		//数据更新


#if config_USE_ANO_TC_UART_RECEIVE
//uint8_t *puCcurrent_Receive_Point = (void*)0;
uint8_t ucANO_TC_Dma_Receive[config_USE_ANO_TC_RECEIVE_SIZE];
#endif


#if config_USE_ANO_TC_UART_SEND
uint8_t ucANO_TC_Dma_Send[config_USE_ANO_TC_SEND_SIZE];
#endif

//t_DMA_UART_STRUCTURE DMA_UART_STRU;

//static void vDMA_UART_STRU_Init(void)					//初始化vDMA_UART_STRU_Init();
//{
//	#if config_USE_DMA_UART_RECEIVE
//	DMA_UART_STRU.ucReceivePack = ucANO_TC_Dma_Receive;
//	puCcurrent_Receive_Point = ucANO_TC_Dma_Receive;
//	DMA_UART_STRU.ucReceivePack_Length = config_USE_DMA_RECEIVE_SIZE;
//	DMA_UART_STRU.uiCheckReceivePack =	0;
//	DMA_UART_STRU.uiReceivePack_FH = config_RECEIVE_FH;		//
//	DMA_UART_STRU.uiReceivePack_FT = config_RECEIVE_FT;
//	#endif
//	#if config_USE_DMA_UART_SEND
//	DMA_UART_STRU.ucSendPack_Length = config_USE_DMA_SEND_SIZE - 5;
//	DMA_UART_STRU.ucSendPack = ucANO_TC_Dma_Send;
//	DMA_UART_STRU.uiCheckSendPack = 0;
//	DMA_UART_STRU.uiSendPack_FH = config_SEND_FH;
//	DMA_UART_STRU.uiSendPack_FT = config_SEND_FT;
//	
//	*(DMA_UART_STRU.ucSendPack) = DMA_UART_STRU.uiSendPack_FH >> 8;
//	*(DMA_UART_STRU.ucSendPack + 1) = DMA_UART_STRU.uiSendPack_FH;
//	*(DMA_UART_STRU.ucSendPack + config_USE_DMA_SEND_SIZE - 1) = DMA_UART_STRU.uiSendPack_FT;
//	#endif
//	DMA_UART_STRU.flag = 0;
//}

void Uart_ANO_TC__Init(void)
{
    DMA_InitTypeDef DMA_Init_Reg;
	NVIC_InitTypeDef NVIC_InitType;
	
    RCC_AHBPeriphClockCmd(_ANO_TC_RCC_AHBPeriph_DMAx, ENABLE);
	vData_Pack_Create();
    //vDMA_UART_STRU_Init();
    #if config_USE_ANO_TC_UART_SEND
    DMA_Init_Reg.DMA_BufferSize = config_USE_ANO_TC_SEND_SIZE;
    DMA_Init_Reg.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_Init_Reg.DMA_M2M = DMA_M2M_Disable;
    DMA_Init_Reg.DMA_MemoryBaseAddr = (uint32_t)ucANO_TC_Dma_Send;
    DMA_Init_Reg.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_Init_Reg.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_Init_Reg.DMA_Mode = DMA_Mode_Normal;
    DMA_Init_Reg.DMA_PeripheralBaseAddr = (uint32_t)&_ANO_TC_UART_TX_Channelx->DR;
    DMA_Init_Reg.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_Init_Reg.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_Init_Reg.DMA_Priority = DMA_Priority_High;
    
    DMA_Init(_ANO_TC_UART_SEND_DMAx_Channelx, &DMA_Init_Reg);
	
		#if config_ANO_TC_UART_SEND_NVIC
		NVIC_InitType.NVIC_IRQChannel = _ANO_TC_UART_SEND_DMAx_Channelx_IRQn;//DMA串口发送中断线
		NVIC_InitType.NVIC_IRQChannelPreemptionPriority = 2;
		NVIC_InitType.NVIC_IRQChannelSubPriority = 2;
		NVIC_InitType.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitType);
		
		DMA_ITConfig(_ANO_TC_UART_SEND_DMAx_Channelx,DMA_IT_TC,ENABLE);//设置dma中断类型
		#endif
	#endif
	
	#if config_USE_ANO_TC_UART_RECEIVE
	DMA_Init_Reg.DMA_BufferSize = config_USE_ANO_TC_RECEIVE_SIZE;
    DMA_Init_Reg.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_Init_Reg.DMA_M2M = DMA_M2M_Disable;
    DMA_Init_Reg.DMA_MemoryBaseAddr = (uint32_t)ucANO_TC_Dma_Receive;
    DMA_Init_Reg.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_Init_Reg.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_Init_Reg.DMA_Mode = DMA_Mode_Normal;
    DMA_Init_Reg.DMA_PeripheralBaseAddr = (uint32_t)&_ANO_TC_UART_RX_Channelx->DR;
    DMA_Init_Reg.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_Init_Reg.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_Init_Reg.DMA_Priority = DMA_Priority_High;
    
    DMA_Init(_ANO_TC_UART_RECEIVE_DMAx_Channelx, &DMA_Init_Reg);
	
		#if config_ANO_TC_UART_RECEIVE_NVIC
		NVIC_InitType.NVIC_IRQChannel = _ANO_TC_UART_RECEIVE_DMAx_Channelx_IRQn;//DMA串口接收中断线
		NVIC_InitType.NVIC_IRQChannelPreemptionPriority = 2;
		NVIC_InitType.NVIC_IRQChannelSubPriority = 2;
		NVIC_InitType.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitType);
		
		DMA_ITConfig(_ANO_TC_UART_RECEIVE_DMAx_Channelx,DMA_IT_TC,ENABLE);//设置dma中断类型
		#endif
	#endif 	
	
	#if config_USE_ANO_TC_UART_RECEIVE
    DMA_Cmd(_ANO_TC_UART_RECEIVE_DMAx_Channelx, ENABLE);
	#endif
	
	#if config_USE_ANO_TC_UART_SEND
    //DMA_Cmd(_ANO_TC_UART_SEND_DMAx_Channelx, ENABLE);
	#endif
}

#if config_USE_ANO_TC_UART_SEND
void vANO_TC_UART_SEND(void)
{
	DMA_Cmd(_ANO_TC_UART_SEND_DMAx_Channelx, DISABLE);
	DMA_SetCurrDataCounter(_ANO_TC_UART_SEND_DMAx_Channelx, config_USE_ANO_TC_SEND_SIZE);
	DMA_Cmd(_ANO_TC_UART_SEND_DMAx_Channelx, ENABLE);	
}

static void vANO_TC_UART_SEND_LENGTH(uint8_t utLength)
{
	DMA_Cmd(_ANO_TC_UART_SEND_DMAx_Channelx, DISABLE);
	DMA_SetCurrDataCounter(_ANO_TC_UART_SEND_DMAx_Channelx, utLength);
	DMA_Cmd(_ANO_TC_UART_SEND_DMAx_Channelx, ENABLE);	
}

static void vData_Pack_Create(void)						//将初始数据写入
{
	uint8_t *putTemp = (void *)0;
	
	putTemp = puiGet_ANO_TC_SendArray();
	
	putTemp[0] = config_ANO_TC_DATAPACK_FH;				//将帧头写入
	
	putTemp[1] = config_ANO_TC_SOURCE_ADDER;			//将源地址写入
	
	putTemp[2] = config_ANO_TC_DESTINATION_ADDER;		//将目标地址写入
}

static uint8_t * putData_Pack_Data_Updata(uint8_t *putData, uint8_t utLength)		//数据更新
{
	uint8_t *putTemp = (void *)0;
	
	putTemp = puiGet_ANO_TC_SendArray() + 3;
	
	memcpy(putTemp, putData,utLength);
	
	return putTemp - 3;
}

void vANO_TC_Send(uint8_t *putData)					//数据发送
{
	uint8_t *putTemp = (void *)0;
	
	uint8_t utLength = putData[1] + 2;
	
	uint8_t utCheckVal = 0;
	
	putTemp = putData_Pack_Data_Updata(putData, utLength);
	
	utCheckVal = utAdd8_Check(putTemp, utLength + 3);
	
	putTemp[3 + utLength] = utCheckVal;
	
	vANO_TC_UART_SEND_LENGTH(4 + utLength);
}

static uint8_t utAdd8_Check(uint8_t *putData, uint8_t utLength)//add8校验
{
	uint8_t utSum = 0;
	while(utLength--)
	{
		utSum += *putData;
		putData ++;
	}
	return utSum;
}

#endif

void _ANO_TC_UART_RECEIVE_DMAx_Channelx_IRQHandler(void)
{
	if(DMA_GetITStatus(_ANO_TC_DMAx_RECEIVE_ITStatus))
	{
		/*
		可以在这里写串口接收完成后处理函数
		*/
		//DMA_UART_STRU.flag |= 0x01;
		DMA_ClearITPendingBit(_ANO_TC_DMAx_RECEIVE_ITStatus);
	}
}

void _ANO_TC_UART_SEND_DMAx_Channelx_IRQHandler(void)
{
	if(DMA_GetITStatus(_ANO_TC_DMAx_SEND_ITStatus))
	{
		/*
		可以在这里写串口发送完成后处理函数
		*/
		//DMA_UART_STRU.flag |= 0x02;
		DMA_ClearITPendingBit(_ANO_TC_DMAx_SEND_ITStatus);
	}
}

#if config_USE_ANO_TC_UART_SEND
uint8_t * puiGet_ANO_TC_SendArray(void)
{
	uint8_t * pucTemp = (void *)(0);
	pucTemp = ucANO_TC_Dma_Send;
	return pucTemp;
}
#endif

#if config_USE_ANO_TC_UART_RECEIVE
uint8_t * puiGet_ANO_TC_ReceiveArray(void)
{
	uint8_t * pucTemp = (void *)(0);
	pucTemp = ucANO_TC_Dma_Receive;
	return pucTemp;
}
#endif


#endif
