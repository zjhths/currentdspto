/*
 * Data_Exchange.h
 *
 *  Created on: 2017-5-19
 *      Author: 418
 */

#ifndef DATA_EXCHANGE_H_
#define DATA_EXCHANGE_H_




extern uint8_t Config_Flag;
extern void ANO_DT_Send_Senser(int16_t a_x,int16_t a_y,int16_t a_z,int16_t g_x,int16_t g_y,int16_t g_z,int16_t m_x,int16_t m_y,int16_t m_z,int32_t bar);
extern void ANO_DT_Send_Status(float angle_rol, float angle_pit, float angle_yaw, int32_t alt, uint8_t fly_model, uint8_t armed);
extern void ANO_DT_Send_GPS(uint8_t State,uint8_t Num,float Lat, float Lon, float Return);
extern void Send_GPSDATA(float lat, float lon, float height,float vx, float vy, float vz);
extern void Send_NAV(float lat, float lon, float height,float vx, float vy, float vz);
#endif /* DATA_EXCHANGE_H_ */
