#ifndef __USART4_H
#define __USART4_H	 
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


void uart4_init(u32 bound);			//����3��ʼ�� 

void Uart4_Send_Byte(u8 data);
void Uart4_String_Send(u8 *data);
void Uart4_String_Send_Length(u8 *data,u8 length);
#endif
