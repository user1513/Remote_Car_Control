#include "djiReceiver_dr16.h"

#if configUSE_DAJRECEIVER_MODE
#define ORIGINCH0 1024
#define ORIGINCH1 1024

extern uint16_t G_dr16_ch0_value ;
extern uint16_t G_dr16_ch1_value ;
extern uint16_t G_dr16_ch2_value ;
extern uint16_t G_dr16_ch3_value ;
extern uint8_t Artilleryflag;

uint8_t xdata uart_send_able[10] = {0x55,0xAA,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF};
unsigned char xdata G_dr16_array[25] = {
	0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00
};
uint8_t G_dr16_count = 0;

uint8_t flag = Disable;

uint16_t NumberOfFetching(uint8_t _value, uint8_t _bit)
{
	uint8_t number = 0;
	uint8_t mask = 0;

	switch(_bit)
	{
		case 1:
			mask = 0x01 << 0;
			number = _value & mask;
			number = number >> 0;
			return number;
		case 2:
			mask = 0x01 << 1;
			number = _value & mask;
			number = number >> 1;
			return number;
		case 3:
			mask = 0x01 << 2;
			number = _value & mask;
			number = number >> 2;
			return number;
		case 4:
			mask = 0x01 << 3;
			number = _value & mask;
			number = number >> 3;
			return number;
		case 5:
			mask = 0x01 << 4;
			number = _value & mask;
			number = number >> 4;
			return number;
		case 6:
			mask = 0x01 << 5;
			number = _value & mask;
			number = number >> 5;
			return number;
		case 7:
			mask = 0x01 << 6;
			number = _value & mask;
			number = number >> 6;
			return number;
		case 8:
			mask = 0x01 << 7;
			number = _value & mask;
			number = number >> 7;
			return number;
		default:
			return 2;
	}
}


void DR16DataAnalysis(uint8_t _data)
{
	
	if(flag != Enable)
	{
		G_dr16_array[G_dr16_count] = _data;
		
		switch(G_dr16_count)
		{
			case 0:
				
				if(G_dr16_array[G_dr16_count] == 0x0F)
				{
					G_dr16_count ++;
					
				}else
				{
					G_dr16_count = 0;
				}
				break;
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
			case 10:
				G_dr16_count ++;
				break;
			case 11:
			case 12:
			case 13:
			case 14:
			case 15:
			case 16:
			case 17:
			case 18:
			case 19:
			case 20:
			case 21:
			case 22:
				G_dr16_count ++;
				break;
			case 23:
				if(G_dr16_array[G_dr16_count] == 0x00)
				{
					G_dr16_count ++;
				}else
				{
					G_dr16_count = 0;
				}
				break;
			case 24:
				if(G_dr16_array[G_dr16_count] == 0x00)
				{
					
					G_dr16_ch0_value  = NumberOfFetching(G_dr16_array[2], 3) * 1024;
					G_dr16_ch0_value += NumberOfFetching(G_dr16_array[2], 2) * 512;
					G_dr16_ch0_value += NumberOfFetching(G_dr16_array[2], 1) * 256;
					G_dr16_ch0_value += NumberOfFetching(G_dr16_array[1], 8) * 128;
					G_dr16_ch0_value += NumberOfFetching(G_dr16_array[1], 7) * 64;
					G_dr16_ch0_value += NumberOfFetching(G_dr16_array[1], 6) * 32;
					G_dr16_ch0_value += NumberOfFetching(G_dr16_array[1], 5) * 16;
					G_dr16_ch0_value += NumberOfFetching(G_dr16_array[1], 4) * 8;
					G_dr16_ch0_value += NumberOfFetching(G_dr16_array[1], 3) * 4;
					G_dr16_ch0_value += NumberOfFetching(G_dr16_array[1], 2) * 2;
					G_dr16_ch0_value += NumberOfFetching(G_dr16_array[1], 1) * 1;
					
					
					G_dr16_ch1_value  = NumberOfFetching(G_dr16_array[3], 6) * 1024;
					G_dr16_ch1_value += NumberOfFetching(G_dr16_array[3], 5) * 512;
					G_dr16_ch1_value += NumberOfFetching(G_dr16_array[3], 4) * 256;
					G_dr16_ch1_value += NumberOfFetching(G_dr16_array[3], 3) * 128;
					G_dr16_ch1_value += NumberOfFetching(G_dr16_array[3], 2) * 64;
					G_dr16_ch1_value += NumberOfFetching(G_dr16_array[3], 1) * 32;
					G_dr16_ch1_value += NumberOfFetching(G_dr16_array[2], 8) * 16;
					G_dr16_ch1_value += NumberOfFetching(G_dr16_array[2], 7) * 8;
					G_dr16_ch1_value += NumberOfFetching(G_dr16_array[2], 6) * 4;
					G_dr16_ch1_value += NumberOfFetching(G_dr16_array[2], 5) * 2;
					G_dr16_ch1_value += NumberOfFetching(G_dr16_array[2], 4) * 1;

					G_dr16_ch2_value  = NumberOfFetching(G_dr16_array[6], 4) * 1024;
					G_dr16_ch2_value += NumberOfFetching(G_dr16_array[6], 3) * 512;
					G_dr16_ch2_value += NumberOfFetching(G_dr16_array[6], 2) * 256;
					G_dr16_ch2_value += NumberOfFetching(G_dr16_array[6], 1) * 128;
					G_dr16_ch2_value += NumberOfFetching(G_dr16_array[5], 8) * 64;
					G_dr16_ch2_value += NumberOfFetching(G_dr16_array[5], 7) * 32;
					G_dr16_ch2_value += NumberOfFetching(G_dr16_array[5], 6) * 16;
					G_dr16_ch2_value += NumberOfFetching(G_dr16_array[5], 5) * 8;
					G_dr16_ch2_value += NumberOfFetching(G_dr16_array[5], 4) * 4;
					G_dr16_ch2_value += NumberOfFetching(G_dr16_array[5], 3) * 2;
					G_dr16_ch2_value += NumberOfFetching(G_dr16_array[5], 2) * 1;

					G_dr16_ch3_value  = NumberOfFetching(G_dr16_array[5], 1) * 1024;
					G_dr16_ch3_value += NumberOfFetching(G_dr16_array[4], 8) * 512;
					G_dr16_ch3_value += NumberOfFetching(G_dr16_array[4], 7) * 256;
					G_dr16_ch3_value += NumberOfFetching(G_dr16_array[4], 6) * 128;
					G_dr16_ch3_value += NumberOfFetching(G_dr16_array[4], 5) * 64;
					G_dr16_ch3_value += NumberOfFetching(G_dr16_array[4], 4) * 32;
					G_dr16_ch3_value += NumberOfFetching(G_dr16_array[4], 3) * 16;
					G_dr16_ch3_value += NumberOfFetching(G_dr16_array[4], 2) * 8;
					G_dr16_ch3_value += NumberOfFetching(G_dr16_array[4], 1) * 4;
					G_dr16_ch3_value += NumberOfFetching(G_dr16_array[3], 8) * 2;
					G_dr16_ch3_value += NumberOfFetching(G_dr16_array[3], 7) * 1;

					if ((G_dr16_array[7] == 0xC0) && (G_dr16_array[8] == 0x02) && (G_dr16_array[9] == 0x17) && (G_dr16_array[10] == 0x18))
					{
						//ԭλ
						uart_send_able[6] &= ~0x01;
						uart_send_able[6] &= ~0x02;
					}
					else if ((G_dr16_array[7] == 0xC0) && (G_dr16_array[8] == 0xFF) && (G_dr16_array[9] == 0x14))
					{
						//HL
						uart_send_able[6] |= 0x01;
						uart_send_able[6] &= ~0x02;
					}
					else if ((G_dr16_array[7] == 0x40) && (G_dr16_array[8] == 0x00) && (G_dr16_array[9] == 0x16))
					{
						uart_send_able[6] |= 0x01 << 1;
						uart_send_able[6] &= ~0x01;
						//CL
					}
					
					if ((G_dr16_array[7] == 0xC0) && (G_dr16_array[8] == 0x02) && (G_dr16_array[9] == 0x17) && (G_dr16_array[10] == 0x18))
					{
						//ԭλGPS
						uart_send_able[6] &= ~(0x01 << 2);
						uart_send_able[6] &= ~(0x01 << 3);
					}
					else if ((G_dr16_array[8] == 0x02) && (G_dr16_array[9] == 0x03) && (G_dr16_array[10] == 0x10))
					{
						//ATTI��
						uart_send_able[6] |= 0x01 << 2;
						uart_send_able[6] &= ~(0x01 << 3);
					}
					else if ((G_dr16_array[8] == 0x02) && (G_dr16_array[9] == 0xFF) && (G_dr16_array[10] == 0x07))
					{
						//ATTI��
						uart_send_able[6] |= 0x01 << 3;
						uart_send_able[6] &= ~(0x01 << 2);
					}

					//����
					if ((G_dr16_array[7] == 0xC0) && (G_dr16_array[6] == 0x08))
					{
						//"����ԭλ";
						uart_send_able[6] &= ~(0x01 << 4);
						uart_send_able[6] &= ~(0x01 << 5);
						
					}
					else if ((G_dr16_array[7] == 0xC2) && (G_dr16_array[6] == 0x38))
					{
						//������
						uart_send_able[6] |= 0x01 << 4;
						uart_send_able[6] &= ~(0x01 << 5);
						
					}
					else if ((G_dr16_array[7] == 0xE9) && (G_dr16_array[6] == 0x48))
					{
						//������
						uart_send_able[6] |= 0x01 << 5;
						uart_send_able[6] &= ~(0x01 << 4);	
					}
					flag = Enable;
					config_RECEIVE_DISABLE_FLAG;
				}
				G_dr16_count = 0;
				break;
			default:
				G_dr16_count = 0;
				break;
		}
	}
}


eCarMode vGetaction(float fAngle,uint16_t lineLength)
{
	eCarMode eCarModeState = Car_STOP;
	static eCarMode eLastCarModeState = Car_STOP;
	if(lineLength > config_ACTION_START_MINVAL)				//������ң���ƶ���С�ķ���,С���趨ֵʱС��ģʽ����stop
	{
		if((fAngle<= 22.5 && fAngle>= 0) || ((fAngle > 360 - 22.5) && fAngle <= 360 ))				//����ÿ���Ƕ�ִ�еĶ���
		{
			eCarModeState = Car_Angle_0;
		}else if (fAngle<= 67.5 && fAngle> 22.5)
		{
			eCarModeState = Car_Angle_45;
		}
		else if (fAngle<= 90 + 22.5 && fAngle> 67.5)
		{
			eCarModeState = Car_Angle_90;
		}
		else if (fAngle<= 135 + 22.5 && fAngle> 90 + 22.5)
		{
			eCarModeState = Car_Angle_135;
		}
		else if (fAngle<= 180 + 22.5 && fAngle> 135 + 22.5)
		{
			eCarModeState = Car_Angle_180;
		}
		else if (fAngle<= 225 + 22.5 && fAngle> 180 + 22.5)
		{
			eCarModeState = Car_Angle_225;
		}
		else if (fAngle<= 270 && fAngle> 225 + 22.5 )
		{
			eCarModeState = Car_Angle_270;
		}
		else
		{
			eCarModeState = Car_Angle_315;
		}
	}
	if(eLastCarModeState == Car_Angle_90 || eLastCarModeState == Car_Angle_270)		//�ж�Car_AngleR_360��Car_AngleL_360ָ��,��תֻ��ʱ���й�
	{
		if(eCarModeState == Car_Angle_45 || eCarModeState == Car_Angle_315)
		{
			eLastCarModeState = Car_AngleR_360;
		}
		else if (eCarModeState == Car_Angle_135 || eCarModeState == Car_Angle_225)
		{
			eLastCarModeState = Car_AngleL_360;
		}		
	}
	if(eCarModeState == Car_Angle_45 ||\
	   eCarModeState == Car_Angle_135 ||\
	   eCarModeState == Car_Angle_225 ||\ 
	   eCarModeState == Car_Angle_315)//�ж��Ƿ��˳�Car_AngleR_360��Car_AngleL_360ָ��
	{
		if(eLastCarModeState == Car_AngleR_360 || eLastCarModeState == Car_AngleL_360)
		{
			eCarModeState = eLastCarModeState;
		}
	}
		eLastCarModeState = eCarModeState;

	return eCarModeState;
}

void vGetAngleInfo(void)
{
	uint16_t Check_val=0;																		//CRCУ��ʹ��
	static float lastval_L = 0,lastval_R = 0;
	float  lineLength, fCurrentval;
	uint16_t *pusLineLength = (void*)0;
	eCarMode eCarModeState;
	fCurrentval = fGetAngle(G_dr16_ch0_value, G_dr16_ch1_value, &lastval_R,&lineLength);		//��Ƕ�,ģ
	pusLineLength = (uint16_t*)&uart_send_able[4];
	*pusLineLength = (uint16_t)lineLength;														//lineLength ��ҡ�˷��� ������Ӧ����
	eCarModeState = vGetaction(fCurrentval, lineLength);										//��fCurrentval ����ҡ�˽Ƕȴ���vGetaction()�л�ȡ�˶�ָ��
	uart_send_able[4] |= (uint8_t)eCarModeState<<2;												//uart_send_able[4] ����λ��Ϊ�˶�ָ��洢,��2λ�Ӻ�һ���ֽڴ洢��ҡ�˷���
	
	
	fCurrentval = fGetAngle(G_dr16_ch2_value, G_dr16_ch3_value, &lastval_L,&lineLength);		//��Ƕ�,ģ
	pusLineLength = (uint16_t*)&uart_send_able[2];
	*pusLineLength = (uint16_t)fCurrentval;														//��fCurrentval ����ҡ�˽Ƕ� ������Ӧ����
	
	Check_val=ModBus_CRC(uart_send_able,7);   													//CRCУ��
	uart_send_able[7]=Check_val;  
	uart_send_able[8]=Check_val>>8;
	
	Uart2SendStrLen(uart_send_able,10);															//uart2�������ݰ�
}

float fGetAngle(uint16_t uChannel_x,uint16_t uChannel_y,float * const lastval,float * const lineLength)//lineLength ֱ�߳���=ģ
{
	float fAngle = 0,fAnglecalc = 0;//�Ƕ� / �Ƕȼ����м����
	int _ch_tempx = uChannel_x - 1024;//��0Ϊ����ԭ��
	int _ch_tempy = uChannel_y - 1024;//��0Ϊ����ԭ��
	fAnglecalc = sqrt((pow((float)_ch_tempx,2)+pow((float)_ch_tempy,2)));//��ģ
	*lineLength = fAnglecalc;											//��ģȡ��
	if(fAnglecalc != 0.0)
		fAngle = asin((float)_ch_tempy/fAnglecalc)*180/PI;				//�Ƕȼ���
	
	if(*lineLength > 660)												//�����޷�ֵ
	{
		*lineLength = 660;
	}
	
	if(0 <= fAngle && _ch_tempx < 0 )
	{
		fAngle = 90 + 90 - fAngle;
	}else if(0 > fAngle && _ch_tempx <= 0)
	{
		fAngle = 180 - fAngle;
	}
	else if(0 > fAngle && _ch_tempx > 0)
	{
		fAngle = 180 + 90 + 90 + fAngle;
	}
	if(fAngle > 360)
	{
		fAngle = *lastval;
	}
	*lastval = fAngle;
	return fAngle;
}


#endif
