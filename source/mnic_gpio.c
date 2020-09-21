/*
 * mnic_gpio.c
 * 模块功能：GPIO模块对引脚复用功能和中断进行了配置
 *  Created on: 2015-12-7
 *      Author: SUN
 */

#include "gpio.h"
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
#include "mnic_i2c.h"
#include "mnic_interrupt.h"

#include "func.h"
#include "interface_ad.h"
#include "interface_hdlc.h"
extern Ad_interface* m_ad_interface;
double  ad_sorce_double;
float ad_sorce_float;
unsigned int test_count=0;

extern Hdlc_interface* my_hdlc;

extern int AD_MEASUER;
//extern long long ADS_test[10000];
extern unsigned int V_data;
//double datai_to_da;
struct _pid *pp;
extern double datai_to_da_pid,datav_to_da_pid;
extern double v_mea_data_mix;
extern double v_mea_data_2500;
extern unsigned int DAV_CONV;
//extern int AD_test1[5000];
//extern int AD_test2[5000];
//extern int AD_test3[5000];
//extern int AD_test4[5000];
//extern int AD_test5[5000];
//extern int AD_test6[5000];
extern int AD_MEASUER;
extern int AD_MEASUER2;
extern int AD_MEASUER3;
extern int AD_MEASUER4;
extern int AD_MEASUER5;


extern long long AD_2500_4;


//extern int AD_pid[16000];
//extern double AD_OUT[5000];
//extern double AD_iir_SEL[5000];
//extern double AD_2500_SEL[5000];
extern void i2c_init();
extern void GPIOInit();
extern void IntInit();
extern void Delay1();






int updata_cnt=0;

int cnt=0;
unsigned short channal_zero[2]={1,32};//1:CH1 2:CH2 4:CH3 8:CH4 10:CH5 20:CH1281
/****************************************************************************/
/*              LOCAL FUNCTION PROTOTYPES                                   */
/****************************************************************************/
//复位中断信号、mailbox中断信号、处理器单元485通讯中断信号
static void GPIOPinMuxSetup();
static void GPIOIsr0(void);     //INT0~INT5
static void GPIOIsr1(void);
static void GPIOIsr2(void);
static void GPIOIsr3(void);
static void GPIOIsr4(void);
static void GPIOIsr5(void);
void PhaseTest(void);
void ZeroAndFusionTest(void);
void NoiseTest(void);
//INT0~INT4 管脚GPIO:
//INT0:GPIO0[15]
//INT1:GPIO7[11]
//INT2:GPIO1[14]
//INT3:GPIO6[0]
//INT4:GPIO2[15]
//BY WQ


/*
 * 函数名：	 void GPIOInit(void)
 * 函数功能：  GPIO模块初始化
 * 函数入口：
 * 函数出口：
 */
void GPIOInit(void)
{
	/*PSC模块配置：将PSC1中的GPIO0模块配置成PD0(ALWAYS ON)状态，下一状态为ENABLE*/
	PSCModuleControl(SOC_PSC_1_REGS, HW_PSC_GPIO, PSC_POWERDOMAIN_ALWAYS_ON,
								     PSC_MDCTL_NEXT_ENABLE);
	/*GPIO引脚复用功能函数*/
	GPIOPinMuxSetup();
}

/*
 * 函数名：	 void GPIOIntInit(void)
 * 函数功能： 配置中断管理器接受GPIO中断
 */
void GPIOIntInit(void)
{

	INT_CLEAR=0xFF;

////	//INT0	  /*配置GPIO0  pin (GPIO0[15])为输入*/
    GPIODirModeSet(SOC_GPIO_0_REGS, 16, GPIO_DIR_INPUT);
//    /*配置GPIO pin (GPIO0[15])为上升沿触发中断*/
    GPIOIntTypeSet(SOC_GPIO_0_REGS, 16, GPIO_INT_TYPE_RISEDGE);
//    /*使能GPIO Bank0中断*/
    GPIOBankIntEnable(SOC_GPIO_0_REGS, 0);
//	/*将中断向量表的INT0注册为GPIO中断服务程序*/
	IntRegister(C674X_MASK_INT11, GPIOIsr0);
//	/*映射中断到 DSP可屏蔽中断*/
	IntEventMap(C674X_MASK_INT11, SYS_INT_GPIO_B0INT);
//	/*使能DSP可屏蔽中断INT5*/
	IntEnable(C674X_MASK_INT11);
////
////	//INT1	   /*配置GPIO pin (INT1:GPIO7[11])为输入*/
	    GPIODirModeSet(SOC_GPIO_0_REGS, 124, GPIO_DIR_INPUT);
	    /*配置GPIO pin (GPIO7[11])为上升沿触发中断*/
	    GPIOIntTypeSet(SOC_GPIO_0_REGS, 124, GPIO_INT_TYPE_RISEDGE);
	    /*使能GPIO Bank7中断*/
	    GPIOBankIntEnable(SOC_GPIO_0_REGS, 7);
		/*将中断向量表的INT8注册为GPIO中断服务程序*/
		IntRegister(C674X_MASK_INT8, GPIOIsr1);
		/*映射中断到 DSP可屏蔽中断*/
		IntEventMap(C674X_MASK_INT8, SYS_INT_GPIO_B7INT);
		/*使能DSP可屏蔽中断INT8*/
		IntEnable(C674X_MASK_INT8);
////
//	//INT2	        /*配置GPIO pin (GPIO1[14])为输入*/    VM_spi_int and IM_spi_int
//		        GPIODirModeSet(SOC_GPIO_0_REGS, 31, GPIO_DIR_INPUT);
//			    /*配置GPIO pin 1(GPIO1[14])为上升沿触发中断*/
//			    GPIOIntTypeSet(SOC_GPIO_0_REGS, 31, GPIO_INT_TYPE_RISEDGE);
//			    /*使能GPIO Bank1中断*/
//			    GPIOBankIntEnable(SOC_GPIO_0_REGS, 1);
//				/*将中断向量表的INT6注册为GPIO中断服务程序*/
//				IntRegister(C674X_MASK_INT7, GPIOIsr2);
//				/*映射中断到 DSP可屏蔽中断*/
//				IntEventMap(C674X_MASK_INT7, SYS_INT_GPIO_B1INT);
				/*使能DSP可屏蔽中断INT7*/
				//IntEnable(C674X_MASK_INT7);
//
////	INT3			 /*配置GPIO为输入*/          //AD中断 97  GP6[0]
				GPIODirModeSet(SOC_GPIO_0_REGS, 97, GPIO_DIR_INPUT);  //  GP6[0]
					/*配置GPIO   GP6[0]为上升沿触发中断*/
				GPIOIntTypeSet(SOC_GPIO_0_REGS, 97, GPIO_INT_TYPE_RISEDGE);//  GP6[0]
				/*使能GPIO Bank6中断*/
				GPIOBankIntEnable(SOC_GPIO_0_REGS, 6);
				/*将中断向量表的INT10注册为GPIO中断服务程序*/
				IntRegister(C674X_MASK_INT10, GPIOIsr3);
				/*映射中断到 DSP可屏蔽中断*/
				IntEventMap(C674X_MASK_INT10, SYS_INT_GPIO_B6INT);
			    /*使能DSP可屏蔽中断INT10*/
				IntEnable(C674X_MASK_INT10);
////
////	//INT4			 /*配置GPIO pin (GPIO2[15])为输入*/     //HDLC & USART
			GPIODirModeSet(SOC_GPIO_0_REGS, 48, GPIO_DIR_INPUT);
				/*配置GPIO pin (GPIO2[15])为上升沿触发中断*/
			GPIOIntTypeSet(SOC_GPIO_0_REGS, 48, GPIO_INT_TYPE_RISEDGE);
				/*使能GPIO Bank2中断*/
			GPIOBankIntEnable(SOC_GPIO_0_REGS, 2);
			/*将中断向量表的INT5注册为GPIO中断服务程序*/
			IntRegister(C674X_MASK_INT9, GPIOIsr4);
				/*映射中断到 DSP可屏蔽中断*/
			IntEventMap(C674X_MASK_INT9, SYS_INT_GPIO_B2INT);
				 /*使能DSP可屏蔽中断INT5*/
			IntEnable(C674X_MASK_INT9);



}

/*
 * 函数名：	 static void GPIOIsr(void)   HDLC中断接收函数
 * 函数功能： 中断服务程序执行GPIO中断。关闭GPIO中断 ，清除系统中断和引脚中断状态，并将FLAG设置为1  GPIO0[15]
 * mailbox中断信号
 */
static void GPIOIsr0(void)
{

	/*关闭GPIO bank0引脚中断*/
    GPIOBankIntDisable(SOC_GPIO_0_REGS, 0);
    INT_EN=0x00;
    // Add your interrupt service code here.

////        get_init_count++;
////    	mailbox_rx_buff[0]=rd_data_rx;
////    	mailbox_rx_buff[1]=rd_data_rx;
////    	mailbox_rx_buff[2]=rd_data_rx;
////    	rd_rst=1;
////    	asm("	NOP");
////    	rd_rst  = 0;
////    	mailbox_clr_int=1;
//        unsigned short int temp=UART_INT_Ctrl;//应为1（中断0）
//        unsigned char num=1;
//        for(;num<7;num++)  //右移6次判断
//        {
//        	if(temp&0x0001==0x0001)
//        	{
//        		 RX_Ctrl=0x01<<(num-1);
//        		 COM_Recv(num,rx_Data_RS485_0);
//        		 UART_INT_Ctrl|=0x0001<<(num-1);//清中断
//        	}
//        	temp=temp>>1;
//        }



    /*在DSPINTC中清除系统中断*/
    IntEventClear(SYS_INT_GPIO_B0INT);
    /*清除GPIO0[15]中断状态*/
    GPIOPinIntClear(SOC_GPIO_0_REGS, 16);
    /*使能GPIO bank0中断*/
    GPIOBankIntEnable(SOC_GPIO_0_REGS, 0);
    INT_EN=0xffff;
    INT_CLEAR=0xffff;
}
/*
 * 函数名：	 static void GPIOIsr1(void)
 * 函数功能： 中断服务程序执行GPIO中断。GPIO0[14]
 * UART 中断!
 */
static void GPIOIsr1(void)
{
   	  /*关闭GPIO bank0引脚中断*/
    GPIOBankIntDisable(SOC_GPIO_0_REGS, 7);
    // Add your interrupt service c-ode here.


    /*在DSPINTC中清除系统中断*/
    IntEventClear(SYS_INT_GPIO_B7INT);
    /*清除GPIO1[13]中断状态*/// 0*16+14+1=15
    GPIOPinIntClear(SOC_GPIO_0_REGS,124);
    /*使能GPIO bank0中断*/
    GPIOBankIntEnable(SOC_GPIO_0_REGS, 7);


}
/*
 * 函数名：	 static void GPIOIsr2(void)
 * 函数功能： 中断服务程序执行GPIO中断。GPIO1[14]
 */
		union
		{
			unsigned char d2ftemp[4];
			float d2fvalue;
		}d2ftype;

		union
		{
			unsigned char amptemp[8];
			double ampvalue;
		}amptype;
static void GPIOIsr2(void)
{


//	unsigned int k;
//
//
//
//
//	/*关闭GPIO bank1引脚中断*/
    GPIOBankIntDisable(SOC_GPIO_0_REGS, 1);
//    // Add your interrupt service code here.
//    if(GPIOPinIntStatus(SOC_GPIO_0_REGS,31)==GPIO_INT_PEND)
//    {
//    	INT_CLEAR=0xFF;
//    	/*清除GPIO1[14]中断状态*/// 1*16+14+1=31

//
//
//    		 up_data.uni_char[7] =AD_OUT_DATA_HH>>8;
//    		 up_data.uni_char[6] =AD_OUT_DATA_HH&0xFF;
//    		 up_data.uni_char[5] =AD_OUT_DATA_HL>>8;
//    		 up_data.uni_char[4] =AD_OUT_DATA_HL&0xFF;
//    		 up_data.uni_char[3]=AD_OUT_DATA_LH>>8;
//    		 up_data.uni_char[2]=AD_OUT_DATA_LH&0xFF;
//    		 up_data.uni_char[1]=AD_OUT_DATA_LL>>8;
//    		 up_data.uni_char[0]=AD_OUT_DATA_LL&0xFF;
//
//    		 d2ftype.d2fvalue=(float)up_data.uni_double;



	IntEventClear(SYS_INT_GPIO_B1INT);
	GPIOPinIntClear(SOC_GPIO_0_REGS,31);
    /*使能GPIO bank1中断*/
    GPIOBankIntEnable(SOC_GPIO_0_REGS,1);
    //    	 GPIOPinIntClear(SOC_GPIO_0_REGS,31);
    //    	 /*在DSPINTC中清除系统中断*/
    //
	INT_EN=0xffff;
	INT_CLEAR=0xffff;
}
/*
 * 函数名：	 static void GPIOIsr3(void)
 * 函数功能： 中断服务程序执行GPIO中断。GPIO0[13]
 */
static void GPIOIsr3(void)
{
		int length=1;
		double ad_temp=0;
        unsigned short *ad_data = (unsigned short *)&ad_temp;

		/*关闭GPIO bank8引脚中断*/
	    GPIOBankIntDisable(SOC_GPIO_0_REGS, 6);

	    if (updata_cnt >=16)
	    {
	        ad_temp = 0x0000000000000000;
	        ad_data[3]= EMIF(AD_OUT_DATA(0)) ;
	        ad_data[2]= EMIF(AD_OUT_DATA(1)) ;
  			ad_data[1]= EMIF(AD_OUT_DATA(2)) ;
  			ad_data[0]= EMIF(AD_OUT_DATA(3)) ;

			ad_sorce_double = *(double*)&ad_temp;
			ad_sorce_float= ad_sorce_double/-50*1000;

			if(m_ad_interface != 0)
			    m_ad_interface->recv(m_ad_interface,(unsigned char*)&ad_sorce_float,&length);
			updata_cnt=0;

	    }
	    else
	    {
	        updata_cnt+=1;
	    }
//以下函数定义在本文件最下方，需要用哪个就开哪个
		/*测噪声时用,1s*/
		//NoiseTest();
	    /*测零位和单通道噪声时用,5min*/
	   //ZeroAndFusionTest();
	    /*相位校正时用*/
	   // PhaseTest();


	    /*在DSPINTC中清除系统中断*/
	    IntEventClear(SYS_INT_GPIO_B6INT);
	    /*清除GPIO8[15]中断状态*/// 8*16+15+1=144
	    GPIOPinIntClear(SOC_GPIO_0_REGS,97);
	    /*使能GPIO bank8中断*/
	    GPIOBankIntEnable(SOC_GPIO_0_REGS,6);

		INT_EN=0x0018;
		INT_CLEAR=0xffff;
}

/*
 * 函数名：	 static void GPIOIsr4(void)
 * 函数功能： 中断服务程序执行GPIO中断。GPIO0[12]
 */
static void GPIOIsr4(void)
{
    // Add your interrupt service code here.
     INT_EN=0x18;
    //////////////////////////////////////////////////
    //HDLC接收数据
     unsigned char temp=0;
      unsigned char hdlc_error;
      unsigned char data_temp[512];
      unsigned int  datalen=0;
      /*关闭GPIO bank0引脚中断*/
      GPIOBankIntDisable(SOC_GPIO_0_REGS, 2);
      HDLC_rx_ctrl_addr &= ~HDLC_Rx_int_enable;//禁止产生接收中断
      temp = HDLC_int_flag_addr;
      if(temp & 0x01 == 0x01)   //判断是否为HDLC中断
      {

    	  hdlc_error=(HDLC_rx_status_addr>>9)&0x07;
    	  if(hdlc_error==0)
    	  {
    		  my_hdlc->recv(my_hdlc,data_temp,&datalen);
    	  }

    	  HDLC_rx_ctrl_addr=0x0;//HDLC复位
    	  asm("   NOP");
    	  HDLC_rx_ctrl_addr=0x7;//第0位为“1”代表复位状态结束，第1位为“1”代表使能帧校验，第2位为“1”代表使能接收中断
    	  asm("   NOP");
    	  HDLC_clr_int_addr=0x1;//清中断
    	  asm("   NOP");
    	  HDLC_clr_int_addr=0x0;//跳出清中断状态
    	  asm("   NOP");

    	  INT_CLEAR=0xFF;
    	  /*使能GPIO bank0中断*/

        }

	  IntEventClear(SYS_INT_GPIO_B2INT);
	  /*清除GPIO0[12]中断状态*/// 0*16+12+1=13
	  GPIOPinIntClear(SOC_GPIO_0_REGS,48);
	  GPIOBankIntEnable(SOC_GPIO_0_REGS, 2);
}

/*
 * 函数名：	 static void GPIOIsr5(void)
 * 函数功能： 中断服务程序执行GPIO中断。GPIO0[3]
 */
static void GPIOIsr5(void)
{

	/*关闭GPIO bank0引脚中断*/
    GPIOBankIntDisable(SOC_GPIO_0_REGS, 0);
    // Add your interrupt service code here.

    /*在DSPINTC中清除系统中断*/
    IntEventClear(SYS_INT_GPIO_B0INT);
    /*清除GPIO0[3]中断状态*/// 0*16+3+1=4
    GPIOPinIntClear(SOC_GPIO_0_REGS,4);
    /*使能GPIO bank0中断*/
    GPIOBankIntEnable(SOC_GPIO_0_REGS, 0);
}



/*
 * 函数名：	 static void GPIOPinMuxSetup()
 * 函数功能：  GPIO0[0]引脚复用配置
 * 函数入口：
 * 函数出口：
 */

//INT0:GPIO0[15]
//INT1:GPIO7[11]
//INT2:GPIO1[14]
//INT3:GPIO6[0]
//INT4:GPIO2[15]


static void GPIOPinMuxSetup()
{
/*宏定义 PINMUX0_GPIO0_0_ENABLE 0x00000008u向左移位0x0000000Cu变成0x00008000u*/
//PINMUX0寄存器GP0[15]   INT0

#define PINMUX0_GPIO0_15_ENABLE    (SYSCFG_PINMUX0_PINMUX0_3_0_GPIO0_15  << \
		SYSCFG_PINMUX0_PINMUX0_3_0_SHIFT)
	unsigned int savePinmux = 0;

	    savePinmux = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(0)) &
	                 ~(SYSCFG_PINMUX0_PINMUX0_3_0));

	    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(0)) =
	         (PINMUX0_GPIO0_15_ENABLE | savePinmux);

	    //PINMUX16寄存器GP7[11]   INT1

#define PINMUX16_GPIO7_11_ENABLE    (SYSCFG_PINMUX16_PINMUX16_27_24_GPIO7_11  << \
		SYSCFG_PINMUX16_PINMUX16_27_24_SHIFT)
		    savePinmux = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(16)) &
	                 ~(SYSCFG_PINMUX16_PINMUX16_27_24));

	    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(0)) =
	         (PINMUX16_GPIO7_11_ENABLE | savePinmux);

	    //PINMUX2寄存器GP1[14]   INT2

#define PINMUX2_GPIO1_14_ENABLE    (SYSCFG_PINMUX2_PINMUX2_7_4_GPIO1_14  << \
		SYSCFG_PINMUX2_PINMUX2_7_4_SHIFT)
		    savePinmux = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(2)) &
	                 ~(SYSCFG_PINMUX2_PINMUX2_7_4));

	    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(2)) =
	         (PINMUX2_GPIO1_14_ENABLE | savePinmux);


	    //PINMUX19寄存器  INT3      //GP6[0]

#define PINMUX19_GPIO6_0_ENABLE    (SYSCFG_PINMUX19_PINMUX19_27_24_GPIO6_0  << \
		SYSCFG_PINMUX19_PINMUX19_27_24_SHIFT)
		    savePinmux = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(19)) &
	                 ~(SYSCFG_PINMUX19_PINMUX19_27_24));
	    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(19)) =
	         (PINMUX19_GPIO6_0_ENABLE | savePinmux);


	    //PINMUX5寄存器GP2[15]   INT4

#define PINMUX5_GPIO2_15_ENABLE    (SYSCFG_PINMUX5_PINMUX5_3_0_GPIO2_15  << \
		SYSCFG_PINMUX5_PINMUX5_3_0_SHIFT)
		    savePinmux = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(5)) &
	                 ~(SYSCFG_PINMUX5_PINMUX5_3_0));
	    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(5)) =
	         (PINMUX5_GPIO2_15_ENABLE | savePinmux);

	    //PINMUX1寄存器   INT5 无
//#define PINMUX1_GPIO0_3_ENABLE    (SYSCFG_PINMUX1_PINMUX1_19_16_GPIO0_3  << \
//		SYSCFG_PINMUX1_PINMUX1_19_16_SHIFT)
//		    savePinmux = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(1)) &
//	                 ~(SYSCFG_PINMUX1_PINMUX1_19_16));
//	    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(1)) =
//	         (PINMUX1_GPIO0_3_ENABLE | savePinmux);
}



//
////内部通信函数
//void InterCommunication1()
//{
//	unsigned int i,j,k;
//	unsigned int freq_temp;
//	unsigned short int amp_temp;
//   // unsigned char hdlc_temp3;
//    //hdlc_temp3=HDLC_rx_data_out_addr & 0xFF;//读取HDLC第三个字节
//    //第三个字节表示了上位机要求电路板的工作模式
//
//	 if(hdlc_temp3 == 0x34)			//要求回传电流数据100个float以及2个byte的温度数据
//		{
//			cur_measure = 1;
//			vol_measure = 0;
//			ch_sel=1;
//
//			trans_data[0] = 0x52;//发送数据的第一个字节为上位机的地址
//			trans_data[1] = Own_Add;//发送数据的第二个字节为当前电路板的地址
//			trans_data[2] =0x34;
//			trans_data[3] =0x01;
//
//
//			trans_data[403] = 0x10;
//			trans_data[404] = 0x10;
//			trans_data[405] = 0xa0;
//			trans_data[406] = 0x41;
////			HDLC_transmit(trans_data,405);
//
//
//
//
//		}
//		else if(hdlc_temp3 == 0x35)			//要求回传电压数据100个float以及2个byte的温度数据
//		{
//			vol_measure = 1;
//			cur_measure = 0;
//
//			trans_data[0] = 0x52;//发送数据的第一个字节为上位机的地址
//			trans_data[1] = Own_Add;//发送数据的第二个字节为当前电路板的地址
//			trans_data[2] =0x35;
//			trans_data[3] =0x01;
//
//
//		}
//
//
//
//
//
//}
//
//
//void InterCommunication2()
//{
//	unsigned int i,j,k;
//	unsigned int freq_temp;
//	unsigned short int amp_temp;
//   // unsigned char hdlc_temp3;
//    //hdlc_temp3=HDLC_rx_data_out_addr & 0xFF;//读取HDLC第三个字节
//    //第三个字节表示了上位机要求电路板的工作模式
//
//
//	 if(hdlc_temp3 == 0x34)			//要求回传电流数据100个float以及2个byte的温度数据
//		{
//			cur_measure = 1;
//			vol_measure = 0;
//			ch_sel=2;
//
//			trans_data[0] = 0x52;//发送数据的第一个字节为上位机的地址
//			trans_data[1] = 0x42;//发送数据的第二个字节为当前电路板的地址
//			trans_data[2] =0x34;
//			trans_data[3] =0x01;
//
//
//			trans_data[403] = 0x10;
//			trans_data[404] = 0x10;
//			trans_data[405] = 0xa0;
//			trans_data[406] = 0x41;
////			HDLC_transmit(trans_data,405);
//
//
//
//
//		}
//		else if(hdlc_temp3 == 0x35)			//要求回传电压数据100个float以及2个byte的温度数据
//		{
//			vol_measure = 1;
//			cur_measure = 0;
//
//			trans_data[0] = 0x52;//发送数据的第一个字节为上位机的地址
//			trans_data[1] = 0x42;//发送数据的第二个字节为当前电路板的地址
//			trans_data[2] =0x35;
//			trans_data[3] =0x01;
//
//		}
//
//
//
//
//
//}
//
//
//void InterCommunication3()
//{
//	unsigned int i,j,k;
//	unsigned int freq_temp;
//	unsigned short int amp_temp;
//   // unsigned char hdlc_temp3;
//    //hdlc_temp3=HDLC_rx_data_out_addr & 0xFF;//读取HDLC第三个字节
//    //第三个字节表示了上位机要求电路板的工作模式
//
//
//	 if(hdlc_temp3 == 0x34)			//要求回传电流数据100个float以及2个byte的温度数据
//		{
//			cur_measure = 1;
//			vol_measure = 0;
//			ch_sel=3;
//
//			trans_data[0] = 0x52;//发送数据的第一个字节为上位机的地址
//			trans_data[1] = 0x43;//发送数据的第二个字节为当前电路板的地址
//			trans_data[2] =0x34;
//			trans_data[3] =0x01;
//
//			trans_data[403] = 0x10;
//			trans_data[404] = 0x10;
//			trans_data[405] = 0xa0;
//			trans_data[406] = 0x41;
////			HDLC_transmit(trans_data,405);
//
//
//
//
//		}
//		else if(hdlc_temp3 == 0x35)			//要求回传电压数据100个float以及2个byte的温度数据
//		{
//			vol_measure = 1;
//			cur_measure = 0;
//
//			trans_data[0] = 0x52;//发送数据的第一个字节为上位机的地址
//			trans_data[1] = 0x43;//发送数据的第二个字节为当前电路板的地址
//			trans_data[2] =0x35;
//			trans_data[3] =0x01;
//
//		}
//
//
//
//
//
//}
//
//void InterCommunication4()
//{
//	unsigned int i,j,k;
//	unsigned int freq_temp;
//	unsigned short int amp_temp;
//   // unsigned char hdlc_temp3;
//    //hdlc_temp3=HDLC_rx_data_out_addr & 0xFF;//读取HDLC第三个字节
//    //第三个字节表示了上位机要求电路板的工作模式
//
//
//	 if(hdlc_temp3 == 0x34)			//要求回传电流数据100个float以及2个byte的温度数据
//		{
//			cur_measure = 1;
//			vol_measure = 0;
//			ch_sel=4;
//
//			trans_data[0] = 0x52;//发送数据的第一个字节为上位机的地址
//			trans_data[1] = 0x44;//发送数据的第二个字节为当前电路板的地址
//			trans_data[2] =0x34;
//			trans_data[3] =0x01;
//
//
//			trans_data[403] = 0x10;
//			trans_data[404] = 0x10;
//			trans_data[405] = 0xa0;
//			trans_data[406] = 0x41;
////			HDLC_transmit(trans_data,405);
//
//
//
//
//		}
//		else if(hdlc_temp3 == 0x35)			//要求回传电压数据100个float以及2个byte的温度数据
//		{
//			vol_measure = 1;
//			cur_measure = 0;
//
//			trans_data[0] = 0x52;//发送数据的第一个字节为上位机的地址
//			trans_data[1] = 0x44;//发送数据的第二个字节为当前电路板的地址
//			trans_data[2] =0x35;
//			trans_data[3] =0x01;
//
//		}
//
//
//
//

//
//}

//void iirTest(void)
//{
//	//测试iir
//	CHANNEL_SEL=0x20;
//	IIR_CH_SEL=0x20;
//	if (k <5000)
//	{
//		AD_2500_1 = 0x0000000000000000;
//		ad_data[3]=IIR_CH_DATA_HH ;
//		ad_data[2]=IIR_CH_DATA_HL  ;
//		ad_data[1]=IIR_CH_DATA_LH;
//		ad_data[0]=IIR_CH_DATA_LL;
//		AD_2500_2 = *(double *)&AD_2500_1;
//		AD_2500_SEL[k] = AD_2500_2;
//
//		AD_MEASUER = CHANNEL_DATA_H;
//		AD_MEASUER = AD_MEASUER<<16;
//		AD_MEASUER|= CHANNEL_DATA_L;
//		AD_test1[k]=AD_MEASUER;
//		AD_MEASUER=0;
//
//		k+=1;
//	}
//	else
//	{
//	k=0;
//
//	}
//}

//void NoiseTest(void)
//{
//	//测试最终1s噪声
//    //测试NOISE
//    unsigned short *ad_data = (unsigned short *)&AD_2500_1;
//	if (k <5000)
//	{
//		AD_2500_1 = 0x0000000000000000;
//		ad_data[3]=AD_OUT_DATA_HH ;
//		ad_data[2]=AD_OUT_DATA_HL  ;
//		ad_data[1]=AD_OUT_DATA_LH;
//		ad_data[0]=AD_OUT_DATA_LL;
//		AD_2500_2 = *(double *)&AD_2500_1;
//		AD_OUT[k] = AD_2500_2/64;
//		AD_2500_2=0;
//
//		          IIR_CH_SEL=channal_zero[1];//1:CH1 2:CH2 4:CH3 8:CH4 10:CH5 20:CH1281
//		          AD_2500_1 = 0x0000000000000000;
//		          ad_data[3]=IIR_CH_DATA_HH ;
//		          ad_data[2]=IIR_CH_DATA_HL  ;
//		          ad_data[1]=IIR_CH_DATA_LH;
//		          ad_data[0]=IIR_CH_DATA_LL;
//		          AD_2500_2 = *(double *)&AD_2500_1;
//		          AD_iir_SEL[k] = AD_2500_2;
//		          AD_2500_2=0;
//		k+=1;
//	}
//	else
//	{
//		channal=FUSION_CH_STATUS;
//		k=0;
//
//	}
//
//}

//
//void PhaseTest(void)
//{
//	/*相位校正时用*/
//	CHANNEL_SEL=0X20;
//	if (k <5000)
//	{
//
//		AD_CHANNAL = CHANNEL_DATA_H;
//		AD_CHANNAL = AD_CHANNAL<<16;
//		AD_CHANNAL|= CHANNEL_DATA_L;
//		AD_test6[k]=AD_CHANNAL;
//		AD_CHANNAL=0;
//
//		AD_MEASUER = AD_2500_1H;
//		AD_MEASUER = AD_MEASUER<<16;
//		AD_MEASUER|= AD_2500_1L;
//		AD_test1[k]=AD_MEASUER;
//		AD_MEASUER=0;
//
//		AD_MEASUER2 = AD_2500_2H;
//		AD_MEASUER2 = AD_MEASUER2<<16;
//		AD_MEASUER2|= AD_2500_2L;
//		AD_test2[k]=AD_MEASUER2;
//		AD_MEASUER2=0;
//
//		AD_MEASUER3 = AD_2500_3H;
//		AD_MEASUER3 = AD_MEASUER3<<16;
//		AD_MEASUER3|= AD_2500_3L;
//		AD_test3[k]=AD_MEASUER3;
//		AD_MEASUER3=0;
//
//		AD_MEASUER4 = AD_2500_4H;
//		AD_MEASUER4 = AD_MEASUER4<<16;
//		AD_MEASUER4|= AD_2500_4L;
//		AD_test4[k]=AD_MEASUER4;
//		AD_MEASUER4=0;
//
//		AD_MEASUER5 = AD_2500_5H;
//		AD_MEASUER5 = AD_MEASUER5<<16;
//		AD_MEASUER5|= AD_2500_5L;
//		AD_test5[k]=AD_MEASUER5;
//		AD_MEASUER5=0;
//
//		k+=1;
//	}
//	else
//	{
//		k=0;
//		AD_MEASUER5=0;
//		AD_MEASUER=0;
//		AD_MEASUER4=0;
//		AD_MEASUER3=0;
//		AD_MEASUER2=0;
//		AD_CHANNAL=0;
//	}
//}
//

//void ZeroAndFusionTest(void)
//{
//	/*测零位和单通道噪声时用*/
//	//5分钟长时间测试
//	unsigned short *ad_data = (unsigned short *)&AD_2500_1;
//	if (cnt>1){
//
//		if (k < 4999)
//		{
//			IIR_CH_SEL=channal_zero[0];//1:CH1 2:CH2 4:CH3 8:CH4 10:CH5 20:CH1281
//			AD_2500_1 = 0x0000000000000000;
//			ad_data[3]=IIR_CH_DATA_HH ;
//			ad_data[2]=IIR_CH_DATA_HL  ;
//			ad_data[1]=IIR_CH_DATA_LH;
//			ad_data[0]=IIR_CH_DATA_LL;
//			AD_2500_2 = *(double *)&AD_2500_1;
//			AD_OUT[k] = AD_2500_2;
//			AD_2500_2=0;
//
//			IIR_CH_SEL=channal_zero[1];//1:CH1 2:CH2 4:CH3 8:CH4 10:CH5 20:CH1281
//			AD_2500_1 = 0x0000000000000000;
//			ad_data[3]=IIR_CH_DATA_HH ;
//			ad_data[2]=IIR_CH_DATA_HL  ;
//			ad_data[1]=IIR_CH_DATA_LH;
//			ad_data[0]=IIR_CH_DATA_LL;
//			AD_2500_2 = *(double *)&AD_2500_1;
//			AD_iir_SEL[k] = AD_2500_2;
//			AD_2500_2=0;
//			k+=1;
//
//		}
//		else
//		{
//		k=0;
//
//		}
//		cnt=0;
//	}
//	else{
//		cnt+=1;
//	}
//}




/*****************************END OF FILE************************************/
