#ifndef _APPCONF_H
#define _APPCONF_H


#define uint8_t unsigned char
#define uint16_t unsigned int
#define uint32_t unsigned long int	

#define pdTURE 1
#define pdFALSE 0
#define Enable pdTURE
#define Disable pdFALSE

#define configUSE_CCP_MODE 0
#define configUSE_TIMER1_MODE 1
#define configUSE_UART1_MODE 1
#define configUSE_UART2_MODE 1
#define configUSE_UART3_MODE 0
#define configUSE_DAJRECEIVER_MODE 1
#define configUSE_MODBUSCRC16_MODE 1

#define PI 3.1415926
#include <STC8.H>
#include "uart1.h"
#include "uart2.h"
#include "uart3.h"
#include "timer1.h"
#include "djiReceiver_dr16.h"
#include <intrins.h>
#include "ccp.h"
#include "ModbusCRC16.h"
#include "stdio.h"
#include "math.h"




#endif

