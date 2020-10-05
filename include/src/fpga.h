#ifndef OCEAN_FPGA_H
#define OCEAN_FPGA_H

#define EMIF(ADDR)              (*(unsigned short int *)ADDR)
#define EMIF_WRITE(a, b)      \
    do{                                        \
    }while(0);
#define	LED_CONFIG 				(0x62000000)
//DAc
    #define	DA_DATA_EN 				(0x62000004)
	#define	DA_DATA_H 			    (0x62000008)
    #define	DA_DATA_L 				(0x6200000C)
 	#define	DA_RST_EN 				(0x62000010)
//AD1281
	#define	AD_RST_EN 			    (0x62000014)
    #define	AD_SYNC_EN 				(0x62000018)
 	#define	AD_CMD_EN 				(0x6200001C)
	#define	AD_REG_WR 			    (0x62000020)
    #define	AD_DAT_RD 				(0x62000024)
 	#define	AD_COMMAND 				(0x62000028)
 	#define	AD_STATUS 				(0x6200002C)
//ad2500������ֱ�����ݣ�32λ
    #define	AD_2500(X,Y)  ((0x62000030+4*(2*X+Y)))
//�ж������ʹ��
	#define	INT_CLEAR  		        (0x62000058)
	#define	INT_EN  	    		(0x6200005C)
//DA��dsp���ƻ�fpga����
//	#define	DA_CONFIG_SEL  		    (0x62000060)
//������ѹģʽ
//	#define	DA_VI_SEL  	    		(0x62000064)

 //�ӵ�һͨ������1281ͨ��
	#define	 CHANNEL_SEL            (0x62000068)
//adͨ��ֱ������
	#define	 CHANNEL_DATA_H            (0x6200006C)
	#define	 CHANNEL_DATA_L            (0x62000070)
//��PIDǰ��adֵ���ۺ�64���ۼӣ��õ��������ȳ���64 2k���ʸ���
	#define	 AD_OUT_DATA(X)     (0x62000074+4*X)

//����ģ�鹦��
 #define	   CONTROL_BYPASS             (0x62000084)
//����ģ�鹦��
 #define          QDATA(X)     (0x62000088+4*X)
 #define          RMDATA(X)  (0x62000098+4*X)
//2500��1281����ϵ��--��ѹ
 #define          AD2500_PARAM_V(X,Y)  ((0x620000A8+4*(4*X+Y)))
 #define          AD1281_PARAM_V(X)     (0x620000F8+4*X)
//2500��1281����ϵ��--����
 #define          AD2500_PARAM_I(X,Y)  ((0x62000108+4*(4*X+Y)))
 #define          AD1281_PARAM_I(X)  (0x62000158+4*X)
//2500��1281ƫ��--��ѹ

 #define          AD2500_OFFSET_V(X,Y)  ((0x62000168+4*(4*X+Y)))
 #define          AD1281_OFFSET_V(X)  (0x620001B8+4*X)
//2500��1281ƫ��--����
 #define          AD2500_OFFSET_I(X,Y)  ((0x620001C8+4*(4*X+Y)))
 #define          AD1281_OFFSET_I(X)  (0x62000218+4*X)

//2500���üĴ���
 #define          AD_2500_CFG_EN            (0x62000258)
 #define          AD_2500_CFG_DIN           (0x6200025C)
//ѡ��dsp���ƣ�0  fpga���ƣ�1
 #define	 	  DA_CONFIG_SEL             (0x62000060)
//������ѹ�����л�    0������       1����ѹ
 #define	      DA_VI_SEL              	(0x62000064)
//DA�������ϵ����ƫ��
 #define          DA_FIX_BASE(X)  (0x62000278+4*X)
 #define          DA_OFFSET(X)     (0x62000288+4*X)
//�� "interface_da.h"

//�������ģʽѡ��
 #define          WAVE_SEL              (0x620002A8)
//�¶�
 #define          GET_TEMPER                (0x62000310)
 #define          SET_TEMPER                (0x62000314)
//�� "interface_da.h" ��ز���
 #define          DESIGN_YEAR               (0x62000318)
 #define          DESIGN_DATE               (0x6200031C)
 #define          DESIGN_VERSION            (0x62000320)
//�����ںϱ���ϵ���Լ�ͨ����ѡ��
#define           FUSION_CH_STATUS   (0x62000324)
#define           FUSION_PARAM(X,Y)  ((0x62000328+4*(4*X+Y)))


//IIR��ͨ�����ݲ鿴
#define           IIR_CH_SEL         (0x620003B8)
#define           IIR_CH_DATA(X)  (0x620003BC+4*X)
//ͨ��ѡ�������
#define           CHANNEL_VLD_CNT     (0x620003CC)
//ͨ����λ��ʱ����������λ
#define           CHANNEL_DLY(X)  (0x620003D0+4*X)
#define           FIFO_RST         (0x620003E8)
//����У������ϵ��
#define           CALIB_PARA(X)  (0x62000378+4*X)
//����У��ƫ��
#define           CALIB_OFFSET(X)  (0x62000388+4*X)
//У�������ݣ�����pid
#define           CALIB_OUT(X)  (0x62000398+4*X)
//����Ϊ��FPGA��emifͨ���趨�ļĴ���

//     #define	sys_reset  		    (0x62000008)

////	mailbox tx interface
	#define	wr_ready 			(0x62001202)
	#define	wr_rst 				(0x62001200)
	#define	wr_data_tx 			(0x62001204)
	#define	fifo_tx_status 		(0x6200120A)   //14 fifo ��             //13��   //12-3  fifo����  //

//	mailbox rx interface
	#define	rd_rst 				(0x62001208)
	#define	rd_data_rx 			(0x62001206)
 	#define	fifo_rx_status 		(0x6200120C)   //14 fifo ��             //13��   //12-3  fifo����  //
	#define	mailbox_clr_int		(0x6200120E)

//    UART
    #define TX_Ctrl             (0x62000400)
    #define RX_Ctrl             (0x62000402)//��λ
    #define TX_Data              (0x62000404)//�Ͱ�λ��Ч
    #define UART_Rest            (0x62000406)//
	#define RX_Data_RS485_0     (0x62000408)//Status 5-15 ��fifo
    #define RX_Data_RS485_1     (0x6200040A)
    #define RX_Data_RS485_2     (0x6200040C)
    #define RX_Data_RS422_0     (0x6200040E)
    #define RX_Data_RS422_1     (0x62000410)
    #define RX_Data_RS422_2     (0x62000412)
    #define Status_RS485_0      (0x62000414)
    #define Status_RS485_1      (0x62000416)
    #define Status_RS485_2      (0x62000418)
    #define Status_RS422_0      (0x6200041A)
    #define Status_RS422_1      (0x6200041C)
    #define Status_RS422_2      (0x6200041E)
    #define UART_INT_Ctrl       (0x62000420)//DSP�ж����ĸ����ڣ����д1���㣻
    #define UART_MASK           (0x62000422)//д1�����ж�
    #define UART_INT_Mode       (0x62000424)
////�жϲ�����ʽ���üĴ�����0:��ʾ������1����ʾ������
////Mode1 �յ�UART_INT_Time���������ж�
    #define UART_Parity_En      (0x62000426)
    #define UART_Parity_Selete  (0x62000428)//1- odd
    #define UART_Baudrate_L     (0x6200042A)
    #define UART_Baudrate_H     (0x6200042C)
    #define UART_INT_Time_L     (0x6200042E)//���Mode1������fifo��Ȳ����ж�
    #define UART_INT_Time_H     (0x62000430)
    #define UART_Freq_L         (0x62000432)//EMIF 60M
    #define UART_Freq_H         (0x62000434)
    #define UART_InitEnd        (0x62000436) //�����ʺ�Ƶ����������1


#endif
