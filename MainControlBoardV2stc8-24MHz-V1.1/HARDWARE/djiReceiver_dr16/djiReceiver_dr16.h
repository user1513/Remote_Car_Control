#ifndef __DJIRECEIVER_DR16_H
#define __DJIRECEIVER_DR16_H

#include "appconf.h"
#if configUSE_DAJRECEIVER_MODE

typedef enum
{
	Car_STOP = 0,
	Car_Angle_0,
	Car_Angle_45,
	Car_Angle_90,
	Car_Angle_135,
	Car_Angle_180,
	Car_Angle_225,
	Car_Angle_270,
	Car_Angle_315,
	Car_AngleL_360,
	Car_AngleR_360
}eCarMode;

void DR16DataAnalysis(uint8_t _data);
void Send_dji_Data(uint8_t _cmd,uint8_t _data0,uint8_t _data1);
uint8_t Remote_Control(uint16_t ch0,uint16_t ch1,uint8_t data1,uint8_t data2);
int tabletennisdata(uint16_t ch2,uint16_t ch3,int _angleval);
void Artillerydata(uint16_t ch2,uint16_t ch3);

eCarMode vGetaction(float fAngle,uint16_t lineLength);
void vGetAngleInfo(void);
float fGetAngle(uint16_t uChannel_x,uint16_t uChannel_y,float * const lastval,float * const lineLength);
#define config_RECEIVE_FLAG ES
#define config_RECEIVE_ENBALE_FLAG config_RECEIVE_FLAG = 1
#define config_RECEIVE_DISABLE_FLAG config_RECEIVE_FLAG = 0
#define config_ACTION_START_MINVAL 50 //当设置遥感移动最小的幅度,小于设定值时小车模式处于stop

#endif
#endif