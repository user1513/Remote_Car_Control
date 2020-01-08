#ifndef _MODBUSCRC16_H
#define _MODBUSCRC16_H

#include "sys.h"
#define configUSE_MODBUSCRC16_MODE 1

#if configUSE_MODBUSCRC16_MODE
uint16_t ModBus_CRC(uint8_t * arg, uint16_t length);
#endif

#endif

