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
//extern float wave_freq;					//����Ƶ��
//extern float wave_range;					//���η�ֵ
//extern float wave_range_c;			//��������ֵת��Ϊ��ѹ��ֵ
//
//extern int wave_type;				//�������Ĭ������̶�ֵ
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
//extern unsigned char trans_data[407];		//�����ڲ���������
//
//extern float adi_out_average,adv_out_average;	//8·AD�������ݵ�ƽ��ֵ
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
//float datai_to_da = 0;		//��DA�����ֵ,����
//float datav_to_da = 0;		//��DA�����ֵ����ѹ
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
//union data_buffer cur_data_ext[4];		//4��ͨ�������ݶ��ս���
//union data_buffer vol_data_ext[4];
//
//union data_buffer cur_data_output[4];		//4�����ڵ����ݷ��ͳ�ȥ
//union data_buffer vol_data_output[4];
//unsigned char start_output = 0;
//extern int NoLoad ;
//unsigned char OutVol = 0;
//unsigned int back_cur_flag = 0;
//unsigned int back_vol_flag=0;
//unsigned char need_vol_flag = 0;
//extern unsigned char trans_data_out_cur[19];	//���ڶ���ش�����
//extern unsigned char trans_data_out_vol[19];	//���ڶ���ش�����
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
//	    if(	VM_spi_rx_flag_addr==0x1)//�ж��Ƿ�Ϊ��ѹ�����ж�
//	    {
////	       GPIOBankIntDisable(SOC_GPIO_0_REGS, 0);  //disable GPIOBank 0
//	       unsigned int j,k;
////	       gpiointFlag = 2;
//
//	       IntEventClear(SYS_INT_GPIO_B0INT);       //���ж��¼�
//	       GPIOPinIntClear(SOC_GPIO_0_REGS, 31);//��GPIO�ж�
//
//	       unsigned short int VM_spi_temp_high,VM_spi_temp_low;
//	       VM_spi_temp_high = VM_spi_rx_high_addr ;
//	       VM_spi_temp_low  = VM_spi_rx_low_addr  ;
//	       VM_SPI_value     = VM_spi_temp_high*65536 +  VM_spi_temp_low ;//��ȡ��ѹ��������ͨ��spi����������
//	       VM_SPI_value_f   = -VM_SPI_value/1000000.0*1.0234;//ת��Ϊ��λΪV�ĵ�ѹ����
//	       adv_out_average  = VM_SPI_value_f;
//
//	       float wwwv;					//������Ҳ�ʱ�Ħ�
//
//	   	   if(output_en)//�ж������־λ
//	   		   {
//	   			   switch(wave_type)//�ж��������
//	   			   {
//	   				case WAVE_SIN ://������Ҳ�
//	   					wwwv = 2 * PI * wave_freq;//w=2*pi*freq
//	   					datav_to_da = wave_range*sin(wwwv * wave_cnt / 64000);//���ƽ���Ϊ64kHzʱ����ʱ�̵�����趨ֵ
//	   					if(wave_cnt< (64000/ wave_freq-1))//ѭ�����������
//	   						wave_cnt++;
//	   					else
//	   						wave_cnt=0;
//	   					asm(    " NOP");
//
//	   					break;
//
//	   				case WAVE_FIXED ://�����ֵ
//						if(rev_flag == 1)
//						{
//							rev_flag = 0;
//							chazhi_cnt = 0;
//							step_range_v = wave_range - last_range;//�������֮��ı仯��
//						}
//
//						chazhi_cnt++;
//						datav_to_da = last_range+ chazhi_cnt* step_range_v/ 4;//���Ĵβ�ֵ���
//
//				//**********new code by web 1030**************//
//						if(chazhi_cnt > 3 )
//						{
//							chazhi_cnt = 3;
//						}
//
//   					    break;
//
//	   				case WAVE_RECTANG ://����
//	   					datav_to_da = wave_range * ((wave_cnt / ((int)(16000/wave_freq))) % 2);//����ʱ�̵����ֵ
//
//	   					if(wave_cnt< (64000/ wave_freq-1))//ѭ�����������
//	   						wave_cnt++;
//	   					else
//	   						wave_cnt=0;
//
//	   					asm(    " NOP");
//	   					break;
//
//	   				case WAVE_TRI ://������ǲ�
//	   					datav_to_da = wave_range / 64000 * wave_freq * (wave_cnt%((int)(64000 / wave_freq)));//����ʱ�̵����ֵ
//
//	   					if(wave_cnt< (64000/ wave_freq-1))//ѭ�����������
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
//	   				DA_DATA = (int)(datav_to_da * DAV_CONV);//ת��Ϊ���ֵ
//
//	   			    DA_Dout_low_Addr = DA_DATA & 0x0000FFFF;
//	   			    DA_Dout_high_Addr = (DA_DATA>>16) & 0x0000FFFF;//ת��ΪDA����Ĵ�����ֵ
//
//	           }
//			up_data.uni_float = adv_out_average;//����ѹ����ֵ�ϴ�
//			if(up_data.uni_float > 6)
//			{
//				asm("	NOP");
//			}
//				//**********************0.0625ms���»ش�ָ�������******************************//
//				//�����ⲿͨѶʱ�ش�������
//			    //need_vol_array��19���ֽڣ�0~2�ֽ���������ش����ݵĵ�ַ��Ϣ�ģ�3~18�ֽڴ洢4������ֵ��ÿ������ֵռ4���ֽ�
//			if(out_cnt_v%4 == 1)//4�����ƽ��ĸ���һ�Σ���0.0625ms���»ش�����
//			{
//				for(j = 0;j<3;j++)//����������ǰ��4���ֽڣ��ճ�����ĸ��ֽ����ڴ洢�µ�����
//				{
//					need_vol_array[3 + j * 4] = need_vol_array[3 + (j+1) * 4];
//					need_vol_array[4 + j * 4] = need_vol_array[4 + (j+1) * 4];
//					need_vol_array[5 + j * 4] = need_vol_array[5 + (j+1) * 4];
//					need_vol_array[6 + j * 4] = need_vol_array[6 + (j+1) * 4];
//				}
//				need_vol_array[15] = up_data.uni_char[0];
//				need_vol_array[16] = up_data.uni_char[1];
//				need_vol_array[17] = up_data.uni_char[2];
//				need_vol_array[18] = up_data.uni_char[3];//�洢�µĲ�������
//			}
//			out_cnt_v++;
//			if(out_cnt_v>15)
//			out_cnt_v = 0;
//		//**********************0.03125���»ش�ָ�������,3.125ms�Իش������������******//
//
//		//******************��λ��Ҫ��******************//
//		   if(data_prepare==1)//�ж���λ���Ƿ�Ҫ��
//		   {
//			   trans_data[2] = 0x35;//��λ��Ҫ��ش���ѹ����ʱ��Ӧ��ģʽΪ0x35
//			   if(updata_cnt%2 == 1)//���ݸ���Ƶ��Ϊ32000Hz
//			    {
//				    for(k=0;k<4;k++)
//				    {
//	  				trans_data[(updata_cnt-1)*2+k+3] = up_data.uni_char[k];//��trans_data[3]��ʼ�洢���ݣ�ÿ�δ洢4���ֽڣ��൱��һ������ֵ
//				    }
//			    }
//			    updata_cnt++;
//			  if(updata_cnt >= 200)//��λ��ÿ��Ҫ���͸���100��float
//			   {
//				updata_cnt=0;
//				data_prepare = 0;
//			   }
//		   }
//		   VM_spi_int_clr_addr  = 0x1;  //���жϱ�־λ
//		   asm(  " NOP");
//           VM_spi_int_clr_addr  = 0x0;  //�������ж�
//	    }
//	    else if(spi_rx_flag_addr  == 0x1)//�ж��Ƿ�Ϊ��������
//		{
//		   	float wwwi;					//������Ҳ�ʱ�Ħ�
//		   	unsigned int j,k;
//
////	        gpiointFlag = 1;
//	        IntEventClear(SYS_INT_GPIO_B1INT);       //���ж��¼�
//	        GPIOPinIntClear(SOC_GPIO_0_REGS, 31);//��GPIO�ж�
//
//	        unsigned short int spi_temp_high,spi_temp_low;
//	        float err_1;
//	        spi_temp_high = spi_rx_high_addr ;
//	        spi_temp_low  = spi_rx_low_addr  ;
//	        SPI_value     = (spi_temp_high<<16) +  spi_temp_low ;//��spi���������ת��Ϊint��
//	        SPI_value_f   = -SPI_value/1000000.0;   //������ת��Ϊfloat�ͣ���λΪmA����·���ԭ��Ҫȡ��
//	        adi_out_average  = SPI_value_f;
//	        if(iii < 40000)//�洢40000���������ݣ����ڲ��Է������ݾ���ˮƽ��Ϊ���Դ��룬����ȥ��
//	        {
//	        	test[iii]=adi_out_average;
//	        	iii++;
//	        }
//	        wave_range_c=wave_range;//�������ֵ
//	        last_range_i=last_range;//��һ���������ֵ
//
//	    	if(output_en)//�ж������־λ
//	    		{
//	    			switch(wave_type)//�ж��������
//	    			{
//	    				case WAVE_SIN ://����
//	    					wwwi = 2 * PI * wave_freq;//w=2*pi*freq
//	    					datai_to_da = wave_range_c*sin(wwwi * wave_cnt / 64000);//���ƽ���Ϊ64kHzʱ����ʱ�̵�����趨ֵ
//
//	    					if(wave_cnt< (64000/ wave_freq-1))//ѭ�����������
//	    						wave_cnt++;
//	    					else
//	    						wave_cnt=0;
//		   					asm(    " NOP");
//
//	    					break;
//
//	    				case WAVE_FIXED ://�����ֵ
//
//							if(rev_flag == 1)
//							{
//								rev_flag = 0;
//								chazhi_cnt = 0;
//								step_range_i = wave_range_c - last_range_i;//�������֮��ı仯��
//							}
//
//							chazhi_cnt++;
//							datai_to_da = last_range_i+ chazhi_cnt* step_range_i/ 4;//���Ĵβ�ֵ���
//							if(chazhi_cnt > 3)
//							{
//								chazhi_cnt = 3;
//							}
//	    					break;
//
//	    				case WAVE_RECTANG ://����
//	    					datai_to_da = wave_range_c * ((wave_cnt / ((int)(16000/wave_freq))) % 2);//����ʱ�̵����ֵ
//
//	    					if(wave_cnt< (64000/ wave_freq-1))//ѭ�����������
//	    						wave_cnt++;
//	    					else
//	    						wave_cnt=0;
//		   					asm(    " NOP");
//
//	    					break;
//	    				case WAVE_TRI ://������ǲ�
//	    					datai_to_da = wave_range_c / 64000 * wave_freq * (wave_cnt%((int)(64000 / wave_freq)));//����ʱ�̵����ֵ
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
//				if((adi_out_average-datai_to_da < 0.1 )&& (adi_out_average-datai_to_da > -0.1 ))//���ֵ���趨ֵ֮������0.1V���ڣ�����pid����
//				{
//					pp->pv = adi_out_average;//��ǰ����ֵ
//					pp->sp = datai_to_da;//��ǰ�趨ֵ
//					err_1=(datai_to_da-adi_out_average)*1000;//����1000��
//					datai_to_da_pid = datai_to_da_pid + pid_calc(&pid_str);//����PID�������м���
//				}
//
//
//
//	   				DA_DATA = (int)(datai_to_da * DAI_CONV);//����趨ֵ��û�����pid������ֵ��Ϊ�������
//	   			    DA_Dout_low_Addr = DA_DATA & 0x0000FFFF;
//	   			    DA_Dout_high_Addr = (DA_DATA>>16) & 0x0000FFFF;//ת��ΪDA����Ĵ�����ֵ
//
//		        }
//			    up_data.uni_float = adi_out_average/CurScale;//����������ֵ�ϴ�
//		//**********************0.0625ms���»ش�ָ�������******************************//
//		//�����ⲿͨѶʱ�ش�������
//		//need_vol_array��19���ֽڣ�0~2�ֽ���������ش����ݵĵ�ַ��Ϣ�ģ�3~18�ֽڴ洢4������ֵ��ÿ������ֵռ4���ֽ�
//			    if(out_cnt_i%4 == 1)//4�����ƽ��ĸ���һ�Σ���0.0625ms���»ش�����
//		        	{
//				       for(j = 0;j<3;j++)//����������ǰ��4���ֽڣ��ճ�����ĸ��ֽ����ڴ洢�µ�����
//				       {
//					      need_cur_array[3 + j * 4] = need_cur_array[3 + (j+1) * 4];
//					      need_cur_array[4 + j * 4] = need_cur_array[4 + (j+1) * 4];
//					      need_cur_array[5 + j * 4] = need_cur_array[5 + (j+1) * 4];
//					      need_cur_array[6 + j * 4] = need_cur_array[6 + (j+1) * 4];
//			         	}
//				        need_cur_array[15] = up_data.uni_char[0];
//				        need_cur_array[16] = up_data.uni_char[1];
//				        need_cur_array[17] = up_data.uni_char[2];
//				        need_cur_array[18] = up_data.uni_char[3];//�洢�µĲ�������
//			       }
//			    out_cnt_i++;
//			    if(out_cnt_i>15)
//			    out_cnt_i = 0;
//		//***************0.03125���»ش�ָ�������,3.125ms�Իش������������*******************//
//		//******************��λ��Ҫ��******************//
//
//		       if(data_prepare==1)						//��λ��Ҫһ����������һ��
//	           	{
//			       trans_data[2] = 0x34;//��λ��Ҫ��ش���ѹ����ʱ��Ӧ��ģʽΪ0x35
//		           if(updata_cnt%2 == 1)				//���ݸ���Ƶ��Ϊ32000Hz
//		         	{
//				         for(k=0;k<4;k++)
//				         {
//		  			        trans_data[(updata_cnt-1)*2+k+3] = up_data.uni_char[k];//��trans_data[3]��ʼ�洢���ݣ�ÿ�δ洢4���ֽڣ��൱��һ������ֵ�����洢100������ֵ
//				         }
//			        }
//			       updata_cnt++;
//		       	   if(updata_cnt >= 200)//��λ��ÿ��Ҫ���͸���100��float
//			       {
//				     updata_cnt=0;
//				     data_prepare = 0;
//			       }
//	           	}
//
//	        spi_int_clr_addr  = 0x1;   //���жϱ�־λ
//	        asm(  " NOP");
//            spi_int_clr_addr  = 0x0;  //�������ж�
//		}
//	    else
//	    	asm(  " NOP");
//}
//void HDLC_and_uart_isr()
//{
//
//	int i;
//	if(INT_STATUSA & 0x01 == 0x01)   //�ж��Ƿ�ΪHDLC�ж�
//	{
//    unsigned int hdlc_byte_num;
//    unsigned int hdlc_byte_temp;
//
//    IntEventClear(SYS_INT_GPIO_B1INT);       //���ж��¼�
//
//	HDLC_rx_ctrl_addr &= ~HDLC_Rx_int_enable;//��ֹ���������ж�
//	hdlc_byte_temp = HDLC_rx_status_addr & 0x01ff;
//	hdlc_byte_num = hdlc_byte_temp>>1;      //���յ������ݸ���
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
//	hdlc_temp1 = HDLC_rx_data_out_addr & 0xFF ;//���յ��ĵ�һ���ֽ�
//	hdlc_temp2 = HDLC_rx_data_out_addr & 0xFF ;//���յ��ĵڶ����ֽ�
//	if(hdlc_temp2 == 0x52)//�ڶ����ֽ�ΪԴ��ַ����Ϊ0x52������Ϊ��λ��������������
//	{
//		if((hdlc_temp1 == Own_Add)||(hdlc_temp1 == 0x45))//��һ����ַΪĿ���ַ�����뵱ǰ��·���ַ��ͬ��Ϊ0x45����ʾѡ�����е�·�壩��������ڲ�ͨ��
//		{
//			hdlc_count2++;
//			InterCommunication();//�ڲ�ͨ�ź���
//		}
//		else
//			hdlc_count3++;
//	}
//	else if(hdlc_temp2 == 0x53)//��Ϊ0x53������Ϊ�ⲿ�����������������
//	{
//		hdlc_count4++;
//		ExterCommunication(hdlc_temp1);//�����ⲿͨ�ź������β�Ϊ���յ��ĵ�һ���ֽ�
//	}
//	else
//	{
//		protocol_error = 1;//���������������������ȴ������HDLC�жϣ�˵�����쳣
//		hdlc_count5++;
//	}
//
//    HDLC_rx_ctrl_addr=0x0;//HDLC��λ
//    asm("   NOP");
//    HDLC_rx_ctrl_addr=0x7;//��0λΪ��1������λ״̬��������1λΪ��1������ʹ��֡У�飬��2λΪ��1������ʹ�ܽ����ж�
//    asm("   NOP");
//	HDLC_clr_int_addr=0x1;//���ж�
//    asm("   NOP");
//    HDLC_clr_int_addr=0x0;//�������ж�״̬
//    asm("   NOP");
//	}
//	else if(uart_int_flag_Addr==1)//�ж��Ƿ�ΪUART�жϣ����ڽ����¶�
//	     {
////		        gpiointFlag = 3;
//		        IntEventClear(SYS_INT_GPIO_B0INT);       //���ж��¼�
//		        GPIOPinIntClear(SOC_GPIO_0_REGS, 15);//��GPIO�ж�
//
//	//	  flame=uart_Rxd_Addr;
//	//    while(uart_Rxd_Addr!=0xAA)
//	//    {
//	//       i=1;
//	//    }
//		      //  int temp_num;
//		        temp_num = (Uart_status_Addr & 0xF000)/4096;//UART���յ������ݸ���
//		        asm("	NOP");
//		        test_count=0;
//		        if(temp_num>=9)//���յ������ݴ���9
//		        {
//		        	flame=uart_Rxd_Addr;//��һ���ֽ�Ϊ֡ͷ��Ϊ0xAA���������ȷ
//		        	if(flame == 0xAA)//֡ͷ��Ϊ0xAA�����������
//		        	{
//						temp[0]=uart_Rxd_Addr;
//						temp[1]=uart_Rxd_Addr;
//						temp[2]=uart_Rxd_Addr;
//						temp[3]=uart_Rxd_Addr;
//						temp[4]=uart_Rxd_Addr;
//						temp[5]=uart_Rxd_Addr;
//						temp[6]=uart_Rxd_Addr;
//						temp[7]=uart_Rxd_Addr;//���ս�������8������
//						uart_temp1=(temp[3]<<24)+(temp[2]<<16)+(temp[1]<<8)+temp[0];//��һ���¶�ֵ
//						uart_temp2=(temp[7]<<24)+(temp[6]<<16)+(temp[5]<<8)+temp[4];//�ڶ����¶�ֵ
//						uart_temp_old = uart_temp;
//						uart_temp=uart_temp1/1000.0;
//						uart_temp_1=uart_temp2/1000.0;//���¶����ݴ洢
//
//						uart_rst_Addr=1;//UART��λ
//						//	asm("	NOP");
//						for(i=0;i<600;i++);
//						uart_rst_Addr=0;//ֹͣUART��λ
//
//		        	}
//
//		        }
//		        else
//		        {
//		       	  asm("	 NOP");
//		        }
//
//			uart_clr_int_Addr=1;//���ж�
//			asm("	NOP");
//			uart_clr_int_Addr=0;//�������ж�
//		    for(i=0;i<6;i++);
//	        LED=~LED;
//	    }
//	else
//	{
//		asm("	NOP");
//	}
//}

//�ڲ�ͨ�ź���
//void InterCommunication()
//{
//	unsigned int i,j;
//    unsigned char hdlc_temp3;
//    hdlc_temp3=HDLC_rx_data_out_addr & 0xFF;//��ȡHDLC�������ֽ�
//    //�������ֽڱ�ʾ����λ��Ҫ���·��Ĺ���ģʽ
//	if(hdlc_temp3 == 0x31)				//�����������
//	{
//		type_flag=current_out;
//		cur_wave.wave_style = HDLC_rx_data_out_addr & 0xFF;//���ĸ��ֽڱ�ʾ�����������
//		wave_type = cur_wave.wave_style;	//�����������
//		for(i=0;i<4;i++)
//		{
//			cur_wave.fre_data.c_data[i] = HDLC_rx_data_out_addr & 0xFF;//��5/6/7/8���ֽڱ�ʾƵ����Ϣ
//		}
//		wave_freq = cur_wave.fre_data.f_data;	//������һ����ͬ��ṹ��ת��Ϊfloat�͵�Ƶ����Ϣ
//		for(j=0;j<4;j++)
//		{
//			cur_wave.amp_data.c_data[j] = HDLC_rx_data_out_addr & 0xFF;//��9,10,11,12���ֽڱ�ʾ��ֵ��Ϣ
//		}
//
//
//		wave_range = cur_wave.amp_data.f_data * CurScale;	//������һ����ͬ��ṹ��ת��Ϊfloat�͵ķ�ֵ��Ϣ
//
//
//		last_range = wave_range;		//������һ�η�ֵ
//		rev_flag = 1;
//		//******************new code by web 10 29********************//
//
//	    DA_OE_Addr=0x0;    //��DA���
//		cur_output_en = 1;//Ӧ��û��ʲô�ã� �����ط���û���õ�
//		output_en=0x1;//ʹ�������־λ
//		if(NoLoad == 1)//���Ϊ���أ�������������
//		{
//			output_en = 0;
//		}
//		VM_spi_ctrl_addr=0x0;//��ֹ��ѹ����ģ������ж�
//		spi_ctrl_addr=0x1;//ʹ�ܵ�������ģ������ж�
//        VM_spi_int_clr_addr  = 0x1;  //���ѹ����ģ���жϱ�־λ
//        asm(  " NOP");
//        VM_spi_int_clr_addr  = 0x0;  //�������ж�״̬
//        spi_int_clr_addr  = 0x1;  //���������ģ���жϱ�־λ
//        asm(  " NOP");
//        spi_int_clr_addr  = 0x0;  //�������ж�״̬
//
//
//	}
//	else if(hdlc_temp3 == 0x32)			//�����ѹ����
//	{
//		type_flag=voltage_out;//�����ѹģʽ
//		vol_wave.wave_style = HDLC_rx_data_out_addr & 0xFF;//��ѹ�������
//		wave_type = vol_wave.wave_style;
//		for(i=0;i<4;i++)
//		{
//			vol_wave.fre_data.c_data[i] = HDLC_rx_data_out_addr & 0xFF;////��5/6/7/8���ֽڱ�ʾƵ����Ϣ
//		}
//		wave_freq = vol_wave.fre_data.f_data;	//������һ����ͬ��ṹ��ת��Ϊfloat�͵�Ƶ����Ϣ
//		for(j=0;j<4;j++)
//		{
//			vol_wave.amp_data.c_data[j] = HDLC_rx_data_out_addr & 0xFF;//��9,10,11,12���ֽڱ�ʾ��ֵ��Ϣ
//		}
//		wave_range = vol_wave.amp_data.f_data ;//������һ����ͬ��ṹ��ת��Ϊfloat�͵ķ�ֵ��Ϣ
//		last_range = wave_range;//������һ�ε����ֵ
//		rev_flag = 1;
//		//******************new code by web 10 30********************//
//	    DA_OE_Addr=0x0;    //��DA���
//		vol_output_en = 1;//ʹ�ܵ�ѹ�����Ҳû���õ�
//		output_en=0x1;//ʹ�������־
//		if(NoLoad == 1)//���û�и��أ����������
//		{
//			output_en = 0;
//		}
//
//		spi_ctrl_addr=0x0;     //��ֹ��������ģ������ж�
//		VM_spi_ctrl_addr=0x1;//ʹ�ܵ�ѹ����ģ������ж�
//        spi_int_clr_addr  = 0x1;  //����������жϱ�־λ
//        asm(  " NOP");
//        spi_int_clr_addr  = 0x0;  //�������ж�
//        VM_spi_int_clr_addr  = 0x1;  //���ѹ�����жϱ�־λ
//        asm(  " NOP");
//        VM_spi_int_clr_addr  = 0x0;  //�������ж�
//
//
//	}
//
//	else if(hdlc_temp3 == 0x33)			//׼����ǰ����״̬�µ�����100��float
//	{
//		data_prepare = 1;
//	}
//	else if(hdlc_temp3 == 0x34)			//Ҫ��ش���������100��float�Լ�2��byte���¶�����
//	{
//		cur_measure = 1;
//		vol_measure = 0;
//		VM_spi_ctrl_addr=0x0;//��ֹ��ѹ����ģ������ж�
//	    spi_ctrl_addr=0x1;//ʹ�ܵ�������ģ������ж�
//		trans_data[0] = 0x52;//�������ݵĵ�һ���ֽ�Ϊ��λ���ĵ�ַ
//		trans_data[1] = Own_Add;//�������ݵĵڶ����ֽ�Ϊ��ǰ��·��ĵ�ַ
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
//	else if(hdlc_temp3 == 0x35)			//Ҫ��ش���ѹ����100��float�Լ�2��byte���¶�����
//	{
//		vol_measure = 1;
//		cur_measure = 0;
//	    spi_ctrl_addr=0x0;//��ֹ��������ģ������ж�
//		VM_spi_ctrl_addr=0x1;//ʹ�ܵ�ѹ����ģ������ж�
//		trans_data[0] = 0x52;//�������ݵĵ�һ���ֽ�Ϊ��λ���ĵ�ַ
//		trans_data[1] = Own_Add;//�������ݵĵڶ����ֽ�Ϊ��ǰ��·��ĵ�ַ
//
//        spi_int_clr_addr  = 0x1;  //clear int
//        asm(  " NOP");
//        spi_int_clr_addr  = 0x0;  //recover from clear
//        VM_spi_int_clr_addr  = 0x1;  //clear int
//        asm(  " NOP");
//        VM_spi_int_clr_addr  = 0x0;  //recover from clear
//	}
//	else if(hdlc_temp3 == 0x39)			//ֹͣ���
//	{
//		DA_OE_Addr=0x1;    //close DA out
//		cur_measure = 0;
//		vol_measure = 0;
//		data_prepare = 0;//���ٸ��»ش�����
//		output_en = 0;//��λ�����־λ
//	    DA_Dout_low_Addr =0x0000;
//	    DA_Dout_high_Addr=0x0000;//DA���0
//	}
//	else if(hdlc_temp3 == 0xFF)			//ϵͳ��ʼ��
//	{
//		DA_OE_Addr=0x1;    //close DA out
//		vol_output_en = 0;
//		cur_output_en = 0;
//		VM_spi_ctrl_addr=0x0;//��ֹ��������ģ������ж�
//	    spi_ctrl_addr=0x1;//��ֹ��������ģ������ж�
//
//		wave_type = WAVE_FIXED;//�������Ϊֱ��
//		wave_freq = 0;//Ƶ��Ϊ0
//
//		/********* ����1010 **********/
//		last_range = 0;		//������һ�η�ֵ
//		/********* ����1010 **********/
//
//		wave_range = 0;
//	    DA_Dout_low_Addr =0x0000;
//	    DA_Dout_high_Addr=0x0000;
//		start_output = 0;//��ֹ���
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
////�ⲿͨ�ź���
//void ExterCommunication(unsigned char target)
//{
//
//	int i,j,k;
//    unsigned char hdlc_temp3;
//    hdlc_temp3=HDLC_rx_data_out_addr & 0xFF;//�������ֽ�Ϊ����ģʽ
//	if((hdlc_temp3 == 0x21)&&((target == 0x45)||(target == Own_Add)))//��ʼ�ⲿͨѶ�������
//	{
//		hdlc_count6++;
//		start_output = 1;//ʹ���ⲿͨ�ſ������
//		wave_type = WAVE_FIXED;			//�ⲿ�����Ϊ��ֱ�����
//		wave_freq = 0;//Ƶ��Ϊ0
//
//		/********* ����1010 **********/
//		last_range = 0;		//������һ�η�ֵ
//		/********* ����1010 **********/
//
//		wave_range = 0;//Ƶ��Ĭ��Ϊ0
//		output_en = 1;//ʹ�������־λ
//
//		rev_flag = 1;
//
//		for(i = 0;i<4;i++)
//		{
//			cur_data_ext[i].f_data = 0;	//��ʼ���������ֵ��Ϣ����
//			vol_data_ext[i].f_data = 0;//��ʼ����ѹ�����ֵ��Ϣ����
//		}
//		for(i = 0;i<19;i++)				//������������
//		{
//			trans_data_out_vol[i] = 0;
//			trans_data_out_cur[i] = 0;
//			need_vol_array[i] = 0;
//			need_cur_array[i] = 0;
//		}
//
//	    DA_Dout_low_Addr =0x0000;
//	    DA_Dout_high_Addr=0x0000;//DA���0
//		DA_OE_Addr=0x0;    //open DA out
//
//
//		VM_spi_ctrl_addr=0x0;//��ֹ��ѹ����ģ������ж�
//		spi_ctrl_addr=0x1;//ʹ�ܵ�������ģ������жϣ�ΪĬ��״̬
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
//	else if((hdlc_temp3 == 0x29)&&((target == 0x45)||(target == Own_Add)))//�����ⲿͨ�Ź���
//	{
//		hdlc_count7++;
//		start_output = 0;//��ֹ�ⲿͨ�ſ������
//		wave_type = 0x04;				//�ⲿ�����Ϊ��ֱ�����
//		wave_freq = 0;//Ƶ�ʳ�ʼ��
//
//		/********* ����1010 **********/
//		last_range = 0;		//������һ�η�ֵ
//		/********* ����1010 **********/
//
//		wave_range = 0;//��ֵ��ʼ��
//		output_en = 0;//��λ�����־λ
////****************new code**************************//
//		rev_flag = 1;
////****************new code**************************//
//		for(i = 0;i<4;i++)
//		{
//			cur_data_ext[i].f_data = 0;		//��ʼ�����������ֵ��Ϣ����
//			vol_data_ext[i].f_data = 0;//��ʼ����ѹ�����ֵ��Ϣ����
//		}
//		for(i = 0;i<19;i++)//�ش���������
//		{
//			trans_data_out_vol[i] = 0;
//			trans_data_out_cur[i] = 0;
//			need_vol_array[i] = 0;
//			need_cur_array[i] = 0;
//		}
//		VM_spi_ctrl_addr=0x0;//��ֹ��ѹ����ģ������ж�
//		spi_ctrl_addr=0x1;//ʹ�ܵ�������ģ������жϣ�ΪĬ��״̬
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
//	else if(hdlc_temp3 == 0x23)		//�ⲿ�������������ͬʱ�ϴ���������
//	{
//		hdlc_count8++;
//		if(start_output == 1)//���ⲿͨ��ʹ��
//		{
//			wave_type = 0x04;//�ⲿ���ֻ���ֱ��
//			for(i = 0;i<4;i++)
//			{
//				for(j = 0;j<4;j++)
//				{
//					cur_data_ext[i].c_data[j] = HDLC_rx_data_out_addr & 0xFF;//���մ��ⲿ������Ҫ����������ݣ�ȫ�����գ����ǽ����ֱ�Ӷ�Ӧͨ��������
//				}
//			}
//
//		/********* ����1010 **********/
//			last_range = wave_range ;		//������һ�η�ֵ
//		/********* ����1010 **********/
//
//		//****************new code**************************//
//				rev_flag = 1;
//		//****************new code**************************//
//
//			wave_range = cur_data_ext[Own_Add-0x41].f_data * CurScale;//�Ե�ǰ��·���Ӧ��ͨ������ת��Ϊ��ֵ
//			datai_to_da_pid = wave_range;//��ʼ�����
//			pid_init(&pid_str,0,wave_range,Kp,Ki,Kd);//pid��ʼ��
//			VM_spi_ctrl_addr=0x0;    //��ֹ��ѹ����ģ������ж�
//			spi_ctrl_addr=0x1;//ʹ�ܵ�������ģ������ж�
//			DA_OE_Addr=0x0;    //open DA out
//			output_en = 1;//ʹ�������־λ
//		//******************new code by web 10 30********************//
//			if(NoLoad == 1)//��Ϊ���أ������
//			{
//				output_en = 0;
//			}
//
//			if(target == Own_Add)			//�����Ӧͨ��ѡ�У���ô�ش��ɵ�������
//			{
//			//	need_cur_flag = 1;
//				need_cur_array[0]=0x53;			//�ش����ݵ�һ���ֽ�Ϊ�ⲿ�������ַ
//				need_cur_array[1]=Own_Add;			//�ش����ݵڶ����ֽ�Ϊ��ǰ��·���ַ
//
//				need_cur_array[2] = 0x23;				//�ش����ݵ������ֽ�Ϊ��ǰ����ģʽ
//				HDLC_transmit(need_cur_array,19);//���ͻش�����
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
//	else if(hdlc_temp3 == 0x24)		//�ⲿ��ѹ�������
//	{
//		hdlc_count9++;
//		if(start_output == 1)//���ⲿͨ��ʹ��
//		{
//			wave_type = 0x04;//���ֱ����ѹ
//			for(i = 0;i<4;i++)
//			{
//				for(j = 0;j<4;j++)
//				{
//					vol_data_ext[i].c_data[j] = HDLC_rx_data_out_addr & 0xFF;//���մ��ⲿ������Ҫ����������ݣ�ȫ�����գ����ǽ����ֱ�Ӷ�Ӧͨ��������
//				}
//			}
//
//		/********* ����1010 **********/
//			last_range = wave_range;		//������һ�η�ֵ
//		/********* ����1010 **********/
//
//		rev_flag = 1;
//			wave_range =(vol_data_ext[Own_Add-0x41].f_data);//�Ե�ǰ��·���Ӧ��ͨ������ת��Ϊ��ֵ
//			datav_to_da_pid = wave_range;//��ʼ��pid���
//			pid_init(&pid_str,0,wave_range,Kp,Ki,Kd);//pid��ʼ��
//			//****************new code by web 1030**************************//
//
//			spi_ctrl_addr=0x0;//��ֹ��������ģ������ж�
//			VM_spi_ctrl_addr=0x1;//ʹ�ܵ�ѹ����ģ������ж�
//			DA_OE_Addr=0x0;    //open DA out
//			output_en = 1;//ʹ�������־λ
//		//******************new code by web 10 30********************//
//			if(NoLoad == 1)//��Ϊ���أ������
//			{
//				output_en = 0;
//			}
//			OutVol = 1;
//			if(target == Own_Add)			//�����Ӧͨ��ѡ�У���ô�ش��ɵ�������
//			{
//				need_vol_flag = 1;
//				need_vol_array[0]=0x53;	//�ش����ݵ�һ���ֽ�Ϊ�ⲿ�������ַ
//				need_vol_array[1]=Own_Add;	//�ش����ݵڶ����ֽ�Ϊ��ǰ��ַ
//				need_vol_array[2] = 0x24;//�ش����ݵ������ֽ�Ϊ��ǰ����ģʽ
//				HDLC_transmit(need_vol_array,19);//���ͻش�����
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
//	else if((hdlc_temp3 == 0x25)&&(target == Own_Add))		//�ⲿҪ��ش���������
//	{
//		hdlc_count10++;
//		back_cur_flag = 1;
//		need_cur_array[0]=0x53;//�ش����ݵ�һ���ֽ�Ϊ�ⲿ�������ַ
//		need_cur_array[1]=Own_Add;//�ش����ݵڶ����ֽ�Ϊ��ǰ��ַ
//		need_cur_array[2] = 0x25;//�ش����ݵ������ֽ�Ϊ��ǰ����ģʽ
//		HDLC_transmit(need_cur_array,19);
//	}
//	else if((hdlc_temp3 == 0x26)&&(target == Own_Add))		//�ⲿҪ��ش���ѹ����
//	{
//		hdlc_count11++;
//		back_vol_flag = 1;
//		need_vol_array[0]=0x53;//�ش����ݵ�һ���ֽ�Ϊ�ⲿ�������ַ
//		need_vol_array[1]=Own_Add;//�ش����ݵڶ����ֽ�Ϊ��ǰ��ַ
//		need_vol_array[2] = 0x26;//�ش����ݵ������ֽ�Ϊ��ǰ����ģʽ
//		HDLC_transmit(need_vol_array,19);
//	}
//	else
//	{
//		hdlc_count12++;
//		protocol_error = 1;
//	}
//}
