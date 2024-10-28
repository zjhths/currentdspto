/*
 * mnic_timer.c
 * 模块功能：定时器模块对定时器定时时间，定时器中断进行了配置
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
 * 函数名：	 void TimerSetUp64Bit(void)
 * 函数功能：  配置定时器模式及定时时间
 * 函数入口：
 * 函数出口：
 */
void TimerInit(void)
{
	/*将定时器2配置成64位通用定时器模式，使用内部时钟源默认为CPU_CLK/2*/
	TimerConfigure(SOC_TMR_2_REGS, TMR_CFG_64BIT_CLK_INT);

	/*将mnic_timer.h定义的值赋给TIMER12和TIMER34,设置64位定时器定时时间为228000*2/456/1000000=1ms */
	TimerPeriodSet(SOC_TMR_2_REGS, TMR_TIMER12, TMR_PERIOD_LSB32);
	TimerPeriodSet(SOC_TMR_2_REGS, TMR_TIMER34, TMR_PERIOD_MSB32);

	/*定时器持续计数*/
	
	TimerEnable(SOC_TMR_2_REGS, TMR_TIMER12, TMR_ENABLE_CONT);
}

/*
 * 函数名：	 void TimerIntInit(void)
 * 函数功能：  定时器中断初始化
 * 函数入口：
 * 函数出口：
 */
void TimerIntInit(void)
{
	/*使能TMIER12中断为普通模式*/
	TimerIntEnable(SOC_TMR_2_REGS, TMR_INT_TMR12_NON_CAPT_MODE);

	/*将中断向量表中的INT6注册为定时器中断服务程序TimerIsr*/
    IntRegister(C674X_MASK_INT6, TimerIsr);

    /*映射中断到 DSP可屏蔽中断INT6*/
    IntEventMap(C674X_MASK_INT6, SYS_INT_T64P2_TINTALL);

    /*使能DSP可屏蔽中断INT6*/
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
 * 函数名：	 static void TimerIsr()
 * 函数功能：  定时器中断服务程序
 * 函数入口：
 * 函数出口：
 */
static void TimerIsr()
{
	/*关闭定时器2中断*/
	TimerIntDisable(SOC_TMR_2_REGS, TMR_INT_TMR12_NON_CAPT_MODE);
    /*关闭所有定时器中断*/
	IntEventClear(SYS_INT_T64P2_TINTALL);
    /*清除定时器2中断状态*/
	TimerIntStatusClear(SOC_TMR_2_REGS, TMR_INT_TMR12_NON_CAPT_MODE);

	/*在此处添加代码*/
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
		//HDLC_Parse();             //通信解析

	}
	if(timer_count_10ms%10==0)   //10ms  100Hz
		{
		timer_count_10ms=0;
		AD_Read_Flag=1;           //读取AD
		}
	if(timer_count_20ms%10==0)   //20ms  50Hz
	    {
			timer_count_20ms=0;
			//VM_IM_CtrlOutPut();  //波形输出
	    }
	if(timer_count_50ms%1000==0)  //1Hz
		{
		timer_count_50ms=0;
		Data_Exchange_Flag=1;       //数据传输

		}
	if(timer_count_500ms%3000==0)//500ms   2Hz
	    {
		//timer_count_500ms=0;
		timer_test_flag ^= 1;
		//LED_CONFIG = timer_test_flag;             //闪灯
	    }
	if(timer_count_15s%15000==0)
	{
		//InitEnd_Flag=1;
	}

	/*使能TMIER12中断为普通模式*/
	TimerIntEnable(SOC_TMR_2_REGS, TMR_INT_TMR12_NON_CAPT_MODE);
}
/*****************************END OF FILE************************************/
