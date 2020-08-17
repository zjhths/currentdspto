#include "pll.h"
#include "psc.h"
#include "ddr.h"
#include "timer.h"
#include "hw_syscfg0_C6748.h"
#include "interrupt.h"
#include "soc_C6748.h"
#include "mnic_C6748.h"
#include "mnic_timer.h"
#include "mnic_gpio.h"
#include "mnic_emif.h"
#include "mnic_test.h"
#include "hw_types.h"
#include "fpga.h"
#include "Init.h"
#include "rs232_rs422.h"
#include "mnic_nor.h"
#include "spi.h"
#include "mini_spi.h"
#include "AD.h"
#include "Data_Exchange.h"
#include "Nav.h"
#include "stdio.h"
#include "MBox.h"
#include "HDLC.h"
#include "pid_func.h"
#include "gpio.h"

struct _pid pid_str;				//,*pid;	用标签来声明一个结构体pid_str
//float process_point;				//当前测量值，要把AD测量结果赋给它
//float set_point;					//设置点，根据所要求的输出赋值

/*****************************************************************************
写入pid控制所需要的数据，包括设定值，当前值，PID参数，误差累积值，上一个误差值
******************************************************************************/
void pid_init(struct _pid *pid,double process_p,double set_p,double p_gain,double i_gain,double d_gain)
{
	pid = &pid_str;					//pid是指向pid的指针，struct _pid *pid生成
	pid->pv = process_p;
	pid->sp = set_p;				//当前差值e(t)=(pid->sp）-（pid->pv）
	pid->pgain = p_gain;
	pid->igain = i_gain;
	pid->dgain = d_gain;
	pid->integral = 0;				//累计差值
	pid->last_error = 0;			//上次差值e(t-1)

}
/*****************************************************************************
PID计算，根据给定的结构体，计算出最后的结果
******************************************************************************/
double pid_calc(struct _pid *pid)
{
	double err,result,err1000;
	double pterm,iterm,dterm;
	double i_cof;

	err = (pid->sp)-(pid->pv);						//当前差值e(t)

	err1000 = err*1000; //将误差放大1000倍后计算
	err1000=(pid->sp)-(pid->pv);
	//积分分离
    if(err1000<5  && err1000>-5)//误差在±5uA以内
        i_cof = 1.2;
    else if((err1000<20 &&err1000 >5) ||(err1000 > -20 && err1000<-5))//误差在±5uA到±20uA之间
        i_cof = (25-abs(err1000))/20;
    else
        i_cof = 0 ;

    if(pid->igain == 0)                             //i参数为0时，误差不累计
        pid->integral = 0;
    else
        pid->integral += err*i_cof;                     //I  上次累计差值加上当前差值

	pterm = err*(pid->pgain);						//P		Kp*e(t)
	iterm = (pid->igain)*(pid->integral);			//Ki*Ee(t)	E表示累加，那个符号打不出来
	dterm = (pid->dgain)*(err-(pid->last_error));   //D		Kd*e[(t)-e(t-1)]

	result = pterm+iterm+dterm;//pid控制结果
	pid->last_error = err;//存储上一个误差值

	if(result>0.15)//pid控制增量应在±1.5mA之内
	{
		result=0.15;
	}
	else if(result<-0.15)
	{
		result=-0.15;
	}
	return(result);
}

