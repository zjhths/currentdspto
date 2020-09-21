/*
 * mnic_gpio.c
 * ģ�鹦�ܣ�GPIOģ������Ÿ��ù��ܺ��жϽ���������
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
//��λ�ж��źš�mailbox�ж��źš���������Ԫ485ͨѶ�ж��ź�
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
//INT0~INT4 �ܽ�GPIO:
//INT0:GPIO0[15]
//INT1:GPIO7[11]
//INT2:GPIO1[14]
//INT3:GPIO6[0]
//INT4:GPIO2[15]
//BY WQ


/*
 * ��������	 void GPIOInit(void)
 * �������ܣ�  GPIOģ���ʼ��
 * ������ڣ�
 * �������ڣ�
 */
void GPIOInit(void)
{
	/*PSCģ�����ã���PSC1�е�GPIO0ģ�����ó�PD0(ALWAYS ON)״̬����һ״̬ΪENABLE*/
	PSCModuleControl(SOC_PSC_1_REGS, HW_PSC_GPIO, PSC_POWERDOMAIN_ALWAYS_ON,
								     PSC_MDCTL_NEXT_ENABLE);
	/*GPIO���Ÿ��ù��ܺ���*/
	GPIOPinMuxSetup();
}

/*
 * ��������	 void GPIOIntInit(void)
 * �������ܣ� �����жϹ���������GPIO�ж�
 */
void GPIOIntInit(void)
{

	INT_CLEAR=0xFF;

////	//INT0	  /*����GPIO0  pin (GPIO0[15])Ϊ����*/
    GPIODirModeSet(SOC_GPIO_0_REGS, 16, GPIO_DIR_INPUT);
//    /*����GPIO pin (GPIO0[15])Ϊ�����ش����ж�*/
    GPIOIntTypeSet(SOC_GPIO_0_REGS, 16, GPIO_INT_TYPE_RISEDGE);
//    /*ʹ��GPIO Bank0�ж�*/
    GPIOBankIntEnable(SOC_GPIO_0_REGS, 0);
//	/*���ж��������INT0ע��ΪGPIO�жϷ������*/
	IntRegister(C674X_MASK_INT11, GPIOIsr0);
//	/*ӳ���жϵ� DSP�������ж�*/
	IntEventMap(C674X_MASK_INT11, SYS_INT_GPIO_B0INT);
//	/*ʹ��DSP�������ж�INT5*/
	IntEnable(C674X_MASK_INT11);
////
////	//INT1	   /*����GPIO pin (INT1:GPIO7[11])Ϊ����*/
	    GPIODirModeSet(SOC_GPIO_0_REGS, 124, GPIO_DIR_INPUT);
	    /*����GPIO pin (GPIO7[11])Ϊ�����ش����ж�*/
	    GPIOIntTypeSet(SOC_GPIO_0_REGS, 124, GPIO_INT_TYPE_RISEDGE);
	    /*ʹ��GPIO Bank7�ж�*/
	    GPIOBankIntEnable(SOC_GPIO_0_REGS, 7);
		/*���ж��������INT8ע��ΪGPIO�жϷ������*/
		IntRegister(C674X_MASK_INT8, GPIOIsr1);
		/*ӳ���жϵ� DSP�������ж�*/
		IntEventMap(C674X_MASK_INT8, SYS_INT_GPIO_B7INT);
		/*ʹ��DSP�������ж�INT8*/
		IntEnable(C674X_MASK_INT8);
////
//	//INT2	        /*����GPIO pin (GPIO1[14])Ϊ����*/    VM_spi_int and IM_spi_int
//		        GPIODirModeSet(SOC_GPIO_0_REGS, 31, GPIO_DIR_INPUT);
//			    /*����GPIO pin 1(GPIO1[14])Ϊ�����ش����ж�*/
//			    GPIOIntTypeSet(SOC_GPIO_0_REGS, 31, GPIO_INT_TYPE_RISEDGE);
//			    /*ʹ��GPIO Bank1�ж�*/
//			    GPIOBankIntEnable(SOC_GPIO_0_REGS, 1);
//				/*���ж��������INT6ע��ΪGPIO�жϷ������*/
//				IntRegister(C674X_MASK_INT7, GPIOIsr2);
//				/*ӳ���жϵ� DSP�������ж�*/
//				IntEventMap(C674X_MASK_INT7, SYS_INT_GPIO_B1INT);
				/*ʹ��DSP�������ж�INT7*/
				//IntEnable(C674X_MASK_INT7);
//
////	INT3			 /*����GPIOΪ����*/          //AD�ж� 97  GP6[0]
				GPIODirModeSet(SOC_GPIO_0_REGS, 97, GPIO_DIR_INPUT);  //  GP6[0]
					/*����GPIO   GP6[0]Ϊ�����ش����ж�*/
				GPIOIntTypeSet(SOC_GPIO_0_REGS, 97, GPIO_INT_TYPE_RISEDGE);//  GP6[0]
				/*ʹ��GPIO Bank6�ж�*/
				GPIOBankIntEnable(SOC_GPIO_0_REGS, 6);
				/*���ж��������INT10ע��ΪGPIO�жϷ������*/
				IntRegister(C674X_MASK_INT10, GPIOIsr3);
				/*ӳ���жϵ� DSP�������ж�*/
				IntEventMap(C674X_MASK_INT10, SYS_INT_GPIO_B6INT);
			    /*ʹ��DSP�������ж�INT10*/
				IntEnable(C674X_MASK_INT10);
////
////	//INT4			 /*����GPIO pin (GPIO2[15])Ϊ����*/     //HDLC & USART
			GPIODirModeSet(SOC_GPIO_0_REGS, 48, GPIO_DIR_INPUT);
				/*����GPIO pin (GPIO2[15])Ϊ�����ش����ж�*/
			GPIOIntTypeSet(SOC_GPIO_0_REGS, 48, GPIO_INT_TYPE_RISEDGE);
				/*ʹ��GPIO Bank2�ж�*/
			GPIOBankIntEnable(SOC_GPIO_0_REGS, 2);
			/*���ж��������INT5ע��ΪGPIO�жϷ������*/
			IntRegister(C674X_MASK_INT9, GPIOIsr4);
				/*ӳ���жϵ� DSP�������ж�*/
			IntEventMap(C674X_MASK_INT9, SYS_INT_GPIO_B2INT);
				 /*ʹ��DSP�������ж�INT5*/
			IntEnable(C674X_MASK_INT9);



}

/*
 * ��������	 static void GPIOIsr(void)   HDLC�жϽ��պ���
 * �������ܣ� �жϷ������ִ��GPIO�жϡ��ر�GPIO�ж� �����ϵͳ�жϺ������ж�״̬������FLAG����Ϊ1  GPIO0[15]
 * mailbox�ж��ź�
 */
static void GPIOIsr0(void)
{

	/*�ر�GPIO bank0�����ж�*/
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
//        unsigned short int temp=UART_INT_Ctrl;//ӦΪ1���ж�0��
//        unsigned char num=1;
//        for(;num<7;num++)  //����6���ж�
//        {
//        	if(temp&0x0001==0x0001)
//        	{
//        		 RX_Ctrl=0x01<<(num-1);
//        		 COM_Recv(num,rx_Data_RS485_0);
//        		 UART_INT_Ctrl|=0x0001<<(num-1);//���ж�
//        	}
//        	temp=temp>>1;
//        }



    /*��DSPINTC�����ϵͳ�ж�*/
    IntEventClear(SYS_INT_GPIO_B0INT);
    /*���GPIO0[15]�ж�״̬*/
    GPIOPinIntClear(SOC_GPIO_0_REGS, 16);
    /*ʹ��GPIO bank0�ж�*/
    GPIOBankIntEnable(SOC_GPIO_0_REGS, 0);
    INT_EN=0xffff;
    INT_CLEAR=0xffff;
}
/*
 * ��������	 static void GPIOIsr1(void)
 * �������ܣ� �жϷ������ִ��GPIO�жϡ�GPIO0[14]
 * UART �ж�!
 */
static void GPIOIsr1(void)
{
   	  /*�ر�GPIO bank0�����ж�*/
    GPIOBankIntDisable(SOC_GPIO_0_REGS, 7);
    // Add your interrupt service c-ode here.


    /*��DSPINTC�����ϵͳ�ж�*/
    IntEventClear(SYS_INT_GPIO_B7INT);
    /*���GPIO1[13]�ж�״̬*/// 0*16+14+1=15
    GPIOPinIntClear(SOC_GPIO_0_REGS,124);
    /*ʹ��GPIO bank0�ж�*/
    GPIOBankIntEnable(SOC_GPIO_0_REGS, 7);


}
/*
 * ��������	 static void GPIOIsr2(void)
 * �������ܣ� �жϷ������ִ��GPIO�жϡ�GPIO1[14]
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
//	/*�ر�GPIO bank1�����ж�*/
    GPIOBankIntDisable(SOC_GPIO_0_REGS, 1);
//    // Add your interrupt service code here.
//    if(GPIOPinIntStatus(SOC_GPIO_0_REGS,31)==GPIO_INT_PEND)
//    {
//    	INT_CLEAR=0xFF;
//    	/*���GPIO1[14]�ж�״̬*/// 1*16+14+1=31

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
    /*ʹ��GPIO bank1�ж�*/
    GPIOBankIntEnable(SOC_GPIO_0_REGS,1);
    //    	 GPIOPinIntClear(SOC_GPIO_0_REGS,31);
    //    	 /*��DSPINTC�����ϵͳ�ж�*/
    //
	INT_EN=0xffff;
	INT_CLEAR=0xffff;
}
/*
 * ��������	 static void GPIOIsr3(void)
 * �������ܣ� �жϷ������ִ��GPIO�жϡ�GPIO0[13]
 */
static void GPIOIsr3(void)
{
		int length=1;
		double ad_temp=0;
        unsigned short *ad_data = (unsigned short *)&ad_temp;

		/*�ر�GPIO bank8�����ж�*/
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
//���º��������ڱ��ļ����·�����Ҫ���ĸ��Ϳ��ĸ�
		/*������ʱ��,1s*/
		//NoiseTest();
	    /*����λ�͵�ͨ������ʱ��,5min*/
	   //ZeroAndFusionTest();
	    /*��λУ��ʱ��*/
	   // PhaseTest();


	    /*��DSPINTC�����ϵͳ�ж�*/
	    IntEventClear(SYS_INT_GPIO_B6INT);
	    /*���GPIO8[15]�ж�״̬*/// 8*16+15+1=144
	    GPIOPinIntClear(SOC_GPIO_0_REGS,97);
	    /*ʹ��GPIO bank8�ж�*/
	    GPIOBankIntEnable(SOC_GPIO_0_REGS,6);

		INT_EN=0x0018;
		INT_CLEAR=0xffff;
}

/*
 * ��������	 static void GPIOIsr4(void)
 * �������ܣ� �жϷ������ִ��GPIO�жϡ�GPIO0[12]
 */
static void GPIOIsr4(void)
{
    // Add your interrupt service code here.
     INT_EN=0x18;
    //////////////////////////////////////////////////
    //HDLC��������
     unsigned char temp=0;
      unsigned char hdlc_error;
      unsigned char data_temp[512];
      unsigned int  datalen=0;
      /*�ر�GPIO bank0�����ж�*/
      GPIOBankIntDisable(SOC_GPIO_0_REGS, 2);
      HDLC_rx_ctrl_addr &= ~HDLC_Rx_int_enable;//��ֹ���������ж�
      temp = HDLC_int_flag_addr;
      if(temp & 0x01 == 0x01)   //�ж��Ƿ�ΪHDLC�ж�
      {

    	  hdlc_error=(HDLC_rx_status_addr>>9)&0x07;
    	  if(hdlc_error==0)
    	  {
    		  my_hdlc->recv(my_hdlc,data_temp,&datalen);
    	  }

    	  HDLC_rx_ctrl_addr=0x0;//HDLC��λ
    	  asm("   NOP");
    	  HDLC_rx_ctrl_addr=0x7;//��0λΪ��1������λ״̬��������1λΪ��1������ʹ��֡У�飬��2λΪ��1������ʹ�ܽ����ж�
    	  asm("   NOP");
    	  HDLC_clr_int_addr=0x1;//���ж�
    	  asm("   NOP");
    	  HDLC_clr_int_addr=0x0;//�������ж�״̬
    	  asm("   NOP");

    	  INT_CLEAR=0xFF;
    	  /*ʹ��GPIO bank0�ж�*/

        }

	  IntEventClear(SYS_INT_GPIO_B2INT);
	  /*���GPIO0[12]�ж�״̬*/// 0*16+12+1=13
	  GPIOPinIntClear(SOC_GPIO_0_REGS,48);
	  GPIOBankIntEnable(SOC_GPIO_0_REGS, 2);
}

/*
 * ��������	 static void GPIOIsr5(void)
 * �������ܣ� �жϷ������ִ��GPIO�жϡ�GPIO0[3]
 */
static void GPIOIsr5(void)
{

	/*�ر�GPIO bank0�����ж�*/
    GPIOBankIntDisable(SOC_GPIO_0_REGS, 0);
    // Add your interrupt service code here.

    /*��DSPINTC�����ϵͳ�ж�*/
    IntEventClear(SYS_INT_GPIO_B0INT);
    /*���GPIO0[3]�ж�״̬*/// 0*16+3+1=4
    GPIOPinIntClear(SOC_GPIO_0_REGS,4);
    /*ʹ��GPIO bank0�ж�*/
    GPIOBankIntEnable(SOC_GPIO_0_REGS, 0);
}



/*
 * ��������	 static void GPIOPinMuxSetup()
 * �������ܣ�  GPIO0[0]���Ÿ�������
 * ������ڣ�
 * �������ڣ�
 */

//INT0:GPIO0[15]
//INT1:GPIO7[11]
//INT2:GPIO1[14]
//INT3:GPIO6[0]
//INT4:GPIO2[15]


static void GPIOPinMuxSetup()
{
/*�궨�� PINMUX0_GPIO0_0_ENABLE 0x00000008u������λ0x0000000Cu���0x00008000u*/
//PINMUX0�Ĵ���GP0[15]   INT0

#define PINMUX0_GPIO0_15_ENABLE    (SYSCFG_PINMUX0_PINMUX0_3_0_GPIO0_15  << \
		SYSCFG_PINMUX0_PINMUX0_3_0_SHIFT)
	unsigned int savePinmux = 0;

	    savePinmux = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(0)) &
	                 ~(SYSCFG_PINMUX0_PINMUX0_3_0));

	    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(0)) =
	         (PINMUX0_GPIO0_15_ENABLE | savePinmux);

	    //PINMUX16�Ĵ���GP7[11]   INT1

#define PINMUX16_GPIO7_11_ENABLE    (SYSCFG_PINMUX16_PINMUX16_27_24_GPIO7_11  << \
		SYSCFG_PINMUX16_PINMUX16_27_24_SHIFT)
		    savePinmux = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(16)) &
	                 ~(SYSCFG_PINMUX16_PINMUX16_27_24));

	    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(0)) =
	         (PINMUX16_GPIO7_11_ENABLE | savePinmux);

	    //PINMUX2�Ĵ���GP1[14]   INT2

#define PINMUX2_GPIO1_14_ENABLE    (SYSCFG_PINMUX2_PINMUX2_7_4_GPIO1_14  << \
		SYSCFG_PINMUX2_PINMUX2_7_4_SHIFT)
		    savePinmux = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(2)) &
	                 ~(SYSCFG_PINMUX2_PINMUX2_7_4));

	    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(2)) =
	         (PINMUX2_GPIO1_14_ENABLE | savePinmux);


	    //PINMUX19�Ĵ���  INT3      //GP6[0]

#define PINMUX19_GPIO6_0_ENABLE    (SYSCFG_PINMUX19_PINMUX19_27_24_GPIO6_0  << \
		SYSCFG_PINMUX19_PINMUX19_27_24_SHIFT)
		    savePinmux = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(19)) &
	                 ~(SYSCFG_PINMUX19_PINMUX19_27_24));
	    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(19)) =
	         (PINMUX19_GPIO6_0_ENABLE | savePinmux);


	    //PINMUX5�Ĵ���GP2[15]   INT4

#define PINMUX5_GPIO2_15_ENABLE    (SYSCFG_PINMUX5_PINMUX5_3_0_GPIO2_15  << \
		SYSCFG_PINMUX5_PINMUX5_3_0_SHIFT)
		    savePinmux = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(5)) &
	                 ~(SYSCFG_PINMUX5_PINMUX5_3_0));
	    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(5)) =
	         (PINMUX5_GPIO2_15_ENABLE | savePinmux);

	    //PINMUX1�Ĵ���   INT5 ��
//#define PINMUX1_GPIO0_3_ENABLE    (SYSCFG_PINMUX1_PINMUX1_19_16_GPIO0_3  << \
//		SYSCFG_PINMUX1_PINMUX1_19_16_SHIFT)
//		    savePinmux = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(1)) &
//	                 ~(SYSCFG_PINMUX1_PINMUX1_19_16));
//	    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(1)) =
//	         (PINMUX1_GPIO0_3_ENABLE | savePinmux);
}



//
////�ڲ�ͨ�ź���
//void InterCommunication1()
//{
//	unsigned int i,j,k;
//	unsigned int freq_temp;
//	unsigned short int amp_temp;
//   // unsigned char hdlc_temp3;
//    //hdlc_temp3=HDLC_rx_data_out_addr & 0xFF;//��ȡHDLC�������ֽ�
//    //�������ֽڱ�ʾ����λ��Ҫ���·��Ĺ���ģʽ
//
//	 if(hdlc_temp3 == 0x34)			//Ҫ��ش���������100��float�Լ�2��byte���¶�����
//		{
//			cur_measure = 1;
//			vol_measure = 0;
//			ch_sel=1;
//
//			trans_data[0] = 0x52;//�������ݵĵ�һ���ֽ�Ϊ��λ���ĵ�ַ
//			trans_data[1] = Own_Add;//�������ݵĵڶ����ֽ�Ϊ��ǰ��·��ĵ�ַ
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
//		else if(hdlc_temp3 == 0x35)			//Ҫ��ش���ѹ����100��float�Լ�2��byte���¶�����
//		{
//			vol_measure = 1;
//			cur_measure = 0;
//
//			trans_data[0] = 0x52;//�������ݵĵ�һ���ֽ�Ϊ��λ���ĵ�ַ
//			trans_data[1] = Own_Add;//�������ݵĵڶ����ֽ�Ϊ��ǰ��·��ĵ�ַ
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
//    //hdlc_temp3=HDLC_rx_data_out_addr & 0xFF;//��ȡHDLC�������ֽ�
//    //�������ֽڱ�ʾ����λ��Ҫ���·��Ĺ���ģʽ
//
//
//	 if(hdlc_temp3 == 0x34)			//Ҫ��ش���������100��float�Լ�2��byte���¶�����
//		{
//			cur_measure = 1;
//			vol_measure = 0;
//			ch_sel=2;
//
//			trans_data[0] = 0x52;//�������ݵĵ�һ���ֽ�Ϊ��λ���ĵ�ַ
//			trans_data[1] = 0x42;//�������ݵĵڶ����ֽ�Ϊ��ǰ��·��ĵ�ַ
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
//		else if(hdlc_temp3 == 0x35)			//Ҫ��ش���ѹ����100��float�Լ�2��byte���¶�����
//		{
//			vol_measure = 1;
//			cur_measure = 0;
//
//			trans_data[0] = 0x52;//�������ݵĵ�һ���ֽ�Ϊ��λ���ĵ�ַ
//			trans_data[1] = 0x42;//�������ݵĵڶ����ֽ�Ϊ��ǰ��·��ĵ�ַ
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
//    //hdlc_temp3=HDLC_rx_data_out_addr & 0xFF;//��ȡHDLC�������ֽ�
//    //�������ֽڱ�ʾ����λ��Ҫ���·��Ĺ���ģʽ
//
//
//	 if(hdlc_temp3 == 0x34)			//Ҫ��ش���������100��float�Լ�2��byte���¶�����
//		{
//			cur_measure = 1;
//			vol_measure = 0;
//			ch_sel=3;
//
//			trans_data[0] = 0x52;//�������ݵĵ�һ���ֽ�Ϊ��λ���ĵ�ַ
//			trans_data[1] = 0x43;//�������ݵĵڶ����ֽ�Ϊ��ǰ��·��ĵ�ַ
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
//		else if(hdlc_temp3 == 0x35)			//Ҫ��ش���ѹ����100��float�Լ�2��byte���¶�����
//		{
//			vol_measure = 1;
//			cur_measure = 0;
//
//			trans_data[0] = 0x52;//�������ݵĵ�һ���ֽ�Ϊ��λ���ĵ�ַ
//			trans_data[1] = 0x43;//�������ݵĵڶ����ֽ�Ϊ��ǰ��·��ĵ�ַ
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
//    //hdlc_temp3=HDLC_rx_data_out_addr & 0xFF;//��ȡHDLC�������ֽ�
//    //�������ֽڱ�ʾ����λ��Ҫ���·��Ĺ���ģʽ
//
//
//	 if(hdlc_temp3 == 0x34)			//Ҫ��ش���������100��float�Լ�2��byte���¶�����
//		{
//			cur_measure = 1;
//			vol_measure = 0;
//			ch_sel=4;
//
//			trans_data[0] = 0x52;//�������ݵĵ�һ���ֽ�Ϊ��λ���ĵ�ַ
//			trans_data[1] = 0x44;//�������ݵĵڶ����ֽ�Ϊ��ǰ��·��ĵ�ַ
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
//		else if(hdlc_temp3 == 0x35)			//Ҫ��ش���ѹ����100��float�Լ�2��byte���¶�����
//		{
//			vol_measure = 1;
//			cur_measure = 0;
//
//			trans_data[0] = 0x52;//�������ݵĵ�һ���ֽ�Ϊ��λ���ĵ�ַ
//			trans_data[1] = 0x44;//�������ݵĵڶ����ֽ�Ϊ��ǰ��·��ĵ�ַ
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
//	//����iir
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
//	//��������1s����
//    //����NOISE
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
//	/*��λУ��ʱ��*/
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
//	/*����λ�͵�ͨ������ʱ��*/
//	//5���ӳ�ʱ�����
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
