#include "usart4.h"
#include "app_main.h"


void Usart4_Init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitTypeState;
	USART_InitTypeDef USART_InitTypeState;
	NVIC_InitTypeDef NVIC_InitTypeState;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	GPIO_InitTypeState.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitTypeState.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitTypeState.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitTypeState);
	
	GPIO_InitTypeState.GPIO_Mode=GPIO_Mode_IPU;;
	GPIO_InitTypeState.GPIO_Pin=GPIO_Pin_11;
	GPIO_Init(GPIOC,&GPIO_InitTypeState);

	USART_InitTypeState.USART_BaudRate=bound;
	USART_InitTypeState.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitTypeState.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitTypeState.USART_Parity=USART_Parity_No;
	USART_InitTypeState.USART_StopBits=USART_StopBits_1;
	USART_InitTypeState.USART_WordLength=USART_WordLength_8b;
	USART_Init(UART4,&USART_InitTypeState);
	
	NVIC_InitTypeState.NVIC_IRQChannel=UART4_IRQn;
	NVIC_InitTypeState.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitTypeState.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitTypeState.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitTypeState);
	
	USART_ITConfig(UART4,USART_IT_RXNE,ENABLE);
	USART_Cmd(UART4,ENABLE);
	
}

void Usart4_Send_Byte(u8 data)
{
	UART4->SR;
	UART4->DR=data;
	while((UART4->SR&0x40)==0);
	UART4->SR &=~0X40;
}

void Usart4_String_Send(u8 *data)
{
    while(*data!='\0')
	{
		Usart4_Send_Byte(*data);
		data++;
	}
}

void Usart4_String_Send1(u8 *data,u8 length)
{
    while(length--)
	{
		Usart4_Send_Byte(*data);
		data++;
	}
}
//帧头 55
//帧头 AA
//cmd
//data
//data
//包尾
//crc_l
//crc_h

u8 USART4_Num=0;

void UART4_IRQHandler(void)                	//串口1中断服务程序
{
	u8 Data=0;
	if(USART_GetITStatus(UART4,USART_IT_RXNE)!= RESET)
	{
		Data=USART_ReceiveData(UART4);
		switch(USART4_Num)
		{
			case 0:if(Data==0x55) {RemoteControlUsartData[USART4_Num]=Data;USART4_Num++;} else USART4_Num=0;break;
			case 1:if(Data==0xAA) {RemoteControlUsartData[USART4_Num]=Data;USART4_Num++;} else USART4_Num=0;break;
            case 2:
            case 3:
            case 4:
					RemoteControlUsartData[USART4_Num]=Data;
					USART4_Num++;
					break;
			case 5:if(Data==0xFF) 
					{
						RemoteControlUsartData[USART4_Num]=Data;
						USART4_Num++;
					} 
					else 
						USART4_Num=0;
					break;
            case 6:
				if(Data==(u8)ModBus_CRC(RemoteControlUsartData,6)) 
				{
					RemoteControlUsartData[USART4_Num]=Data;USART4_Num++;
				} 
				else
				{
					USART4_Num=0;
				}
				break;            
            case 7:
				if(Data==(u8)(ModBus_CRC(RemoteControlUsartData,6)>>8))
				{ 
					RemoteControlUsartData[USART4_Num]=Data;
					RemoteControlUsartData[8]=0xFF; USART4_Num=0;
				}
				USART4_Num=0;break;
		
            default: USART4_Num=0;
		}
		USART_ClearITPendingBit(UART4,USART_IT_RXNE);
	}
}





















