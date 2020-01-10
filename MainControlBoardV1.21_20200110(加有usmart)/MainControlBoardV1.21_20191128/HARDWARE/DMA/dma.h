#ifndef _DMA_H
#define _DMA_H

#include "sys.h"

//////////////////////////////////////////////////////////////////////////
/*
�ڵ��ô���dmaʱ��Ҫʹ�ܶ�Ӧ����dma����
USART_DMACmd(USART1, USART_DMAReq_Tx|USART_DMAReq_Rx,  ENABLE);	
	uart4_init(100000);
	Uart_Dma_Init();
*/
/////////////////////////////////////////////////////////////////////////
#define config_USE_DMA_ENABLE  1  		//����DMAģʽʹ��

#define config_USE_DMA_UART_RECEIVE 1	//����DMA���ڽ���ģʽʹ��
#define config_USE_DMA_UART_SEND 0		//����DMA���ڷ���ģʽʹ��

#define config_DMA_UART_RECEIVE_NVIC 1	//����DMA���ڽ���ģʽ�ж�ʹ��
#define config_DMA_UART_SEND_NVIC 0		//����DMA���ڷ���ģʽ�ж�ʹ��


#define config_USE_DMA_RECEIVE_SIZE 10	//����DMA���ڽ����ܴ�С
#define config_USE_DMA_SEND_SIZE 10		//����DMA���ڷ����ܴ�С

#define config_RECEIVE_FH 	0X55AA		//���ý������ݰ�֡ͷ
#define config_RECEIVE_FT 	0XFF		//���ý������ݰ�֡β
#define config_SEND_FH	 	0X55AA		//���÷������ݰ�֡ͷ
#define config_SEND_FT 		0XFF		//���÷������ݰ�֡β

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
��������˴���ֻ��Ҫ��������궨�岿�ֵĲ���
*/
#define RCC_AHBPeriph_DMAx RCC_AHBPeriph_DMA2 		//dma����ʱ����
#define DMAx_RECEIVE_ITStatus DMA2_IT_TC3			//���¶�����մ���dma�ж�״̬
#define DMAx_SEND_ITStatus DMA2_IT_TC5				//���¶��巢�ʹ���dma�ж�״̬

#define UART_RECEIVE_DMAx_Channelx 	DMA2_Channel3	//���¶���DMAͨ����
#define UART_SEND_DMAx_Channelx 	DMA2_Channel5	//���¶���DMAͨ����

#define UART_RX_Channelx 		UART4				//���¶��崮��Դ��ַͨ����
#define UART_TX_Channelx 		UART4				//���¶��崮��Դ��ַͨ����

#define UART_RECEIVE_DMAx_Channelx_IRQn	 DMA2_Channel3_IRQn//���¶���DMA���ڽ����ж���ͨ����
#define UART_SEND_DMAx_Channelx_IRQn	 DMA2_Channel4_5_IRQn//���¶���DMA���ڷ����ж���ͨ����

#define UART_RECEIVE_DMAx_Channelx_IRQHandler DMA2_Channel3_IRQHandler	//���¶���DMA���ڽ�������жϴ�����
#define UART_SEND_DMAx_Channelx_IRQHandler DMA2_Channel4_5_IRQHandler		//���¶���DMA���ڷ�������жϴ�����
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if config_USE_DMA_ENABLE
typedef struct _DMA_UART_STRUCTURE
{
	#if config_USE_DMA_UART_RECEIVE
	uint16_t uiReceivePack_FH;			//�������ݰ�֡ͷ
	uint8_t  uiReceivePack_FT;			//�������ݰ�֡β
	uint8_t ucReceivePack_Length; 		//�������ݰ�����
	uint8_t *ucReceivePack;				//�������ݰ����ݴ��ָ���ַ
	uint16_t uiCheckReceivePack;		//�������ݰ�У��ֵ
	#endif
	#if config_USE_DMA_UART_SEND
	uint16_t uiSendPack_FH;			//�������ݰ�֡ͷ
	uint8_t  uiSendPack_FT;			//�������ݰ�֡β
	uint8_t ucSendPack_Length; 		//�������ݰ�����
	uint8_t *ucSendPack;				//�������ݰ����ݴ��ָ���ַ
	uint16_t uiCheckSendPack;			//�������ݰ�У��ֵ
	#endif
	uint8_t flag;
}t_DMA_UART_STRUCTURE;
#endif

#define DMA_UART_RECEIVE_Cmd(x) DMA_Cmd(UART_RECEIVE_DMAx_Channelx, x) //dma���ڽ���ʹ�ܺ궨��


#define RestartSetUartReceiveCount(x) DMA_SetCurrDataCounter(UART_RECEIVE_DMAx_Channelx, config_USE_DMA_RECEIVE_SIZE + x)

extern t_DMA_UART_STRUCTURE DMA_UART_STRU;

extern uint8_t *puCcurrent_Receive_Point;
void Uart_Dma_Init(void);

void vDMA_UART_SEND(void);

uint8_t * puiGetSendArray(void);

uint8_t * puiGetReceiveArray(void);



#endif

