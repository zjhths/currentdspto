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

struct _pid pid_str;				//,*pid;	�ñ�ǩ������һ���ṹ��pid_str
//float process_point;				//��ǰ����ֵ��Ҫ��AD�������������
//float set_point;					//���õ㣬������Ҫ��������ֵ

/*****************************************************************************
д��pid��������Ҫ�����ݣ������趨ֵ����ǰֵ��PID����������ۻ�ֵ����һ�����ֵ
******************************************************************************/
void pid_init(struct _pid *pid,double process_p,double set_p,double p_gain,double i_gain,double d_gain)
{
	pid = &pid_str;					//pid��ָ��pid��ָ�룬struct _pid *pid����
	pid->pv = process_p;
	pid->sp = set_p;				//��ǰ��ֵe(t)=(pid->sp��-��pid->pv��
	pid->pgain = p_gain;
	pid->igain = i_gain;
	pid->dgain = d_gain;
	pid->integral = 0;				//�ۼƲ�ֵ
	pid->last_error = 0;			//�ϴβ�ֵe(t-1)

}
/*****************************************************************************
PID���㣬���ݸ����Ľṹ�壬��������Ľ��
******************************************************************************/
double pid_calc(struct _pid *pid)
{
	double err,result,err1000;
	double pterm,iterm,dterm;
	double i_cof;

	err = (pid->sp)-(pid->pv);						//��ǰ��ֵe(t)

	err1000 = err*1000; //�����Ŵ�1000�������
	err1000=(pid->sp)-(pid->pv);
	//���ַ���
    if(err1000<5  && err1000>-5)//����ڡ�5uA����
        i_cof = 1.2;
    else if((err1000<20 &&err1000 >5) ||(err1000 > -20 && err1000<-5))//����ڡ�5uA����20uA֮��
        i_cof = (25-abs(err1000))/20;
    else
        i_cof = 0 ;

    if(pid->igain == 0)                             //i����Ϊ0ʱ�����ۼ�
        pid->integral = 0;
    else
        pid->integral += err*i_cof;                     //I  �ϴ��ۼƲ�ֵ���ϵ�ǰ��ֵ

	pterm = err*(pid->pgain);						//P		Kp*e(t)
	iterm = (pid->igain)*(pid->integral);			//Ki*Ee(t)	E��ʾ�ۼӣ��Ǹ����Ŵ򲻳���
	dterm = (pid->dgain)*(err-(pid->last_error));   //D		Kd*e[(t)-e(t-1)]

	result = pterm+iterm+dterm;//pid���ƽ��
	pid->last_error = err;//�洢��һ�����ֵ

	if(result>0.15)//pid��������Ӧ�ڡ�1.5mA֮��
	{
		result=0.15;
	}
	else if(result<-0.15)
	{
		result=-0.15;
	}
	return(result);
}

