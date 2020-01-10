#ifndef __USART4_H
#define __USART4_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板
//串口3驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2014/3/29
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   


void uart4_init(u32 bound);			//串口3初始化 

void Uart4_Send_Byte(u8 data);
void Uart4_String_Send(u8 *data);
void Uart4_String_Send_Length(u8 *data,u8 length);
#endif
