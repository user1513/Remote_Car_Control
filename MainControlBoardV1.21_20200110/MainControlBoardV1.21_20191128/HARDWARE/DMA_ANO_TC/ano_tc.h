#ifndef _ANO_TC_H
#define _ANO_TC_H

#include "sys.h"

//////////////////////////////////////////////////////////////////////////
/*
ʹ��������λ�����
�ڵ��ô���dmaʱ��Ҫʹ�ܶ�Ӧ����dma����
USART_DMACmd(USART1, USART_DMAReq_Tx|USART_DMAReq_Rx,  ENABLE);	
	uart4_init(100000);
	Uart_Dma_Init();
*/
/////////////////////////////////////////////////////////////////////////
#define config_USE_ANO_TC_ENABLE  1  		//����DMAģʽʹ��

#define config_USE_ANO_TC_UART_RECEIVE 1	//����������λ�����ڽ���ģʽʹ��
#define config_USE_ANO_TC_UART_SEND 1		//����������λ�����ڷ���ģʽʹ��

#define config_ANO_TC_UART_RECEIVE_NVIC 1	//����������λ�����ڽ���ģʽ�ж�ʹ��
#define config_ANO_TC_UART_SEND_NVIC 1		//����������λ�����ڷ���ģʽ�ж�ʹ��


#define config_USE_ANO_TC_RECEIVE_SIZE 30	//����������λ�����ڽ����ܴ�С
#define config_USE_ANO_TC_SEND_SIZE 60		//����������λ�����ڷ����ܴ�С

#define config_ANO_TC_SOURCE_ADDER 			0X05		//����Դ��ַ
#define config_ANO_TC_DESTINATION_ADDER 	0XAF		//Ŀ�ĵص�ַ
#define config_ANO_TC_DATAPACK_FH 			0XAA		//������λ�����ݰ�֡ͷ
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
��������˴���ֻ��Ҫ��������궨�岿�ֵĲ���
*/
#define _ANO_TC_RCC_AHBPeriph_DMAx RCC_AHBPeriph_DMA1 		//������λ��dma����ʱ����
#define _ANO_TC_DMAx_RECEIVE_ITStatus DMA1_IT_TC5			//���¶���������λ�����մ���dma�ж�״̬
#define _ANO_TC_DMAx_SEND_ITStatus DMA1_IT_TC4				//���¶���������λ�����ʹ���dma�ж�״̬

#define _ANO_TC_UART_RECEIVE_DMAx_Channelx 	DMA1_Channel5	//���¶���������λ��DMAͨ����
#define _ANO_TC_UART_SEND_DMAx_Channelx 	DMA1_Channel4	//���¶���������λ��DMAͨ����

#define _ANO_TC_UART_RX_Channelx 		USART1				//���¶���������λ������Դ��ַͨ����
#define _ANO_TC_UART_TX_Channelx 		USART1				//���¶���������λ������Դ��ַͨ����

#define _ANO_TC_UART_RECEIVE_DMAx_Channelx_IRQn	 DMA1_Channel5_IRQn//���¶���������λ��DMA���ڽ����ж���ͨ����
#define _ANO_TC_UART_SEND_DMAx_Channelx_IRQn	 DMA1_Channel4_IRQn//���¶���������λ��DMA���ڷ����ж���ͨ����
//DMA1_Channel5_IRQHandler
#define _ANO_TC_UART_RECEIVE_DMAx_Channelx_IRQHandler DMA1_Channel5_IRQHandler	//���¶���������λ��DMA���ڽ�������жϴ�����
#define _ANO_TC_UART_SEND_DMAx_Channelx_IRQHandler 	  DMA1_Channel4_IRQHandler		//���¶���������λ��DMA���ڷ�������жϴ�����
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//#if config_USE_DMA_ENABLE
//typedef struct _DMA_UART_STRUCTURE
//{
//	#if config_USE_DMA_UART_RECEIVE
//	uint16_t uiReceivePack_FH;			//�������ݰ�֡ͷ
//	uint8_t  uiReceivePack_FT;			//�������ݰ�֡β
//	uint8_t ucReceivePack_Length; 		//�������ݰ�����
//	uint8_t *ucReceivePack;				//�������ݰ����ݴ��ָ���ַ
//	uint16_t uiCheckReceivePack;		//�������ݰ�У��ֵ
//	#endif
//	#if config_USE_DMA_UART_SEND
//	uint16_t uiSendPack_FH;			//�������ݰ�֡ͷ
//	uint8_t  uiSendPack_FT;			//�������ݰ�֡β
//	uint8_t ucSendPack_Length; 		//�������ݰ�����
//	uint8_t *ucSendPack;				//�������ݰ����ݴ��ָ���ַ
//	uint16_t uiCheckSendPack;			//�������ݰ�У��ֵ
//	#endif
//	uint8_t flag;
//}t_DMA_UART_STRUCTURE;
//#endif

#define _ANO_TC_UART_RECEIVE_Cmd(x) DMA_Cmd(_ANO_TC_UART_RECEIVE_DMAx_Channelx, x) //������λ��dma���ڽ���ʹ�ܺ궨��

#define RestartSet_ANO_TC_UartReceiveCount(x) DMA_SetCurrDataCounter(_ANO_TC_UART_RECEIVE_DMAx_Channelx, config_USE_ANO_TC_RECEIVE_SIZE + x)//������λ��dma���ڽ��ո��������趨�궨��

//extern t_DMA_UART_STRUCTURE DMA_UART_STRU;

//extern uint8_t *puCcurrent_Receive_Point;

void Uart_ANO_TC__Init(void);			//��ʼ��������λ��dma�ӿ�
		
void vANO_TC_UART_SEND(void);			//����config_USE_ANO_TC_SEND_SIZE�̶�����

uint8_t * puiGet_ANO_TC_SendArray(void);			//��ȡ����ANO_TC_SendArra

uint8_t * puiGet_ANO_TC_ReceiveArray(void);			//��ȡ����ANO_TC_SendArra

/* *putData���ݰ���ʽ:"������1byte"	"���ݳ���1byte"	"����N byte" */

void vANO_TC_Send(uint8_t *putData);					//���ݷ���

#endif

