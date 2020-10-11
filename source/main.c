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
#include "interface_da.h"
#include "Init.h"

#include "mnic_nor.h"
#include "spi.h"



#include "stdio.h"



#include "mnic_i2c.h"
#include "mnic_interrupt.h"
#include "gpio.h"


#include "comm_factory.h"
#include <protocol_analyze.h>

#include "math.h"
#include "mini_spi.h"
#include "mnic_i2c.h"
#include "Init.h"
long long pid_a=0,pid_b=0;
unsigned int count,flag;


double datav_to_da = 0;
//unsigned int AD_2500_1;





//long long ADS_test[10000];
//int AD_test1[5000];
//int AD_test2[5000];
//int AD_test3[5000];
//int AD_test4[5000];
//int AD_test5[5000];
//int AD_test6[5000];
//int AD_pid[16000];
//int AD_chn[5000];
//int AD_1281[5000];

//long long AD_total[5000];
//double AD_2500_SEL[5000];
//int  da_test[500];
//double AD_OUT[5000];
//double AD_iir_SEL[5000];
double test_valuei=0;
double test_valuev=0;
double Rx=0;
double set_i=0;
long long set_num;
long long set_num1;
long long set_num2;
long long set_num3;
long long set_num4;


double q;
double r;
long long q_d;
long long r_d;

//double mea_data_2500；
//double v_mea_data_2500;

long long AD_kal_1;
long long AD_kal_2;
long long AD_kal_3;
long long AD_kal_4;

int DA_DATA=0;
float wwwi;
float datai_to_da = 0;
#define PI 3.1415926

unsigned int wave_cnt=0;

int bias;
float DA_SET;


int ad_pid;



float ad_mea;


unsigned int DAI_CONV = 0;




/*
 * 函数名：	  void Delay()
 * 函数功能：  延时
 */
 void Delay1()
{
	unsigned int delayTime;
	for(delayTime = 0; delayTime < 7000000; delayTime++);
	delayTime=0;
}
 void Delay2()
{
	unsigned int delayTime;
	for(delayTime = 0; delayTime < 1000; delayTime++);
}


/*
 * 函数名：	 void IntInit(void)
 * 函数功能：  将中断初始化函数汇总到一个函数中
 * 函数入口：
 * 函数出口：
 */
void IntInit(void)
{
	/*中断初始化*/
	IntDSPINTCInit();
	TimerIntInit();
	GPIOIntInit();
	SPIIntInit();
	IntGlobalEnable();
}

//设置输出波形； 测试用
void SetOutWave()
{
//设置输出正弦波
	//正弦波输出
    unsigned int i=0;
    float m_frequncy=1,m_amplitude=1;
    double m_double=0.0002;
    double m_Q=0,m_R=1;
    unsigned int int_frequncy=0;
    unsigned char *p_float =( unsigned char *)&m_frequncy;
    float m_amplitude_tag=-50;
   // CHANNEL_SEL = 0x400;
//        p_float=( unsigned char *)&m_Q;
//        QDATA_HH = *(unsigned short *)&p_float[6];
//        QDATA_HL = *(unsigned short *)&p_float[4];
//        QDATA_LH = *(unsigned short *)&p_float[2];
//        QDATA_LL = *(unsigned short *)&p_float[0];
//
//        p_float=( unsigned char *)&m_R;
//        RMDATA_HH = *(unsigned short *)&p_float[6];
//        RMDATA_HL = *(unsigned short *)&p_float[4];
//        RMDATA_LH = *(unsigned short *)&p_float[2];
//        RMDATA_LL = *(unsigned short *)&p_float[0];
//
//        p_float=( unsigned char *)&m_double;
//        SIN_AMP_HH = *(unsigned short *)&p_float[6];
//        SIN_AMP_HL = *(unsigned short *)&p_float[4];
//        SIN_AMP_LH = *(unsigned short *)&p_float[2];
//        SIN_AMP_LL = *(unsigned short *)&p_float[0];
//		SIN_AMP_HH=0x3f84;  //0.01  3f847ae147ae147b
//		SIN_AMP_HL=0x7ae1;
//		SIN_AMP_LH=0x47ae;
//		SIN_AMP_LL=0x147b;

//	 	SIN_AMP_HH=0x3fb9;//0.1
//	 	SIN_AMP_HL=0x9999;
//	 	SIN_AMP_LH=0x9999;
//	 	SIN_AMP_LL=0x999a;

//	 	SIN_AMP_HH=0x3ff0;  //1
//	 	SIN_AMP_HL=0x0000;
//	 	SIN_AMP_LH=0x0000;
//	 	SIN_AMP_LL=0x0000;

	// 	SIN_AMP_HH=0x4004;  //2.5
	// 	SIN_AMP_HL=0x0000;
	// 	SIN_AMP_LH=0x0000;
	// 	SIN_AMP_LL=0x0000;

	// 	SIN_AMP_HH=0x4008;  //3
	// 	SIN_AMP_HL=0x0000;
	// 	SIN_AMP_LH=0x0000;
	// 	SIN_AMP_LL=0x0000;

//		SIN_FRQ_H=0x0014;//200HZ:666666 160HZ:51eb85 120HZ:3d70a4 80HZ:28f5c3 40HZ:147ae1
//		SIN_FRQ_L=0x7ae1;
//		WAVE_SEL=0x8;//正弦波
//	 	DA_VI_SEL=0x0;//电压1 电流0
//	 	DA_CONFIG_SEL=0X1;
//	 	Delay1();

	// //常值输出
		 WAVE_SEL=0x1;
		 DA_VI_SEL=0x0;//电压1 电流0
		 DA_CONFIG_SEL=0x1;//开环输出：0  闭环：1
		 Delay1();
		 SET_POINT_HH= 0x0000 ; //0
		 SET_POINT_HL= 0x0000 ;
		 SET_POINT_LH= 0x0000 ;
		 SET_POINT_LL= 0x0000 ;
		 Delay1();
//		 SET_POINT_HH= 0xbf40 ; //-0.0005 bf40624dd2f1a9fc
//		 SET_POINT_HL= 0x624d ;
//		 SET_POINT_LH= 0xd2f1 ;
//		 SET_POINT_LL= 0xa9fc ;
//		 Delay1();
//		 SET_POINT_HH= 0xbf60 ; //-0.002 bf60624dd2f1a9fc
//		 SET_POINT_HL= 0x624d ;
//		 SET_POINT_LH= 0xd2f1 ;
//		 SET_POINT_LL= 0xa9fc ;
//		 Delay1();
//		 SET_POINT_HH= 0xbf84 ; //-0.01 bf847ae147ae147b
//		 SET_POINT_HL= 0x7ae1 ;
//		 SET_POINT_LH= 0x47ae ;
//		 SET_POINT_LL= 0x147b ;
//		 Delay1();
//		 SET_POINT_HH= 0xbfa9 ; //-0.05 bfa999999999999a
//		 SET_POINT_HL= 0x9999 ;
//		 SET_POINT_LH= 0x9999 ;
//		 SET_POINT_LL= 0x999a ;
//		 Delay1();
//		 SET_POINT_HH= 0xbfa9 ; //-0.05000025 bfa999a1fd1569f5
//		 SET_POINT_HL= 0x99a1 ;
//		 SET_POINT_LH= 0xfd15 ;
//		 SET_POINT_LL= 0x69f5 ;
//		 Delay1();
//	 	 SET_POINT_HH= 0xbfb9 ; //-0.1 bfb999999999999a
//	 	 SET_POINT_HL= 0x9999 ;
//	 	 SET_POINT_LH= 0x9999 ;
//	 	 SET_POINT_LL= 0x999A ;
//	 	 Delay1();
//		 SET_POINT_HH= 0xbff0 ; //-1 bff0000000000000
//		 SET_POINT_HL= 0x0000 ;
//		 SET_POINT_LH= 0x0000 ;
//		 SET_POINT_LL= 0x0000 ;
//		 Delay1();
//		 SET_POINT_HH= 0xc004 ;//-2.5 c004000000000000
//		 SET_POINT_HL= 0x0000 ;
//		 SET_POINT_LH= 0x0000 ;
//		 SET_POINT_LL= 0x0000 ;
//		 Delay1();
//		 SET_POINT_HH= 0x3ff0 ; //1
//		 SET_POINT_HL= 0x0000 ;
//		 SET_POINT_LH= 0x0000 ;
//		 SET_POINT_LL= 0x0000 ;
//		// DA_CONFIG_SEL=0x1;//开环输出：0  闭环：1
//		 Delay1();
//		 SET_POINT_HH= 0x4000 ; //2
//		 SET_POINT_HL= 0x0000 ;
//		 SET_POINT_LH= 0x0000 ;
//		 SET_POINT_LL= 0x0000 ;
//		 Delay1();
//		 SET_POINT_HH= 0x4012 ; //4.5
//		 SET_POINT_HL= 0x0000 ;
//		 SET_POINT_LH= 0x0000 ;
//		 SET_POINT_LL= 0x0000 ;
//		 Delay1();
//	        int_frequncy =128000/m_frequncy/0.5;
//	        m_double = fabs(m_amplitude*m_amplitude_tag/1000);//电压模式下：value = 目标电压（V）；电流模式下value = -50 * 目标电流（A）
//	        p_float=( unsigned char *)&int_frequncy;
//	        SQUARE_HIGH_DUTY=(unsigned short )int_frequncy;
//	        SQUARE_LOW_DUTY=(unsigned short )int_frequncy;
//
//	        p_float=( unsigned char *)&m_double;
//	        SQUARE_HIGH_AMP_HH=*(unsigned short *)&p_float[6];
//	        SQUARE_HIGH_AMP_HL=*(unsigned short *)&p_float[4];
//	        SQUARE_HIGH_AMP_LH=*(unsigned short *)&p_float[2];
//	        SQUARE_HIGH_AMP_LL=*(unsigned short *)&p_float[0];
//	        m_double=-m_double;
//	        SQUARE_LOW_AMP_HH=*(unsigned short *)&p_float[6];
//	        SQUARE_LOW_AMP_HL=*(unsigned short *)&p_float[4];
//	        SQUARE_LOW_AMP_LH=*(unsigned short *)&p_float[2];
//	        SQUARE_LOW_AMP_LL=*(unsigned short *)&p_float[0];
//	        DA_CONFIG_SEL=0X0;
//	        WAVE_SEL=2;//zhengxian
//	        DA_CONFIG_SEL=0X1;
//	        Delay1();
//	        CONTROL_BYPASS=0x0;
//        int_frequncy =128000/m_frequncy/0.5;
//        m_double = fabs(m_amplitude*m_amplitude_tag/1000);//电压模式下：value = 目标电压（V）；电流模式下value = -50 * 目标电流（A）
//        p_float=( unsigned char *)&int_frequncy;
//        SQUARE_HIGH_DUTY=(unsigned short )int_frequncy;
//        SQUARE_LOW_DUTY=(unsigned short )int_frequncy;
//
//        p_float=( unsigned char *)&m_double;
//        SQUARE_HIGH_AMP_HH=*(unsigned short *)&p_float[6];
//        SQUARE_HIGH_AMP_HL=*(unsigned short *)&p_float[4];
//        SQUARE_HIGH_AMP_LH=*(unsigned short *)&p_float[2];
//        SQUARE_HIGH_AMP_LL=*(unsigned short *)&p_float[0];
//        m_double=-m_double;
//        SQUARE_LOW_AMP_HH=*(unsigned short *)&p_float[6];
//        SQUARE_LOW_AMP_HL=*(unsigned short *)&p_float[4];
//        SQUARE_LOW_AMP_LH=*(unsigned short *)&p_float[2];
//        SQUARE_LOW_AMP_LL=*(unsigned short *)&p_float[0];
//        DA_CONFIG_SEL=0X0;
//        WAVE_SEL=2;//zhengxian
//        DA_CONFIG_SEL=0X1;
//        CONTROL_BYPASS=0x2;
}




/*
 * 函数名：    void Board_Init(void)
 * 函数功能： 系统初始化，包括总线初始化，定时器初始化与时钟同步、复位等操作，EMIF，GPIO，中断，FPGA，传感器初始化
 * 函数入口：  无
 * 函数出口： 无
 */
void Board_Init(void)
{
	/*设置主频时钟和EMIF时钟*/
		Set_Core_456MHz();
      // Set_Core_300MHz();
		/*设置DDR时钟*/
		//Set_DDRPLL_150MHz();
		/*设置DDR时间*/
		//DDRInit(150);
		/*至少600MCLK延迟*/
		Delay1();

		/*EMIF初始化*/
		EMIFAInit();

	//	/*GPIO初始化*/
		GPIOInit();
	   //SPIInit();
	//	/*TIMER初始化*/
		TimerInit();
    //i2c9038初始化
		i2c_init();
	//	/*中断初始化*/
		IntInit();
		/*fpga初始化*/
		fpga_init();
		/*传感器初始化*/
//		SensorInit();
		Delay1();
//		SWITCH28V_Output(0xff);
//		SWITCH5V_Output(0x0f);

		/*HDLC初始化*/

//		 DSJ_initA();
//		 DSJ_initB();

}




int i;
#define MODLE_NUM 4
Base_Core* model_list[MODLE_NUM];
int work_status = 0;
protocol_analyze_interface* p_protocol_analyze;
int main(void){
	Board_Init();  //初始化
	/*在这里添加主程序*/
	 EMIF(INT_EN)=0X0000;   //初始化配置时先关闭中断使能        1:int0 2:int1 4:int2  8:int3 10:int4
//初始化配置器件寄存器
//2500初始化配置寄存器
	AD2500_init();
//1281初始化配置寄存器
	AD1281_init();
//DA校准以及AD校准
 	Flash_data_init();
//配置FPGA寄存器
//ad检测配置校准器
	ADPara_init();
//da检测配置校准器
	DAPara_init();
//相位补偿校正
	channaldelay_init();
//数据融合配置权重
	FUSION_init();
//PID配置
	PID_init();

	Calib_Para_init();
	Kalmen_init();
//测试用，控制内部模块跳过
	sys_int();//1跳过kalman   2：跳过pid  4:跳过iir 8:跳过final iir 10：跳过1281平均 0xD:只有PID
//以上初始化配置完毕


//设置输出波形（正弦波或直流输出）测试用
	SetOutWave();



	asm("   NOP");
	 EMIF(INT_CLEAR)=0xFF;//清中断  先开中断再清中断目的是：AD中断会一直持续使能，只有清中断后下一个中断使能上升沿到来才能进中断。
    //开中断
	 EMIF(INT_EN)=0X0018;   //开中断使能        1:int0 2:int1 4:int2  8:int3 10:int4
//while(1) {}
////
//	}//JUST FOR TEST



//接口管道协议，将一个接口分成多功能复用：uart，hdlc，数据上下传；   详细在ydk说明文档
	 Core_Factory* core_factory = new_core_factory();
	 p_protocol_analyze = new_protocol_analyze_interface();
	 model_list[0]      = core_factory->create_new_core(CORE_HDLC);
	 model_list[1]      = core_factory->create_new_core(CORE_UART);
	 model_list[2]      = core_factory->create_new_core(CORE_AD);
	 model_list[3]      = core_factory->create_new_core(CORE_DA);

	 p_protocol_analyze->hdlc_input_fifo = model_list[0]->up_in_data_list;
	 p_protocol_analyze->hdlc_output_fifo = model_list[0]->up_out_data_list;

	 p_protocol_analyze->uart_input_fifo = model_list[1]->up_in_data_list;
	 p_protocol_analyze->uart_output_fifo = model_list[1]->up_out_data_list;

	 p_protocol_analyze->ad_input_fifo =model_list[2]->up_in_data_list;

	 p_protocol_analyze->da_output_fifo =model_list[3]->up_out_data_list;



	while(1)   //按照前面协议指定工作模式循环扫描工作
	{
        if(MODLE_NUM <= work_status)  //work_status 4次一循环
        {
            work_status =0;
        }
	    model_list[work_status]->process(model_list[work_status]);
	    work_status++;
	    p_protocol_analyze->analyze(p_protocol_analyze);
	}
}
/*****************************END OF FILE************************************/
