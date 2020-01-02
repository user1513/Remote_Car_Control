#ifndef _USART4_H
#define _USART4_H

#include "sys.h"
#include "Data_Check.h"


void Usart4_Init(u32 bound);
void Usart4_String_Send(u8 *data);
void Usart4_Send_Byte(u8 data);
void Usart4_String_Send1(u8 *data,u8 length);

#endif



