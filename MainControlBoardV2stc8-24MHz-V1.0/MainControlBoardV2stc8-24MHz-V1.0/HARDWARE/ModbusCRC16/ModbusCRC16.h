#ifndef _MODBUSCRC16_H
#define _MODBUSCRC16_H

#include "appconf.h"

#if configUSE_MODBUSCRC16_MODE
uint16_t ModBus_CRC(uint8_t * arg, uint16_t length);
#endif

#endif

