/*
 * mnic_timer.c
 * ģ�鹦�ܣ���ʱ��ģ��Զ�ʱ����ʱʱ�䣬��ʱ���жϽ���������
 *  Created on: 2015-12-7
 *      Author: SUN
 */

#include "hw_types.h"
#include "timer.h"
#include "interrupt.h"
#include "soc_C6748.h"
#include "mnic_timer.h"
#include "mnic_test.h"
#include "fpga.h"


static void TimerIsr();

/*
 * ��������	 void TimerSetUp64Bit(void)
 * �������ܣ�  ���ö�ʱ��ģʽ����ʱʱ��
 * ������ڣ�
 * �������ڣ�
 */
void TimerInit(void)
{
	/*����ʱ��2���ó�64λͨ�ö�ʱ��ģʽ��ʹ���ڲ�ʱ��ԴĬ��ΪCPU_CLK/2*/
	TimerConfigure(SOC_TMR_2_REGS, TMR_CFG_64BIT_CLK_INT);

	/*��mnic_timer.h�����ֵ����TIMER12��TIMER34,����64λ��ʱ����ʱʱ��Ϊ228000*2/456/1000000=1ms */
	TimerPeriodSet(SOC_TMR_2_REGS, TMR_TIMER12, TMR_PERIOD_LSB32);
	TimerPeriodSet(SOC_TMR_2_REGS, TMR_TIMER34, TMR_PERIOD_MSB32);

	/*��ʱ����������*/
	
	TimerEnable(SOC_TMR_2_REGS, TMR_TIMER12, TMR_ENABLE_CONT);
}

/*
 * ��������	 void TimerIntInit(void)
 * �������ܣ�  ��ʱ���жϳ�ʼ��
 * ������ڣ�
 * �������ڣ�
 */
void TimerIntInit(void)
{
	/*ʹ��TMIER12�ж�Ϊ��ͨģʽ*/
	TimerIntEnable(SOC_TMR_2_REGS, TMR_INT_TMR12_NON_CAPT_MODE);

	/*���ж��������е�INT6ע��Ϊ��ʱ���жϷ������TimerIsr*/
    IntRegister(C674X_MASK_INT6, TimerIsr);

    /*ӳ���жϵ� DSP�������ж�INT6*/
    IntEventMap(C674X_MASK_INT6, SYS_INT_T64P2_TINTALL);

    /*ʹ��DSP�������ж�INT6*/
    IntEnable(C674X_MASK_INT6);
    EMIF(LED_CONFIG)=2;
}

unsigned char GPS_R_Flag=0;
unsigned char AD_Read_Flag=0;
unsigned char IMU_Flag=0;
unsigned char Data_Exchange_Flag=0;
unsigned char InitEnd_Flag=0;
unsigned char Navigation_Flag=0;


extern  void HDLC_Parse();
extern void  VM_IM_CtrlOutPut();
/*
 * ��������	 static void TimerIsr()
 * �������ܣ�  ��ʱ���жϷ������
 * ������ڣ�
 * �������ڣ�
 */
static void TimerIsr()
{
	/*�رն�ʱ��2�ж�*/
	TimerIntDisable(SOC_TMR_2_REGS, TMR_INT_TMR12_NON_CAPT_MODE);
    /*�ر����ж�ʱ���ж�*/
	IntEventClear(SYS_INT_T64P2_TINTALL);
    /*�����ʱ��2�ж�״̬*/
	TimerIntStatusClear(SOC_TMR_2_REGS, TMR_INT_TMR12_NON_CAPT_MODE);

	/*�ڴ˴���Ӵ���*/
	static unsigned int timer_count_5ms=0;
	static unsigned int timer_count_10ms=0;
	static unsigned int timer_count_20ms=0;
	static unsigned int timer_count_50ms=0;
	static unsigned int timer_count_500ms=0;
	static unsigned int timer_count_15s=0;
	timer_count_5ms++;
	timer_count_10ms++;
	timer_count_20ms++;
	timer_count_50ms++;
	timer_count_500ms++;
	timer_count_15s++;
	if(timer_count_5ms%5==0)    //5ms   200Hz
	{
		timer_count_5ms=0;
		//HDLC_Parse();             //ͨ�Ž���

	}
	if(timer_count_10ms%10==0)   //10ms  100Hz
		{
		timer_count_10ms=0;
		AD_Read_Flag=1;           //��ȡAD
		}
	if(timer_count_20ms%10==0)   //20ms  50Hz
	    {
			timer_count_20ms=0;
			//VM_IM_CtrlOutPut();  //�������
	    }
	if(timer_count_50ms%1000==0)  //1Hz
		{
		timer_count_50ms=0;
		Data_Exchange_Flag=1;       //���ݴ���

		}
	if(timer_count_500ms%3000==0)//500ms   2Hz
	    {
		//timer_count_500ms=0;
		timer_test_flag ^= 1;
		//LED_CONFIG = timer_test_flag;             //����
	    }
	if(timer_count_15s%15000==0)
	{
		//InitEnd_Flag=1;
	}

	/*ʹ��TMIER12�ж�Ϊ��ͨģʽ*/
	TimerIntEnable(SOC_TMR_2_REGS, TMR_INT_TMR12_NON_CAPT_MODE);
}
/*****************************END OF FILE************************************/
