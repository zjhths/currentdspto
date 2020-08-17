/*
 * Data_Exchange.c
 *
 *  Created on: 2017-5-19
 *      Author: 418
 */
#include "stdint.h"

#include "Data_Exchange.h"
#include "rs232_rs422.h"
#define BYTE0(dwTemp)       ( *( (char *)(&dwTemp)    ) )
#define BYTE1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )
#define BYTE2(dwTemp)       ( *( (char *)(&dwTemp) + 2) )
#define BYTE3(dwTemp)       ( *( (char *)(&dwTemp) + 3) )

uint8_t Config_Flag=0;
uint8_t data_to_send[50];	//·¢ËÍÊý¾Ý»º´æ
void ANO_DT_Send_Data(uint8_t *dataToSend , uint8_t length)
{
	COM_Send(5,dataToSend,length);
}

static void ANO_DT_Send_Check(uint8_t head, uint8_t check_sum)
{
	data_to_send[0]=0xAA;
	data_to_send[1]=0xAA;
	data_to_send[2]=0xEF;
	data_to_send[3]=2;
	data_to_send[4]=head;
	data_to_send[5]=check_sum;


	uint8_t sum = 0;
	uint8_t i=0;
	for(;i<6;i++)
		sum += data_to_send[i];
	data_to_send[6]=sum;

	ANO_DT_Send_Data(data_to_send, 7);
}
void ANO_DT_Send_Senser(int16_t a_x,int16_t a_y,int16_t a_z,int16_t g_x,int16_t g_y,int16_t g_z,int16_t m_x,int16_t m_y,int16_t m_z,int32_t bar)
{
	uint8_t _cnt=0;
	int16_t _temp;

	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x02;
	data_to_send[_cnt++]=0;

	_temp = a_x;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = a_y;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = a_z;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);

	_temp = g_x;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = g_y;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = g_z;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);

	_temp = m_x;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = m_y;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = m_z;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	data_to_send[3] = _cnt-4;

	uint8_t sum = 0;
	uint8_t i=0;
	for(;i<_cnt;i++)
	sum += data_to_send[i];
	data_to_send[_cnt++] = sum;
	//COM_Send(5,data_to_send,_cnt);
	ANO_DT_Send_Data(data_to_send, _cnt);

}
void ANO_DT_Send_Status(float angle_rol, float angle_pit, float angle_yaw, int32_t alt, uint8_t fly_model, uint8_t armed)
{
	uint8_t _cnt=0;
	int16_t _temp;
	int32_t _temp2 = alt;

	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x01;
	data_to_send[_cnt++]=0;

	_temp = (int)(angle_rol*100);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = (int)(angle_pit*100);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	if(angle_yaw>180)  angle_yaw -=360;

	_temp = (int)(angle_yaw*100);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);

	data_to_send[_cnt++]=BYTE3(_temp2);
	data_to_send[_cnt++]=BYTE2(_temp2);
	data_to_send[_cnt++]=BYTE1(_temp2);
	data_to_send[_cnt++]=BYTE0(_temp2);

	data_to_send[_cnt++] = fly_model;

	data_to_send[_cnt++] = armed;

	data_to_send[3] = _cnt-4;

	uint8_t sum = 0;
	uint8_t i=0;
	for(;i<_cnt;i++)
		sum += data_to_send[i];
	data_to_send[_cnt++]=sum;

	ANO_DT_Send_Data(data_to_send, _cnt);
}
void ANO_DT_Send_GPS(uint8_t State,uint8_t Num,float Lat, float Lon, float Return)
{
	uint8_t _cnt=0;

	int8_t _temp;
	int16_t _temp1;
	int32_t _temp2;

	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x04;
	data_to_send[_cnt++]=0;

	_temp = State;
	data_to_send[_cnt++]=BYTE0(_temp);

	_temp = Num;
	data_to_send[_cnt++]=BYTE0(_temp);

	_temp2 = (int)(Lat*10000000);
	data_to_send[_cnt++]=BYTE3(_temp2);
	data_to_send[_cnt++]=BYTE2(_temp2);
	data_to_send[_cnt++]=BYTE1(_temp2);
	data_to_send[_cnt++]=BYTE0(_temp2);

	_temp2 = (int)(Lon*10000000);
	data_to_send[_cnt++]=BYTE3(_temp2);
	data_to_send[_cnt++]=BYTE2(_temp2);
	data_to_send[_cnt++]=BYTE1(_temp2);
	data_to_send[_cnt++]=BYTE0(_temp2);

	_temp1= (short)Return*10;
	data_to_send[_cnt++]=BYTE1(_temp1);
	data_to_send[_cnt++]=BYTE0(_temp1);

	data_to_send[3] = _cnt-4;

	uint8_t sum = 0;
	uint8_t i=0;
	for(;i<_cnt;i++)
		sum += data_to_send[i];
	data_to_send[_cnt++]=sum;

	ANO_DT_Send_Data(data_to_send, _cnt);
}
uint8_t  data_to_send_float(uint8_t cnt,float temp)
{
		data_to_send[cnt++]=BYTE3(temp);
		data_to_send[cnt++]=BYTE2(temp);
		data_to_send[cnt++]=BYTE1(temp);
		data_to_send[cnt++]=BYTE0(temp);
		return cnt;
}
void Send_NAV(float lat, float lon, float height,float vx, float vy, float vz)
{
	uint8_t _cnt=0;

	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xF1;
	data_to_send[_cnt++]=0;

	_cnt=data_to_send_float(_cnt,lat);
	_cnt=data_to_send_float(_cnt,lon);
	_cnt=data_to_send_float(_cnt,height);
	_cnt=data_to_send_float(_cnt,vx);
	_cnt=data_to_send_float(_cnt,vy);
	_cnt=data_to_send_float(_cnt,vz);

	data_to_send[3] = _cnt-4;

	uint8_t sum = 0;
	uint8_t i=0;
	for(;i<_cnt;i++)
		sum += data_to_send[i];
	data_to_send[_cnt++]=sum;

	ANO_DT_Send_Data(data_to_send, _cnt);
}

void Send_GPSDATA(float lat, float lon, float height,float vx, float vy, float vz)
{
	    uint8_t _cnt=0;

		data_to_send[_cnt++]=0xAA;
		data_to_send[_cnt++]=0xAA;
		data_to_send[_cnt++]=0xF2;
		data_to_send[_cnt++]=0;

		_cnt=data_to_send_float(_cnt,lat);
		_cnt=data_to_send_float(_cnt,lon);
		_cnt=data_to_send_float(_cnt,height);
		_cnt=data_to_send_float(_cnt,vx);
		_cnt=data_to_send_float(_cnt,vy);
		_cnt=data_to_send_float(_cnt,vz);

		data_to_send[3] = _cnt-4;

		uint8_t sum = 0;
		uint8_t i=0;
		for(;i<_cnt;i++)
			sum += data_to_send[i];
		data_to_send[_cnt++]=sum;

		ANO_DT_Send_Data(data_to_send, _cnt);
}
