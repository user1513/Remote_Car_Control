#ifndef _DMA_H
#define _DMA_H

#include "sys.h"

void Uart_Dma_Init(void);

void vDMA_UART_SEND(void);

uint8_t * puiGetSendArray(void);

uint8_t * puiGetReceiveArray(void);
#endif

