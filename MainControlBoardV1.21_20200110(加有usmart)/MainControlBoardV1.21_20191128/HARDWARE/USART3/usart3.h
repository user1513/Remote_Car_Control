#ifndef __USART3_H
#define __USART3_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//����3��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2014/3/29
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   


void usart3_init(u32 bound);			//����3��ʼ�� 
void Usart3_Send_Byte(uint8_t data);
void Usart3_String_Send(uint8_t *data);
void Usart3_String_Send_Length(uint8_t *data,uint8_t length);
#endif
