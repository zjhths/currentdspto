/*
 * mnic_timer.h
 *
 * Created on: 2015-12-7
 * Author: SUN
 */
//����Ԥ���������ֹͷ�ļ��ظ������ͱ���
#ifndef MNIC_TIMER_H_
#define MNIC_TIMER_H_

#define TMR_PERIOD_LSB32             0x00037AA0 // 228000  1ms for 456/2MHz   ��ʱ��ʱ��Դ����Ϊ�ڲ�ʱ��Դ����Ĭ��ΪCPU_CLK/2  //(0x000002AC)//684	//(0x00002C88)
#define TMR_PERIOD_MSB32               (0x0)

void TimerInit(void);
void TimerIntInit(void);
extern unsigned char GPS_R_Flag;
extern unsigned char AD_Read_Flag;
extern unsigned char IMU_Flag;
extern unsigned char Data_Exchange_Flag;
extern unsigned char InitEnd_Flag;
extern unsigned char Navigation_Flag;
#endif /* MNIC_TIMER_H_ */
