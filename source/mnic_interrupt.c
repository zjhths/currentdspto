/*
 * mnic_interrupt.c
 *
 *  Created on: 2019-11-15
 *      Author: Administrator
 */
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
//#include "i2c.h"
#include "hw_i2c.h"
#include "tms320c6748_sysconfig.h"
#include "types.h"
#include "mnic_i2c.h"
#include "mnic_interrupt.h"
#include "func.h"


extern unsigned int count;
extern unsigned int flag;
extern unsigned char dataToSlave[2];
//
//extern unsigned int ADI[8];
//extern unsigned int ADI_L[8];
//extern int ADI_signed[8];
//extern float ADI_f[8];
//
//extern unsigned int ADS[8];
//extern int ADS_signed[8];
//extern float ADS_f[8];
//unsigned short int temp_high_S[8]={0,0,0,0,0,0,0,0};
//unsigned short int temp_low_S[8]={0,0,0,0,0,0,0,0};
//
//extern int SPI_value;
//extern int VM_SPI_value;
//extern float VM_SPI_value_f;
//extern float SPI_value_f;
//
//extern unsigned int temp[8];
//extern unsigned char flame;
//unsigned int uart_count;
//extern unsigned int count;
//extern unsigned int flag;
//extern unsigned char dataToSlave[2];
//extern unsigned char *HDLC_trans;
//extern unsigned char *uart_trans;
//extern unsigned char HDLC_Rev_Frame[11];
//extern unsigned int hdlc_count1,hdlc_count2,hdlc_count3,hdlc_count4,hdlc_count5,hdlc_count6,hdlc_count7,hdlc_count8,hdlc_count9,hdlc_count10,hdlc_count11,hdlc_count12;
//wave_msg vol_wave;
//wave_msg cur_wave;
//extern float wave_freq;					//波形频率
//extern float wave_range;					//波形幅值
//extern float wave_range_c;			//将电流幅值转换为电压幅值
//
//extern int wave_type;				//波形类别，默认输出固定值
//extern float last_range;
//extern float last_range_i;
//
//extern unsigned int uart_cnt;
//extern unsigned int uart_temp1,uart_temp2;
//extern float uart_temp;
//extern float uart_temp_1;
//float uart_temp_old;
//extern float ADS_test[4000];
//int ADS_test_count=0;
//
//
//extern unsigned char type_flag;
//extern unsigned int output_en;
//
//
//extern unsigned int wave_cnt;
//extern unsigned char trans_data[407];		//用于内部传输数据
//
//extern float adi_out_average,adv_out_average;	//8路AD测量数据的平均值
//int temp_num;
//
//extern unsigned int ds_cnt;
//extern unsigned int DAI_CONV ;
//extern unsigned int DAV_CONV ;
//float MaxCurrent = 50;//mA
//float MaxVoltage = 15;//V
//
////
//int zsp_cnt = 0;
//int zhihou = 5;
//float datai_to_da = 0;		//给DA的输出值,电流
//float datav_to_da = 0;		//给DA的输出值，电压
//unsigned int chazhi_cnt=0;
//
//float zsp_out[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//float zsp_in[3] = {0,0,0};
//extern unsigned char rev_flag;
//float step_range_i = 0;
//float step_range_v = 0;
//extern int DA_DATA;
//extern float CurScale;
//extern unsigned int out_cnt_v ;
//extern unsigned char need_vol_array[19];
//extern unsigned char need_cur_array[19];
//extern unsigned int out_cnt_i ;
//extern unsigned int out_cnt_v ;
//extern union my_uni up_data;
//extern union my_uni back_data;
//extern union my_uni back_data1;
//extern int updata_cnt;
//union data_buffer cur_data_ext[4];		//4个通道的数据都收进来
//union data_buffer vol_data_ext[4];
//
//union data_buffer cur_data_output[4];		//4个周期的数据发送出去
//union data_buffer vol_data_output[4];
//unsigned char start_output = 0;
//extern int NoLoad ;
//unsigned char OutVol = 0;
//unsigned int back_cur_flag = 0;
//unsigned int back_vol_flag=0;
//unsigned char need_vol_flag = 0;
//extern unsigned char trans_data_out_cur[19];	//用于对外回传数据
//extern unsigned char trans_data_out_vol[19];	//用于对外回传数据
//unsigned char cur_output_en = 0;
//unsigned char vol_output_en = 0;
//unsigned int test_count=0;
//unsigned char hdlc_temp0,hdlc_temp1,hdlc_temp2;
//extern float datai_to_da_pid,datav_to_da_pid;
//
//extern float adv_ma[1000];
//extern float adv_sum,adv_last_end;
//extern unsigned int adv_ma_count;
//extern float adi_ma[1000];
//extern float adi_sum,adi_last_end;
//extern unsigned int adi_ma_count;
//extern unsigned char AD_test_flag;
//float adv_out_ma,adi_out_ma=0;
//
//unsigned int adi_s_count =0;
//float  adi_s_out_ma=0,adi_s_sum=0;
//
//
//float test[40000];
//int iii = 0 ;
//
//
void I2CIsr()
{
    unsigned int intCode = 0;

    /* Get interrupt vector code */
    intCode = I2CInterruptVectorGet(SOC_I2C_0_REGS);

    /* Clear status of interrupt */
#ifdef _TMS320C6X
    IntEventClear(SYS_INT_I2C0_INT);
#else
    IntSystemStatusClear(SYS_INT_I2CINT0);
#endif

    if (intCode == I2C_INTCODE_TX_READY)
    {
         /* Put data to data transmit register of i2c */
         I2CMasterDataPut(SOC_I2C_0_REGS, dataToSlave[count++]);
    }

    if (intCode == I2C_INTCODE_STOP)
    {
	/* Disable transmit data ready register */
        I2CMasterIntDisableEx(SOC_I2C_0_REGS,I2C_INT_TRANSMIT_READY);
        flag = 0;
    }
}
//
//
//
//void VM_spi_int_and_IM_spi_int()
//{
//	    if(	VM_spi_rx_flag_addr==0x1)//判断是否为电压测量中断
//	    {
////	       GPIOBankIntDisable(SOC_GPIO_0_REGS, 0);  //disable GPIOBank 0
//	       unsigned int j,k;
////	       gpiointFlag = 2;
//
//	       IntEventClear(SYS_INT_GPIO_B0INT);       //清中断事件
//	       GPIOPinIntClear(SOC_GPIO_0_REGS, 31);//清GPIO中断
//
//	       unsigned short int VM_spi_temp_high,VM_spi_temp_low;
//	       VM_spi_temp_high = VM_spi_rx_high_addr ;
//	       VM_spi_temp_low  = VM_spi_rx_low_addr  ;
//	       VM_SPI_value     = VM_spi_temp_high*65536 +  VM_spi_temp_low ;//读取电压测量部分通过spi传来的数据
//	       VM_SPI_value_f   = -VM_SPI_value/1000000.0*1.0234;//转换为单位为V的电压数据
//	       adv_out_average  = VM_SPI_value_f;
//
//	       float wwwv;					//输出正弦波时的ω
//
//	   	   if(output_en)//判断输出标志位
//	   		   {
//	   			   switch(wave_type)//判断输出类型
//	   			   {
//	   				case WAVE_SIN ://输出正弦波
//	   					wwwv = 2 * PI * wave_freq;//w=2*pi*freq
//	   					datav_to_da = wave_range*sin(wwwv * wave_cnt / 64000);//控制节拍为64kHz时任意时刻的输出设定值
//	   					if(wave_cnt< (64000/ wave_freq-1))//循环，不断输出
//	   						wave_cnt++;
//	   					else
//	   						wave_cnt=0;
//	   					asm(    " NOP");
//
//	   					break;
//
//	   				case WAVE_FIXED ://输出定值
//						if(rev_flag == 1)
//						{
//							rev_flag = 0;
//							chazhi_cnt = 0;
//							step_range_v = wave_range - last_range;//两次输出之间的变化量
//						}
//
//						chazhi_cnt++;
//						datav_to_da = last_range+ chazhi_cnt* step_range_v/ 4;//按四次插值输出
//
//				//**********new code by web 1030**************//
//						if(chazhi_cnt > 3 )
//						{
//							chazhi_cnt = 3;
//						}
//
//   					    break;
//
//	   				case WAVE_RECTANG ://方波
//	   					datav_to_da = wave_range * ((wave_cnt / ((int)(16000/wave_freq))) % 2);//任意时刻的输出值
//
//	   					if(wave_cnt< (64000/ wave_freq-1))//循环，不断输出
//	   						wave_cnt++;
//	   					else
//	   						wave_cnt=0;
//
//	   					asm(    " NOP");
//	   					break;
//
//	   				case WAVE_TRI ://输出三角波
//	   					datav_to_da = wave_range / 64000 * wave_freq * (wave_cnt%((int)(64000 / wave_freq)));//任意时刻的输出值
//
//	   					if(wave_cnt< (64000/ wave_freq-1))//循环，不断输出
//	   						wave_cnt++;
//	   					else
//	   						wave_cnt=0;
//	   					asm(    " NOP");
//	   					break;
//	   			    }
//	   			    if(ds_cnt < 64000)
//	   			    {
//	   				    ds_cnt++;
//	   		     	}
//	   			    else
//	   				    ds_cnt = 0;
//
//	   				DA_DATA = (int)(datav_to_da * DAV_CONV);//转换为输出值
//
//	   			    DA_Dout_low_Addr = DA_DATA & 0x0000FFFF;
//	   			    DA_Dout_high_Addr = (DA_DATA>>16) & 0x0000FFFF;//转换为DA输出寄存器的值
//
//	           }
//			up_data.uni_float = adv_out_average;//将电压测量值上传
//			if(up_data.uni_float > 6)
//			{
//				asm("	NOP");
//			}
//				//**********************0.0625ms更新回传指令的数据******************************//
//				//这是外部通讯时回传的数据
//			    //need_vol_array有19个字节，0~2字节是用来存回传数据的地址信息的，3~18字节存储4个测量值，每个测量值占4个字节
//			if(out_cnt_v%4 == 1)//4个控制节拍更新一次，即0.0625ms更新回传数据
//			{
//				for(j = 0;j<3;j++)//将所有数据前移4个字节，空出最后四个字节用于存储新的数据
//				{
//					need_vol_array[3 + j * 4] = need_vol_array[3 + (j+1) * 4];
//					need_vol_array[4 + j * 4] = need_vol_array[4 + (j+1) * 4];
//					need_vol_array[5 + j * 4] = need_vol_array[5 + (j+1) * 4];
//					need_vol_array[6 + j * 4] = need_vol_array[6 + (j+1) * 4];
//				}
//				need_vol_array[15] = up_data.uni_char[0];
//				need_vol_array[16] = up_data.uni_char[1];
//				need_vol_array[17] = up_data.uni_char[2];
//				need_vol_array[18] = up_data.uni_char[3];//存储新的测量数据
//			}
//			out_cnt_v++;
//			if(out_cnt_v>15)
//			out_cnt_v = 0;
//		//**********************0.03125更新回传指令的数据,3.125ms对回传数据整体更新******//
//
//		//******************上位机要数******************//
//		   if(data_prepare==1)//判断上位机是否要数
//		   {
//			   trans_data[2] = 0x35;//上位机要求回传电压数据时对应的模式为0x35
//			   if(updata_cnt%2 == 1)//数据更新频率为32000Hz
//			    {
//				    for(k=0;k<4;k++)
//				    {
//	  				trans_data[(updata_cnt-1)*2+k+3] = up_data.uni_char[k];//从trans_data[3]开始存储数据，每次存储4个字节，相当于一个测量值
//				    }
//			    }
//			    updata_cnt++;
//			  if(updata_cnt >= 200)//上位机每次要数就更新100个float
//			   {
//				updata_cnt=0;
//				data_prepare = 0;
//			   }
//		   }
//		   VM_spi_int_clr_addr  = 0x1;  //清中断标志位
//		   asm(  " NOP");
//           VM_spi_int_clr_addr  = 0x0;  //结束清中断
//	    }
//	    else if(spi_rx_flag_addr  == 0x1)//判断是否为电流测量
//		{
//		   	float wwwi;					//输出正弦波时的ω
//		   	unsigned int j,k;
//
////	        gpiointFlag = 1;
//	        IntEventClear(SYS_INT_GPIO_B1INT);       //清中断事件
//	        GPIOPinIntClear(SOC_GPIO_0_REGS, 31);//清GPIO中断
//
//	        unsigned short int spi_temp_high,spi_temp_low;
//	        float err_1;
//	        spi_temp_high = spi_rx_high_addr ;
//	        spi_temp_low  = spi_rx_low_addr  ;
//	        SPI_value     = (spi_temp_high<<16) +  spi_temp_low ;//将spi传输的数据转化为int型
//	        SPI_value_f   = -SPI_value/1000000.0;   //将数据转化为float型，单位为mA，电路设计原因，要取负
//	        adi_out_average  = SPI_value_f;
//	        if(iii < 40000)//存储40000个测量数据，用于测试分析数据精度水平，为测试代码，可以去掉
//	        {
//	        	test[iii]=adi_out_average;
//	        	iii++;
//	        }
//	        wave_range_c=wave_range;//电流输出值
//	        last_range_i=last_range;//上一个电流输出值
//
//	    	if(output_en)//判断输出标志位
//	    		{
//	    			switch(wave_type)//判断输出类型
//	    			{
//	    				case WAVE_SIN ://正弦
//	    					wwwi = 2 * PI * wave_freq;//w=2*pi*freq
//	    					datai_to_da = wave_range_c*sin(wwwi * wave_cnt / 64000);//控制节拍为64kHz时任意时刻的输出设定值
//
//	    					if(wave_cnt< (64000/ wave_freq-1))//循环，不断输出
//	    						wave_cnt++;
//	    					else
//	    						wave_cnt=0;
//		   					asm(    " NOP");
//
//	    					break;
//
//	    				case WAVE_FIXED ://输出定值
//
//							if(rev_flag == 1)
//							{
//								rev_flag = 0;
//								chazhi_cnt = 0;
//								step_range_i = wave_range_c - last_range_i;//两次输出之间的变化量
//							}
//
//							chazhi_cnt++;
//							datai_to_da = last_range_i+ chazhi_cnt* step_range_i/ 4;//按四次插值输出
//							if(chazhi_cnt > 3)
//							{
//								chazhi_cnt = 3;
//							}
//	    					break;
//
//	    				case WAVE_RECTANG ://方波
//	    					datai_to_da = wave_range_c * ((wave_cnt / ((int)(16000/wave_freq))) % 2);//任意时刻的输出值
//
//	    					if(wave_cnt< (64000/ wave_freq-1))//循环，不断输出
//	    						wave_cnt++;
//	    					else
//	    						wave_cnt=0;
//		   					asm(    " NOP");
//
//	    					break;
//	    				case WAVE_TRI ://输出三角波
//	    					datai_to_da = wave_range_c / 64000 * wave_freq * (wave_cnt%((int)(64000 / wave_freq)));//任意时刻的输出值
//
//	    					if(wave_cnt< (64000/ wave_freq-1))
//	    						wave_cnt++;
//	    					else
//	    						wave_cnt=0;
//		   					asm(    " NOP");
//
//	    					break;
//	    			}
//	   			    if(ds_cnt < 64000)
//	   			    {
//	   				    ds_cnt++;
//	   		     	}
//	   			    else
//	   				    ds_cnt = 0;
//
//				if((adi_out_average-datai_to_da < 0.1 )&& (adi_out_average-datai_to_da > -0.1 ))//输出值与设定值之间相差±0.1V以内，进行pid控制
//				{
//					pp->pv = adi_out_average;//当前测量值
//					pp->sp = datai_to_da;//当前设定值
//					err_1=(datai_to_da-adi_out_average)*1000;//误差的1000倍
//					datai_to_da_pid = datai_to_da_pid + pid_calc(&pid_str);//进入PID函数进行计算
//				}
//
//
//
//	   				DA_DATA = (int)(datai_to_da * DAI_CONV);//输出设定值，没有输出pid反馈的值，为开环输出
//	   			    DA_Dout_low_Addr = DA_DATA & 0x0000FFFF;
//	   			    DA_Dout_high_Addr = (DA_DATA>>16) & 0x0000FFFF;//转换为DA输出寄存器的值
//
//		        }
//			    up_data.uni_float = adi_out_average/CurScale;//将电流测量值上传
//		//**********************0.0625ms更新回传指令的数据******************************//
//		//这是外部通讯时回传的数据
//		//need_vol_array有19个字节，0~2字节是用来存回传数据的地址信息的，3~18字节存储4个测量值，每个测量值占4个字节
//			    if(out_cnt_i%4 == 1)//4个控制节拍更新一次，即0.0625ms更新回传数据
//		        	{
//				       for(j = 0;j<3;j++)//将所有数据前移4个字节，空出最后四个字节用于存储新的数据
//				       {
//					      need_cur_array[3 + j * 4] = need_cur_array[3 + (j+1) * 4];
//					      need_cur_array[4 + j * 4] = need_cur_array[4 + (j+1) * 4];
//					      need_cur_array[5 + j * 4] = need_cur_array[5 + (j+1) * 4];
//					      need_cur_array[6 + j * 4] = need_cur_array[6 + (j+1) * 4];
//			         	}
//				        need_cur_array[15] = up_data.uni_char[0];
//				        need_cur_array[16] = up_data.uni_char[1];
//				        need_cur_array[17] = up_data.uni_char[2];
//				        need_cur_array[18] = up_data.uni_char[3];//存储新的测量数据
//			       }
//			    out_cnt_i++;
//			    if(out_cnt_i>15)
//			    out_cnt_i = 0;
//		//***************0.03125更新回传指令的数据,3.125ms对回传数据整体更新*******************//
//		//******************上位机要数******************//
//
//		       if(data_prepare==1)						//上位机要一次数，运行一次
//	           	{
//			       trans_data[2] = 0x34;//上位机要求回传电压数据时对应的模式为0x35
//		           if(updata_cnt%2 == 1)				//数据更新频率为32000Hz
//		         	{
//				         for(k=0;k<4;k++)
//				         {
//		  			        trans_data[(updata_cnt-1)*2+k+3] = up_data.uni_char[k];//从trans_data[3]开始存储数据，每次存储4个字节，相当于一个测量值，共存储100个测量值
//				         }
//			        }
//			       updata_cnt++;
//		       	   if(updata_cnt >= 200)//上位机每次要数就更新100个float
//			       {
//				     updata_cnt=0;
//				     data_prepare = 0;
//			       }
//	           	}
//
//	        spi_int_clr_addr  = 0x1;   //清中断标志位
//	        asm(  " NOP");
//            spi_int_clr_addr  = 0x0;  //结束清中断
//		}
//	    else
//	    	asm(  " NOP");
//}
//void HDLC_and_uart_isr()
//{
//
//	int i;
//	if(INT_STATUSA & 0x01 == 0x01)   //判断是否为HDLC中断
//	{
//    unsigned int hdlc_byte_num;
//    unsigned int hdlc_byte_temp;
//
//    IntEventClear(SYS_INT_GPIO_B1INT);       //清中断事件
//
//	HDLC_rx_ctrl_addr &= ~HDLC_Rx_int_enable;//禁止产生接收中断
//	hdlc_byte_temp = HDLC_rx_status_addr & 0x01ff;
//	hdlc_byte_num = hdlc_byte_temp>>1;      //接收到的数据个数
//
////    for(i=0;i<11;i++)   //read data
////    {
////        HDLC_Rev_Frame[i]= HDLC_rx_data_out_addr & 0xFF;
////        asm("   NOP");
////    }
////    if(hdlc_byte_num!=11)
////    {
////        asm("   NOP");
////    }
//
//    //judge
//	hdlc_count1++;
//
//	hdlc_temp1 = HDLC_rx_data_out_addr & 0xFF ;//接收到的第一个字节
//	hdlc_temp2 = HDLC_rx_data_out_addr & 0xFF ;//接收到的第二个字节
//	if(hdlc_temp2 == 0x52)//第二个字节为源地址，若为0x52，代表为上位机发送来的命令
//	{
//		if((hdlc_temp1 == Own_Add)||(hdlc_temp1 == 0x45))//第一个地址为目标地址，若与当前电路板地址相同或为0x45（表示选中所有电路板），则进入内部通信
//		{
//			hdlc_count2++;
//			InterCommunication();//内部通信函数
//		}
//		else
//			hdlc_count3++;
//	}
//	else if(hdlc_temp2 == 0x53)//若为0x53，代表为外部计算机发送来的命令
//	{
//		hdlc_count4++;
//		ExterCommunication(hdlc_temp1);//进入外部通信函数，形参为接收到的第一个字节
//	}
//	else
//	{
//		protocol_error = 1;//若上面两种情况都不符合却进入了HDLC中断，说明有异常
//		hdlc_count5++;
//	}
//
//    HDLC_rx_ctrl_addr=0x0;//HDLC复位
//    asm("   NOP");
//    HDLC_rx_ctrl_addr=0x7;//第0位为“1”代表复位状态结束，第1位为“1”代表使能帧校验，第2位为“1”代表使能接收中断
//    asm("   NOP");
//	HDLC_clr_int_addr=0x1;//清中断
//    asm("   NOP");
//    HDLC_clr_int_addr=0x0;//跳出清中断状态
//    asm("   NOP");
//	}
//	else if(uart_int_flag_Addr==1)//判断是否为UART中断，用于接收温度
//	     {
////		        gpiointFlag = 3;
//		        IntEventClear(SYS_INT_GPIO_B0INT);       //清中断事件
//		        GPIOPinIntClear(SOC_GPIO_0_REGS, 15);//清GPIO中断
//
//	//	  flame=uart_Rxd_Addr;
//	//    while(uart_Rxd_Addr!=0xAA)
//	//    {
//	//       i=1;
//	//    }
//		      //  int temp_num;
//		        temp_num = (Uart_status_Addr & 0xF000)/4096;//UART接收到的数据个数
//		        asm("	NOP");
//		        test_count=0;
//		        if(temp_num>=9)//接收到的数据大于9
//		        {
//		        	flame=uart_Rxd_Addr;//第一个字节为帧头若为0xAA，则接收正确
//		        	if(flame == 0xAA)//帧头若为0xAA，则继续接收
//		        	{
//						temp[0]=uart_Rxd_Addr;
//						temp[1]=uart_Rxd_Addr;
//						temp[2]=uart_Rxd_Addr;
//						temp[3]=uart_Rxd_Addr;
//						temp[4]=uart_Rxd_Addr;
//						temp[5]=uart_Rxd_Addr;
//						temp[6]=uart_Rxd_Addr;
//						temp[7]=uart_Rxd_Addr;//接收接下来的8个数据
//						uart_temp1=(temp[3]<<24)+(temp[2]<<16)+(temp[1]<<8)+temp[0];//第一个温度值
//						uart_temp2=(temp[7]<<24)+(temp[6]<<16)+(temp[5]<<8)+temp[4];//第二个温度值
//						uart_temp_old = uart_temp;
//						uart_temp=uart_temp1/1000.0;
//						uart_temp_1=uart_temp2/1000.0;//将温度数据存储
//
//						uart_rst_Addr=1;//UART复位
//						//	asm("	NOP");
//						for(i=0;i<600;i++);
//						uart_rst_Addr=0;//停止UART复位
//
//		        	}
//
//		        }
//		        else
//		        {
//		       	  asm("	 NOP");
//		        }
//
//			uart_clr_int_Addr=1;//清中断
//			asm("	NOP");
//			uart_clr_int_Addr=0;//结束清中断
//		    for(i=0;i<6;i++);
//	        LED=~LED;
//	    }
//	else
//	{
//		asm("	NOP");
//	}
//}

//内部通信函数
//void InterCommunication()
//{
//	unsigned int i,j;
//    unsigned char hdlc_temp3;
//    hdlc_temp3=HDLC_rx_data_out_addr & 0xFF;//读取HDLC第三个字节
//    //第三个字节表示了上位机要求电路板的工作模式
//	if(hdlc_temp3 == 0x31)				//输出电流数据
//	{
//		type_flag=current_out;
//		cur_wave.wave_style = HDLC_rx_data_out_addr & 0xFF;//第四个字节表示输出电流类型
//		wave_type = cur_wave.wave_style;	//输出电流类型
//		for(i=0;i<4;i++)
//		{
//			cur_wave.fre_data.c_data[i] = HDLC_rx_data_out_addr & 0xFF;//第5/6/7/8个字节表示频率信息
//		}
//		wave_freq = cur_wave.fre_data.f_data;	//采用了一个共同体结构，转化为float型的频率信息
//		for(j=0;j<4;j++)
//		{
//			cur_wave.amp_data.c_data[j] = HDLC_rx_data_out_addr & 0xFF;//第9,10,11,12个字节表示幅值信息
//		}
//
//
//		wave_range = cur_wave.amp_data.f_data * CurScale;	//采用了一个共同体结构，转化为float型的幅值信息
//
//
//		last_range = wave_range;		//保存上一次幅值
//		rev_flag = 1;
//		//******************new code by web 10 29********************//
//
//	    DA_OE_Addr=0x0;    //打开DA输出
//		cur_output_en = 1;//应该没有什么用， 其他地方都没有用到
//		output_en=0x1;//使能输出标志位
//		if(NoLoad == 1)//如果为空载，则不允许电流输出
//		{
//			output_en = 0;
//		}
//		VM_spi_ctrl_addr=0x0;//禁止电压测量模块产生中断
//		spi_ctrl_addr=0x1;//使能电流测量模块产生中断
//        VM_spi_int_clr_addr  = 0x1;  //清电压测量模块中断标志位
//        asm(  " NOP");
//        VM_spi_int_clr_addr  = 0x0;  //跳出清中断状态
//        spi_int_clr_addr  = 0x1;  //清电流测量模块中断标志位
//        asm(  " NOP");
//        spi_int_clr_addr  = 0x0;  //跳出清中断状态
//
//
//	}
//	else if(hdlc_temp3 == 0x32)			//输出电压数据
//	{
//		type_flag=voltage_out;//输出电压模式
//		vol_wave.wave_style = HDLC_rx_data_out_addr & 0xFF;//电压输出类型
//		wave_type = vol_wave.wave_style;
//		for(i=0;i<4;i++)
//		{
//			vol_wave.fre_data.c_data[i] = HDLC_rx_data_out_addr & 0xFF;////第5/6/7/8个字节表示频率信息
//		}
//		wave_freq = vol_wave.fre_data.f_data;	//采用了一个共同体结构，转化为float型的频率信息
//		for(j=0;j<4;j++)
//		{
//			vol_wave.amp_data.c_data[j] = HDLC_rx_data_out_addr & 0xFF;//第9,10,11,12个字节表示幅值信息
//		}
//		wave_range = vol_wave.amp_data.f_data ;//采用了一个共同体结构，转化为float型的幅值信息
//		last_range = wave_range;//保存上一次的输出值
//		rev_flag = 1;
//		//******************new code by web 10 30********************//
//	    DA_OE_Addr=0x0;    //打开DA输出
//		vol_output_en = 1;//使能电压输出，也没有用到
//		output_en=0x1;//使能输出标志
//		if(NoLoad == 1)//如果没有负载，则不允许输出
//		{
//			output_en = 0;
//		}
//
//		spi_ctrl_addr=0x0;     //禁止电流测量模块产生中断
//		VM_spi_ctrl_addr=0x1;//使能电压测量模块产生中断
//        spi_int_clr_addr  = 0x1;  //清电流测量中断标志位
//        asm(  " NOP");
//        spi_int_clr_addr  = 0x0;  //结束清中断
//        VM_spi_int_clr_addr  = 0x1;  //清电压测量中断标志位
//        asm(  " NOP");
//        VM_spi_int_clr_addr  = 0x0;  //结束清中断
//
//
//	}
//
//	else if(hdlc_temp3 == 0x33)			//准备当前测量状态下的数据100个float
//	{
//		data_prepare = 1;
//	}
//	else if(hdlc_temp3 == 0x34)			//要求回传电流数据100个float以及2个byte的温度数据
//	{
//		cur_measure = 1;
//		vol_measure = 0;
//		VM_spi_ctrl_addr=0x0;//禁止电压测量模块产生中断
//	    spi_ctrl_addr=0x1;//使能电流测量模块产生中断
//		trans_data[0] = 0x52;//发送数据的第一个字节为上位机的地址
//		trans_data[1] = Own_Add;//发送数据的第二个字节为当前电路板的地址
//
//        VM_spi_int_clr_addr  = 0x1;  //clear int
//        asm(  " NOP");
//        VM_spi_int_clr_addr  = 0x0;  //recover from clear
//        spi_int_clr_addr  = 0x1;  //clear int
//        asm(  " NOP");
//        spi_int_clr_addr  = 0x0;  //recover from clear
//
//
//	}
//	else if(hdlc_temp3 == 0x35)			//要求回传电压数据100个float以及2个byte的温度数据
//	{
//		vol_measure = 1;
//		cur_measure = 0;
//	    spi_ctrl_addr=0x0;//禁止电流测量模块产生中断
//		VM_spi_ctrl_addr=0x1;//使能电压测量模块产生中断
//		trans_data[0] = 0x52;//发送数据的第一个字节为上位机的地址
//		trans_data[1] = Own_Add;//发送数据的第二个字节为当前电路板的地址
//
//        spi_int_clr_addr  = 0x1;  //clear int
//        asm(  " NOP");
//        spi_int_clr_addr  = 0x0;  //recover from clear
//        VM_spi_int_clr_addr  = 0x1;  //clear int
//        asm(  " NOP");
//        VM_spi_int_clr_addr  = 0x0;  //recover from clear
//	}
//	else if(hdlc_temp3 == 0x39)			//停止输出
//	{
//		DA_OE_Addr=0x1;    //close DA out
//		cur_measure = 0;
//		vol_measure = 0;
//		data_prepare = 0;//不再更新回传数据
//		output_en = 0;//复位输出标志位
//	    DA_Dout_low_Addr =0x0000;
//	    DA_Dout_high_Addr=0x0000;//DA输出0
//	}
//	else if(hdlc_temp3 == 0xFF)			//系统初始化
//	{
//		DA_OE_Addr=0x1;    //close DA out
//		vol_output_en = 0;
//		cur_output_en = 0;
//		VM_spi_ctrl_addr=0x0;//禁止电流测量模块产生中断
//	    spi_ctrl_addr=0x1;//禁止电流测量模块产生中断
//
//		wave_type = WAVE_FIXED;//输出类型为直流
//		wave_freq = 0;//频率为0
//
//		/********* 新增1010 **********/
//		last_range = 0;		//保存上一次幅值
//		/********* 新增1010 **********/
//
//		wave_range = 0;
//	    DA_Dout_low_Addr =0x0000;
//	    DA_Dout_high_Addr=0x0000;
//		start_output = 0;//禁止输出
//
//        VM_spi_int_clr_addr  = 0x1;  //clear int
//        asm(  " NOP");
//        VM_spi_int_clr_addr  = 0x0;  //recover from clear
//        spi_int_clr_addr  = 0x1;  //clear int
//        asm(  " NOP");
//        spi_int_clr_addr  = 0x0;  //recover from clear
//
//	}
//	else
//		protocol_error = 1;//error
//
//}
//
////外部通信函数
//void ExterCommunication(unsigned char target)
//{
//
//	int i,j,k;
//    unsigned char hdlc_temp3;
//    hdlc_temp3=HDLC_rx_data_out_addr & 0xFF;//第三个字节为工作模式
//	if((hdlc_temp3 == 0x21)&&((target == 0x45)||(target == Own_Add)))//开始外部通讯输出功能
//	{
//		hdlc_count6++;
//		start_output = 1;//使能外部通信控制输出
//		wave_type = WAVE_FIXED;			//外部输出认为是直流输出
//		wave_freq = 0;//频率为0
//
//		/********* 新增1010 **********/
//		last_range = 0;		//保存上一次幅值
//		/********* 新增1010 **********/
//
//		wave_range = 0;//频率默认为0
//		output_en = 1;//使能输出标志位
//
//		rev_flag = 1;
//
//		for(i = 0;i<4;i++)
//		{
//			cur_data_ext[i].f_data = 0;	//初始化电流输幅值信息数组
//			vol_data_ext[i].f_data = 0;//初始化电压输出幅值信息数组
//		}
//		for(i = 0;i<19;i++)				//回数数组清零
//		{
//			trans_data_out_vol[i] = 0;
//			trans_data_out_cur[i] = 0;
//			need_vol_array[i] = 0;
//			need_cur_array[i] = 0;
//		}
//
//	    DA_Dout_low_Addr =0x0000;
//	    DA_Dout_high_Addr=0x0000;//DA输出0
//		DA_OE_Addr=0x0;    //open DA out
//
//
//		VM_spi_ctrl_addr=0x0;//禁止电压测量模块产生中断
//		spi_ctrl_addr=0x1;//使能电流测量模块产生中断，为默认状态
//        asm(  " NOP");
//        VM_spi_int_clr_addr  = 0x1;  //clear int
//        asm(  " NOP");
//        VM_spi_int_clr_addr  = 0x0;  //recover from clear
//        spi_int_clr_addr  = 0x1;  //clear int
//        asm(  " NOP");
//        spi_int_clr_addr  = 0x0;  //recover from clear
//	}
//
//
//	else if((hdlc_temp3 == 0x29)&&((target == 0x45)||(target == Own_Add)))//结束外部通信功能
//	{
//		hdlc_count7++;
//		start_output = 0;//禁止外部通信控制输出
//		wave_type = 0x04;				//外部输出认为是直流输出
//		wave_freq = 0;//频率初始化
//
//		/********* 新增1010 **********/
//		last_range = 0;		//保存上一次幅值
//		/********* 新增1010 **********/
//
//		wave_range = 0;//幅值初始化
//		output_en = 0;//复位输出标志位
////****************new code**************************//
//		rev_flag = 1;
////****************new code**************************//
//		for(i = 0;i<4;i++)
//		{
//			cur_data_ext[i].f_data = 0;		//初始化电流输出幅值信息数组
//			vol_data_ext[i].f_data = 0;//初始化电压输出幅值信息数组
//		}
//		for(i = 0;i<19;i++)//回传数组清零
//		{
//			trans_data_out_vol[i] = 0;
//			trans_data_out_cur[i] = 0;
//			need_vol_array[i] = 0;
//			need_cur_array[i] = 0;
//		}
//		VM_spi_ctrl_addr=0x0;//禁止电压测量模块产生中断
//		spi_ctrl_addr=0x1;//使能电流测量模块产生中断，为默认状态
//	    DA_Dout_low_Addr =0x0000;
//	    DA_Dout_high_Addr=0x0000;
//		DA_OE_Addr=0x0;    //open DA out
//        VM_spi_int_clr_addr  = 0x1;  //clear int
//        asm(  " NOP");
//        VM_spi_int_clr_addr  = 0x0;  //recover from clear
//        spi_int_clr_addr  = 0x1;  //clear int
//        asm(  " NOP");
//        spi_int_clr_addr  = 0x0;  //recover from clear
//	}
//	else if(hdlc_temp3 == 0x23)		//外部电流数据输出，同时上传电流数据
//	{
//		hdlc_count8++;
//		if(start_output == 1)//若外部通信使能
//		{
//			wave_type = 0x04;//外部输出只输出直流
//			for(i = 0;i<4;i++)
//			{
//				for(j = 0;j<4;j++)
//				{
//					cur_data_ext[i].c_data[j] = HDLC_rx_data_out_addr & 0xFF;//接收从外部发过来要求输出的数据，全部接收，但是仅输出直接对应通道的数据
//				}
//			}
//
//		/********* 新增1010 **********/
//			last_range = wave_range ;		//保存上一次幅值
//		/********* 新增1010 **********/
//
//		//****************new code**************************//
//				rev_flag = 1;
//		//****************new code**************************//
//
//			wave_range = cur_data_ext[Own_Add-0x41].f_data * CurScale;//对当前电路板对应的通道数据转化为幅值
//			datai_to_da_pid = wave_range;//初始化输出
//			pid_init(&pid_str,0,wave_range,Kp,Ki,Kd);//pid初始化
//			VM_spi_ctrl_addr=0x0;    //禁止电压测量模块产生中断
//			spi_ctrl_addr=0x1;//使能电流测量模块产生中断
//			DA_OE_Addr=0x0;    //open DA out
//			output_en = 1;//使能输出标志位
//		//******************new code by web 10 30********************//
//			if(NoLoad == 1)//若为空载，则不输出
//			{
//				output_en = 0;
//			}
//
//			if(target == Own_Add)			//如果对应通道选中，那么回传采到的数据
//			{
//			//	need_cur_flag = 1;
//				need_cur_array[0]=0x53;			//回传数据第一个字节为外部计算机地址
//				need_cur_array[1]=Own_Add;			//回传数据第二个字节为当前电路板地址
//
//				need_cur_array[2] = 0x23;				//回传数据第三个字节为当前工作模式
//				HDLC_transmit(need_cur_array,19);//发送回传数据
//			}
//	        VM_spi_int_clr_addr  = 0x1;  //clear int
//	  //      for(i=1;i<100;i++);
//	        asm(  " NOP");
//	        VM_spi_int_clr_addr  = 0x0;  //recover from clear
//	        spi_int_clr_addr  = 0x1;  //clear int
//	 //       for(i=1;i<100;i++);
//	        asm(  " NOP");
//	        spi_int_clr_addr  = 0x0;  //recover from clear
//		}
//	}
//	else if(hdlc_temp3 == 0x24)		//外部电压数据输出
//	{
//		hdlc_count9++;
//		if(start_output == 1)//若外部通信使能
//		{
//			wave_type = 0x04;//输出直流电压
//			for(i = 0;i<4;i++)
//			{
//				for(j = 0;j<4;j++)
//				{
//					vol_data_ext[i].c_data[j] = HDLC_rx_data_out_addr & 0xFF;//接收从外部发过来要求输出的数据，全部接收，但是仅输出直接对应通道的数据
//				}
//			}
//
//		/********* 新增1010 **********/
//			last_range = wave_range;		//保存上一次幅值
//		/********* 新增1010 **********/
//
//		rev_flag = 1;
//			wave_range =(vol_data_ext[Own_Add-0x41].f_data);//对当前电路板对应的通道数据转化为幅值
//			datav_to_da_pid = wave_range;//初始化pid输出
//			pid_init(&pid_str,0,wave_range,Kp,Ki,Kd);//pid初始化
//			//****************new code by web 1030**************************//
//
//			spi_ctrl_addr=0x0;//禁止电流测量模块产生中断
//			VM_spi_ctrl_addr=0x1;//使能电压测量模块产生中断
//			DA_OE_Addr=0x0;    //open DA out
//			output_en = 1;//使能输出标志位
//		//******************new code by web 10 30********************//
//			if(NoLoad == 1)//若为空载，则不输出
//			{
//				output_en = 0;
//			}
//			OutVol = 1;
//			if(target == Own_Add)			//如果对应通道选中，那么回传采到的数据
//			{
//				need_vol_flag = 1;
//				need_vol_array[0]=0x53;	//回传数据第一个字节为外部计算机地址
//				need_vol_array[1]=Own_Add;	//回传数据第二个字节为当前地址
//				need_vol_array[2] = 0x24;//回传数据第三个字节为当前工作模式
//				HDLC_transmit(need_vol_array,19);//发送回传数据
//			}
//	        VM_spi_int_clr_addr  = 0x1;  //clear int
//	        asm(  " NOP");
//	        VM_spi_int_clr_addr  = 0x0;  //recover from clear
//	        spi_int_clr_addr  = 0x1;  //clear int
//	        asm(  " NOP");
//	        spi_int_clr_addr  = 0x0;  //recover from clear
//
//		}
//	}
//	else if((hdlc_temp3 == 0x25)&&(target == Own_Add))		//外部要求回传电流数据
//	{
//		hdlc_count10++;
//		back_cur_flag = 1;
//		need_cur_array[0]=0x53;//回传数据第一个字节为外部计算机地址
//		need_cur_array[1]=Own_Add;//回传数据第二个字节为当前地址
//		need_cur_array[2] = 0x25;//回传数据第三个字节为当前工作模式
//		HDLC_transmit(need_cur_array,19);
//	}
//	else if((hdlc_temp3 == 0x26)&&(target == Own_Add))		//外部要求回传电压数据
//	{
//		hdlc_count11++;
//		back_vol_flag = 1;
//		need_vol_array[0]=0x53;//回传数据第一个字节为外部计算机地址
//		need_vol_array[1]=Own_Add;//回传数据第二个字节为当前地址
//		need_vol_array[2] = 0x26;//回传数据第三个字节为当前工作模式
//		HDLC_transmit(need_vol_array,19);
//	}
//	else
//	{
//		hdlc_count12++;
//		protocol_error = 1;
//	}
//}
