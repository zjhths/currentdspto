#ifndef OCEAN_FPGA_H
#define OCEAN_FPGA_H

	//Global
//	#define	CLK_FRE 				(*(unsigned short int *)0x62000000)
// 	#define	DA_CLK_FRE 				(*(unsigned short int *)0x62000004)
//	#define	DA_RST_DLY 			    (*(unsigned short int *)0x62000008)
//    #define	CODE_SEL 				(*(unsigned short int *)0x6200000C)
//    #define	AD_SMPL  		        (*(unsigned short int *)0x62000010)
//	#define	AD_SMPL_CNT 		    (*(unsigned short int *)0x62000014)
//LED
 	#define	LED_CONFIG 				(*(unsigned short int *)0x62000000)
//DAc
    #define	DA_DATA_EN 				(*(unsigned short int *)0x62000004)
	#define	DA_DATA_H 			    (*(unsigned short int *)0x62000008)
    #define	DA_DATA_L 				(*(unsigned short int *)0x6200000C)
 	#define	DA_RST_EN 				(*(unsigned short int *)0x62000010)
//AD1281
	#define	AD_RST_EN 			    (*(unsigned short int *)0x62000014)
    #define	AD_SYNC_EN 				(*(unsigned short int *)0x62000018)
 	#define	AD_CMD_EN 				(*(unsigned short int *)0x6200001C)
	#define	AD_REG_WR 			    (*(unsigned short int *)0x62000020)
    #define	AD_DAT_RD 				(*(unsigned short int *)0x62000024)
 	#define	AD_COMMAND 				(*(unsigned short int *)0x62000028)
 	#define	AD_STATUS 				(*(unsigned short int *)0x6200002C)
//ad2500读到的直接数据，32位
	#define	AD_2500_1H 			    (*(unsigned short int *)0x62000030)
    #define	AD_2500_1L 			    (*(unsigned short int *)0x62000034)
	#define	AD_2500_2H 			    (*(unsigned short int *)0x62000038)
    #define	AD_2500_2L 			    (*(unsigned short int *)0x6200003C)
	#define	AD_2500_3H 			    (*(unsigned short int *)0x62000040)
	#define	AD_2500_3L 			    (*(unsigned short int *)0x62000044)
	#define	AD_2500_4H 				(*(unsigned short int *)0x62000048)
  	#define	AD_2500_4L 				(*(unsigned short int *)0x6200004C)
	#define	AD_2500_5H 				(*(unsigned short int *)0x62000050)
  	#define	AD_2500_5L 				(*(unsigned short int *)0x62000054)
//中断清除和使能
	#define	INT_CLEAR  		        (*(unsigned short int *)0x62000058)
	#define	INT_EN  	    		(*(unsigned short int *)0x6200005C)
//DA由dsp控制或fpga控制
//	#define	DA_CONFIG_SEL  		    (*(unsigned short int *)0x62000060)
//电流电压模式
//	#define	DA_VI_SEL  	    		(*(unsigned short int *)0x62000064)

 //从第一通道到第1281通道
	#define	 CHANNEL_SEL            (*(unsigned short int *)0x62000068)
//ad通道直读数据
	#define	 CHANNEL_DATA_H            (*(volatile unsigned short  *)0x6200006C)
	#define	 CHANNEL_DATA_L            (*(volatile unsigned short  *)0x62000070)
//进PID前的ad值，综合64次累加，得到的数首先除以64 2k速率更新
	#define	 AD_OUT_DATA_HH            (*(unsigned short int *)0x62000074)
	#define	 AD_OUT_DATA_HL            (*(unsigned short int *)0x62000078)
	#define	 AD_OUT_DATA_LH            (*(unsigned short int *)0x6200007C)
	#define	 AD_OUT_DATA_LL            (*(unsigned short int *)0x62000080)

//跳过模块功能
 #define	   CONTROL_BYPASS             (*(unsigned short int *)0x62000084)
//跳过模块功能
 #define          QDATA_HH                (*(unsigned short int *)0x62000088)
 #define          QDATA_HL                (*(unsigned short int *)0x6200008C)
 #define          QDATA_LH                (*(unsigned short int *)0x62000090)
 #define          QDATA_LL                (*(unsigned short int *)0x62000094)
 #define          RMDATA_HH               (*(unsigned short int *)0x62000098)
 #define          RMDATA_HL               (*(unsigned short int *)0x6200009c)
 #define          RMDATA_LH               (*(unsigned short int *)0x620000A0)
 #define          RMDATA_LL               (*(unsigned short int *)0x620000A4)
//2500、1281比例系数--电压
 #define          AD2500_PARAM1_VHH       (*(unsigned short int *)0x620000A8)
 #define          AD2500_PARAM1_VHL       (*(unsigned short int *)0x620000AC)
 #define          AD2500_PARAM1_VLH       (*(unsigned short int *)0x620000B0)
 #define          AD2500_PARAM1_VLL       (*(unsigned short int *)0x620000B4)
 #define          AD2500_PARAM2_VHH       (*(unsigned short int *)0x620000B8)
 #define          AD2500_PARAM2_VHL       (*(unsigned short int *)0x620000BC)
 #define          AD2500_PARAM2_VLH       (*(unsigned short int *)0x620000C0)
 #define          AD2500_PARAM2_VLL       (*(unsigned short int *)0x620000C4)
 #define          AD2500_PARAM3_VHH       (*(unsigned short int *)0x620000C8)
 #define          AD2500_PARAM3_VHL       (*(unsigned short int *)0x620000CC)
 #define          AD2500_PARAM3_VLH       (*(unsigned short int *)0x620000D0)
 #define          AD2500_PARAM3_VLL       (*(unsigned short int *)0x620000D4)
 #define          AD2500_PARAM4_VHH       (*(unsigned short int *)0x620000D8)
 #define          AD2500_PARAM4_VHL       (*(unsigned short int *)0x620000DC)
 #define          AD2500_PARAM4_VLH       (*(unsigned short int *)0x620000E0)
 #define          AD2500_PARAM4_VLL       (*(unsigned short int *)0x620000E4)
 #define          AD2500_PARAM5_VHH       (*(unsigned short int *)0x620000E8)
 #define          AD2500_PARAM5_VHL       (*(unsigned short int *)0x620000EC)
 #define          AD2500_PARAM5_VLH       (*(unsigned short int *)0x620000F0)
 #define          AD2500_PARAM5_VLL       (*(unsigned short int *)0x620000F4)
 #define          AD1281_PARAM_VHH        (*(unsigned short int *)0x620000F8)
 #define          AD1281_PARAM_VHL        (*(unsigned short int *)0x620000FC)
 #define          AD1281_PARAM_VLH        (*(unsigned short int *)0x62000100)
 #define          AD1281_PARAM_VLL        (*(unsigned short int *)0x62000104)
//2500、1281比例系数--电流
 #define          AD2500_PARAM1_IHH       (*(unsigned short int *)0x62000108)
 #define          AD2500_PARAM1_IHL       (*(unsigned short int *)0x6200010C)
 #define          AD2500_PARAM1_ILH       (*(unsigned short int *)0x62000110)
 #define          AD2500_PARAM1_ILL       (*(unsigned short int *)0x62000114)
 #define          AD2500_PARAM2_IHH       (*(unsigned short int *)0x62000118)
 #define          AD2500_PARAM2_IHL       (*(unsigned short int *)0x6200011C)
 #define          AD2500_PARAM2_ILH       (*(unsigned short int *)0x62000120)
 #define          AD2500_PARAM2_ILL       (*(unsigned short int *)0x62000124)
 #define          AD2500_PARAM3_IHH       (*(unsigned short int *)0x62000128)
 #define          AD2500_PARAM3_IHL       (*(unsigned short int *)0x6200012C)
 #define          AD2500_PARAM3_ILH       (*(unsigned short int *)0x62000130)
 #define          AD2500_PARAM3_ILL       (*(unsigned short int *)0x62000134)
 #define          AD2500_PARAM4_IHH       (*(unsigned short int *)0x62000138)
 #define          AD2500_PARAM4_IHL       (*(unsigned short int *)0x6200013C)
 #define          AD2500_PARAM4_ILH       (*(unsigned short int *)0x62000140)
 #define          AD2500_PARAM4_ILL       (*(unsigned short int *)0x62000144)
 #define          AD2500_PARAM5_IHH       (*(unsigned short int *)0x62000148)
 #define          AD2500_PARAM5_IHL       (*(unsigned short int *)0x6200014C)
 #define          AD2500_PARAM5_ILH       (*(unsigned short int *)0x62000150)
 #define          AD2500_PARAM5_ILL       (*(unsigned short int *)0x62000154)
 #define          AD1281_PARAM_IHH        (*(unsigned short int *)0x62000158)
 #define          AD1281_PARAM_IHL        (*(unsigned short int *)0x6200015C)
 #define          AD1281_PARAM_ILH        (*(unsigned short int *)0x62000160)
 #define          AD1281_PARAM_ILL        (*(unsigned short int *)0x62000164)
//2500、1281偏置--电压
 #define          AD2500_OFFSET1_VHH      (*(unsigned short int *)0x62000168)
 #define          AD2500_OFFSET1_VHL      (*(unsigned short int *)0x6200016C)
 #define          AD2500_OFFSET1_VLH      (*(unsigned short int *)0x62000170)
 #define          AD2500_OFFSET1_VLL      (*(unsigned short int *)0x62000174)
 #define          AD2500_OFFSET2_VHH      (*(unsigned short int *)0x62000178)
 #define          AD2500_OFFSET2_VHL      (*(unsigned short int *)0x6200017C)
 #define          AD2500_OFFSET2_VLH      (*(unsigned short int *)0x62000180)
 #define          AD2500_OFFSET2_VLL      (*(unsigned short int *)0x62000184)
 #define          AD2500_OFFSET3_VHH      (*(unsigned short int *)0x62000188)
 #define          AD2500_OFFSET3_VHL      (*(unsigned short int *)0x6200018C)
 #define          AD2500_OFFSET3_VLH      (*(unsigned short int *)0x62000190)
 #define          AD2500_OFFSET3_VLL      (*(unsigned short int *)0x62000194)
 #define          AD2500_OFFSET4_VHH      (*(unsigned short int *)0x62000198)
 #define          AD2500_OFFSET4_VHL      (*(unsigned short int *)0x6200019C)
 #define          AD2500_OFFSET4_VLH      (*(unsigned short int *)0x620001A0)
 #define          AD2500_OFFSET4_VLL      (*(unsigned short int *)0x620001A4)
 #define          AD2500_OFFSET5_VHH      (*(unsigned short int *)0x620001A8)
 #define          AD2500_OFFSET5_VHL      (*(unsigned short int *)0x620001AC)
 #define          AD2500_OFFSET5_VLH      (*(unsigned short int *)0x620001B0)
 #define          AD2500_OFFSET5_VLL      (*(unsigned short int *)0x620001B4)
 #define          AD1281_OFFSET_VHH       (*(unsigned short int *)0x620001B8)
 #define          AD1281_OFFSET_VHL       (*(unsigned short int *)0x620001BC)
 #define          AD1281_OFFSET_VLH       (*(unsigned short int *)0x620001C0)
 #define          AD1281_OFFSET_VLL       (*(unsigned short int *)0x620001C4)
//2500、1281偏置--电流
 #define          AD2500_OFFSET1_IHH      (*(unsigned short int *)0x620001C8)
 #define          AD2500_OFFSET1_IHL      (*(unsigned short int *)0x620001CC)
 #define          AD2500_OFFSET1_ILH      (*(unsigned short int *)0x620001D0)
 #define          AD2500_OFFSET1_ILL      (*(unsigned short int *)0x620001D4)
 #define          AD2500_OFFSET2_IHH      (*(unsigned short int *)0x620001D8)
 #define          AD2500_OFFSET2_IHL      (*(unsigned short int *)0x620001DC)
 #define          AD2500_OFFSET2_ILH      (*(unsigned short int *)0x620001E0)
 #define          AD2500_OFFSET2_ILL      (*(unsigned short int *)0x620001E4)
 #define          AD2500_OFFSET3_IHH      (*(unsigned short int *)0x620001E8)
 #define          AD2500_OFFSET3_IHL      (*(unsigned short int *)0x620001EC)
 #define          AD2500_OFFSET3_ILH      (*(unsigned short int *)0x620001F0)
 #define          AD2500_OFFSET3_ILL      (*(unsigned short int *)0x620001F4)
 #define          AD2500_OFFSET4_IHH      (*(unsigned short int *)0x620001F8)
 #define          AD2500_OFFSET4_IHL      (*(unsigned short int *)0x620001FC)
 #define          AD2500_OFFSET4_ILH      (*(unsigned short int *)0x62000200)
 #define          AD2500_OFFSET4_ILL      (*(unsigned short int *)0x62000204)
 #define          AD2500_OFFSET5_IHH      (*(unsigned short int *)0x62000208)
 #define          AD2500_OFFSET5_IHL      (*(unsigned short int *)0x6200020C)
 #define          AD2500_OFFSET5_ILH      (*(unsigned short int *)0x62000210)
 #define          AD2500_OFFSET5_ILL      (*(unsigned short int *)0x62000214)
 #define          AD1281_OFFSET_IHH       (*(unsigned short int *)0x62000218)
 #define          AD1281_OFFSET_IHL       (*(unsigned short int *)0x6200021C)
 #define          AD1281_OFFSET_ILH       (*(unsigned short int *)0x62000220)
 #define          AD1281_OFFSET_ILL       (*(unsigned short int *)0x62000224)
//在 "interface_da.h"--pid参数
// #define          PID_KP_HH            (*(unsigned short int *)0x62000228)
// #define          PID_KP_HL            (*(unsigned short int *)0x6200022C)
// #define          PID_KP_LH            (*(unsigned short int *)0x62000230)
// #define          PID_KP_LL            (*(unsigned short int *)0x62000234)
//
// #define          PID_KI_HH            (*(unsigned short int *)0x62000238)
// #define          PID_KI_HL            (*(unsigned short int *)0x6200023C)
// #define          PID_KI_LH            (*(unsigned short int *)0x62000240)
// #define          PID_KI_LL            (*(unsigned short int *)0x62000244)
//
// #define          PID_KD_HH            (*(unsigned short int *)0x62000248)
// #define          PID_KD_HL            (*(unsigned short int *)0x6200024C)
// #define          PID_KD_LH            (*(unsigned short int *)0x62000250)
// #define          PID_KD_LL            (*(unsigned short int *)0x62000254)
//2500配置寄存器
 #define          AD_2500_CFG_EN            (*(unsigned short int *)0x62000258)
 #define          AD_2500_CFG_DIN           (*(unsigned short int *)0x6200025C)
//选择dsp控制：0  fpga控制：1
 #define	 	  DA_CONFIG_SEL             (*(unsigned short int *)0x62000060)
//电流电压控制切换    0：电流       1：电压
 #define	      DA_VI_SEL              	(*(unsigned short int *)0x62000064)
//DA输出比例系数和偏置
 #define          DA_FIX_BASE_HH          (*(unsigned short int *)0x62000278)
 #define          DA_FIX_BASE_HL          (*(unsigned short int *)0x6200027C)
 #define          DA_FIX_BASE_LH          (*(unsigned short int *)0x62000280)
 #define          DA_FIX_BASE_LL          (*(unsigned short int *)0x62000284)
 #define          DA_OFFSET_HH            (*(unsigned short int *)0x62000288)
 #define          DA_OFFSET_HL            (*(unsigned short int *)0x6200028C)
 #define          DA_OFFSET_LH            (*(unsigned short int *)0x62000290)
 #define          DA_OFFSET_LL            (*(unsigned short int *)0x62000294)
//在 "interface_da.h"
// #define          SET_POINT_HH          (*(unsigned short int *)0x62000298)
// #define          SET_POINT_HL          (*(unsigned short int *)0x6200029C)
// #define          SET_POINT_LH          (*(unsigned short int *)0x620002A0)
// #define          SET_POINT_LL          (*(unsigned short int *)0x620002A4)
//输出波形模式选择
 #define          WAVE_SEL              (*(unsigned short int *)0x620002A8)
//在 "interface_da.h"
// #define          SIN_FRQ_H             (*(unsigned short int *)0x620002AC)
// #define          SIN_FRQ_L             (*(unsigned short int *)0x620002B0)
// #define          SIN_AMP_HH            (*(unsigned short int *)0x620002B4)
// #define          SIN_AMP_HL            (*(unsigned short int *)0x620002B8)
// #define          SIN_AMP_LH            (*(unsigned short int *)0x620002BC)
// #define          SIN_AMP_LL            (*(unsigned short int *)0x620002C0)
// #define          SQUARE_HIGH_DUTY              (*(unsigned short int *)0x620002E8)
// #define          SQUARE_LOW_DUTY               (*(unsigned short int *)0x620002EC)
// #define          SQUARE_HIGH_AMP_HH            (*(unsigned short int *)0x620002F0)
// #define          SQUARE_HIGH_AMP_HL            (*(unsigned short int *)0x620002F4)
// #define          SQUARE_HIGH_AMP_LH            (*(unsigned short int *)0x620002F8)
// #define          SQUARE_HIGH_AMP_LL            (*(unsigned short int *)0x620002FC)
// #define          SQUARE_LOW_AMP_HH             (*(unsigned short int *)0x62000300)
// #define          SQUARE_LOW_AMP_HL             (*(unsigned short int *)0x62000304)
// #define          SQUARE_LOW_AMP_LH             (*(unsigned short int *)0x62000308)
// #define          SQUARE_LOW_AMP_LL             (*(unsigned short int *)0x6200030C)
//温度
 #define          GET_TEMPER                (*(unsigned short int *)0x62000310)
 #define          SET_TEMPER                (*(unsigned short int *)0x62000314)
//在 "interface_da.h" 相关参数
 #define          DESIGN_YEAR               (*(unsigned short int *)0x62000318)
 #define          DESIGN_DATE               (*(unsigned short int *)0x6200031C)
 #define          DESIGN_VERSION            (*(unsigned short int *)0x62000320)
//数据融合比例系数以及通道数选择
#define           FUSION_CH_STATUS   (*(unsigned short int *)0x62000324)
#define           FUSION_PARAM1_HH   (*(unsigned short int *)0x62000328)
#define           FUSION_PARAM1_HL   (*(unsigned short int *)0x6200032C)
#define           FUSION_PARAM1_LH   (*(unsigned short int *)0x62000330)
#define           FUSION_PARAM1_LL   (*(unsigned short int *)0x62000334)
#define           FUSION_PARAM2_HH   (*(unsigned short int *)0x62000338)
#define           FUSION_PARAM2_HL   (*(unsigned short int *)0x6200033C)
#define           FUSION_PARAM2_LH   (*(unsigned short int *)0x62000340)
#define           FUSION_PARAM2_LL   (*(unsigned short int *)0x62000344)
#define           FUSION_PARAM3_HH   (*(unsigned short int *)0x62000348)
#define           FUSION_PARAM3_HL   (*(unsigned short int *)0x6200034C)
#define           FUSION_PARAM3_LH   (*(unsigned short int *)0x62000350)
#define           FUSION_PARAM3_LL   (*(unsigned short int *)0x62000354)
#define           FUSION_PARAM4_HH   (*(unsigned short int *)0x62000358)
#define           FUSION_PARAM4_HL   (*(unsigned short int *)0x6200035C)
#define           FUSION_PARAM4_LH   (*(unsigned short int *)0x62000360)
#define           FUSION_PARAM4_LL   (*(unsigned short int *)0x62000364)
#define           FUSION_PARAM5_HH   (*(unsigned short int *)0x62000368)
#define           FUSION_PARAM5_HL   (*(unsigned short int *)0x6200036C)
#define           FUSION_PARAM5_LH   (*(unsigned short int *)0x62000370)
#define           FUSION_PARAM5_LL   (*(unsigned short int *)0x62000374)
//IIR参数配置  暂时资源不够 iir先不改
//#define           IIR_PARAM0_HH      (*(unsigned short int *)0x62000378)
//#define           IIR_PARAM0_HL      (*(unsigned short int *)0x6200037C)
//#define           IIR_PARAM0_LH      (*(unsigned short int *)0x62000380)
//#define           IIR_PARAM0_LL      (*(unsigned short int *)0x62000384)
//#define           IIR_PARAM1_HH      (*(unsigned short int *)0x62000388)
//#define           IIR_PARAM1_HL      (*(unsigned short int *)0x6200038C)
//#define           IIR_PARAM1_LH      (*(unsigned short int *)0x62000390)
//#define           IIR_PARAM1_LL      (*(unsigned short int *)0x62000394)
//#define           IIR_PARAM2_HH      (*(unsigned short int *)0x62000398)
//#define           IIR_PARAM2_HL      (*(unsigned short int *)0x6200039C)
//#define           IIR_PARAM2_LH      (*(unsigned short int *)0x620003A0)
//#define           IIR_PARAM2_LL      (*(unsigned short int *)0x620003A4)
//#define           IIR_PARAM3_HH      (*(unsigned short int *)0x620003A8)
//#define           IIR_PARAM3_HL      (*(unsigned short int *)0x620003AC)
//#define           IIR_PARAM3_LH      (*(unsigned short int *)0x620003B0)
//#define           IIR_PARAM3_LL      (*(unsigned short int *)0x620003B4)
//IIR后通道数据查看
#define           IIR_CH_SEL         (*(unsigned short int *)0x620003B8)
#define           IIR_CH_DATA_HH     (*(unsigned short int *)0x620003BC)
#define           IIR_CH_DATA_HL     (*(unsigned short int *)0x620003C0)
#define           IIR_CH_DATA_LH     (*(unsigned short int *)0x620003C4)
#define           IIR_CH_DATA_LL     (*(unsigned short int *)0x620003C8)
//通道选择计数器
#define           CHANNEL_VLD_CNT     (*(unsigned short int *)0x620003CC)
//通道相位延时计数器及复位
#define           CHANNEL1_DLY     (*(unsigned short int *)0x620003D0)
#define           CHANNEL2_DLY     (*(unsigned short int *)0x620003D4)
#define           CHANNEL3_DLY     (*(unsigned short int *)0x620003D8)
#define           CHANNEL4_DLY     (*(unsigned short int *)0x620003DC)
#define           CHANNEL5_DLY     (*(unsigned short int *)0x620003E0)
#define           CHANNEL6_DLY     (*(unsigned short int *)0x620003E0)
#define           FIFO_RST         (*(unsigned short int *)0x620003E4)
//二次校正比例系数
#define           CALIB_PARA_HH     (*(unsigned short int *)0x620003E8)
#define           CALIB_PARA_HL     (*(unsigned short int *)0x620003EC)
#define           CALIB_PARA_LH     (*(unsigned short int *)0x620003F0)
#define           CALIB_PARA_LL     (*(unsigned short int *)0x620003F4)
//二次校正偏置
#define           CALIB_OFFSET_HH     (*(unsigned short int *)0x620003F8)
#define           CALIB_OFFSET_HL     (*(unsigned short int *)0x620003FC)
#define           CALIB_OFFSET_LH     (*(unsigned short int *)0x62000400)
#define           CALIB_OFFSET_LL     (*(unsigned short int *)0x62000404)
//校正后数据，进入pid
#define           CALIB_OUT_HH     (*(unsigned short int *)0x62000408)
#define           CALIB_OUT_HL     (*(unsigned short int *)0x6200040C)
#define           CALIB_OUT_LH     (*(unsigned short int *)0x62000400)
#define           CALIB_OUT_LL     (*(unsigned short int *)0x62000404)
//以上为与FPGA的emif通行设定的寄存器

//     #define	sys_reset  		    (*(unsigned short int *)0x62000008)

////	mailbox tx interface
	#define	wr_ready 			(*(unsigned short int *)0x62001202)
	#define	wr_rst 				(*(unsigned short int *)0x62001200)
	#define	wr_data_tx 			(*(unsigned short int *)0x62001204)
	#define	fifo_tx_status 		(*(unsigned short int *)0x6200120A)   //14 fifo 满             //13空   //12-3  fifo长度  //

//	mailbox rx interface
	#define	rd_rst 				(*(unsigned short int *)0x62001208)
	#define	rd_data_rx 			(*(unsigned short int *)0x62001206)
 	#define	fifo_rx_status 		(*(unsigned short int *)0x6200120C)   //14 fifo 满             //13空   //12-3  fifo长度  //
	#define	mailbox_clr_int		(*(unsigned short int *)0x6200120E)

//    UART
    #define TX_Ctrl             (*(unsigned short int *)0x62000400)
    #define RX_Ctrl             (*(unsigned short int *)0x62000402)//按位
    #define TX_Data              (*(unsigned short int *)0x62000404)//低八位有效
    #define UART_Rest            (*(unsigned short int *)0x62000406)//
	#define RX_Data_RS485_0     (*(unsigned short int *)0x62000408)//Status 5-15 读fifo
    #define RX_Data_RS485_1     (*(unsigned short int *)0x6200040A)
    #define RX_Data_RS485_2     (*(unsigned short int *)0x6200040C)
    #define RX_Data_RS422_0     (*(unsigned short int *)0x6200040E)
    #define RX_Data_RS422_1     (*(unsigned short int *)0x62000410)
    #define RX_Data_RS422_2     (*(unsigned short int *)0x62000412)
    #define Status_RS485_0      (*(unsigned short int *)0x62000414)
    #define Status_RS485_1      (*(unsigned short int *)0x62000416)
    #define Status_RS485_2      (*(unsigned short int *)0x62000418)
    #define Status_RS422_0      (*(unsigned short int *)0x6200041A)
    #define Status_RS422_1      (*(unsigned short int *)0x6200041C)
    #define Status_RS422_2      (*(unsigned short int *)0x6200041E)
    #define UART_INT_Ctrl       (*(unsigned short int *)0x62000420)//DSP判断是哪个串口，最后写1清零；
    #define UART_MASK           (*(unsigned short int *)0x62000422)//写1屏蔽中断
    #define UART_INT_Mode       (*(unsigned short int *)0x62000424)
////中断产生方式配置寄存器，0:表示定长；1：表示不定长
////Mode1 收到UART_INT_Time个数产生中断
    #define UART_Parity_En      (*(unsigned short int *)0x62000426)
    #define UART_Parity_Selete  (*(unsigned short int *)0x62000428)//1- odd
    #define UART_Baudrate_L     (*(unsigned short int *)0x6200042A)
    #define UART_Baudrate_H     (*(unsigned short int *)0x6200042C)
    #define UART_INT_Time_L     (*(unsigned short int *)0x6200042E)//配合Mode1，接收fifo深度产生中断
    #define UART_INT_Time_H     (*(unsigned short int *)0x62000430)
    #define UART_Freq_L         (*(unsigned short int *)0x62000432)//EMIF 60M
    #define UART_Freq_H         (*(unsigned short int *)0x62000434)
    #define UART_InitEnd        (*(unsigned short int *)0x62000436) //波特率和频率设置完置1




////HDLC
//    #define HDLC_TX_EN_A		(*(unsigned short int *)0x62002000)		//WRITE ONLY
//    #define HDLC_TX_CTRL_A		(*(unsigned short int *)0x62002004)
//    #define HDLC_TX_DATA_A		(*(unsigned short int *)0x62002008)		//WRITE ONLY
//    #define HDLC_TX_STATUS_A	(*(unsigned short int *)0x6200200C)		//WRITE ONLY
//
//    #define HDLC_RX_EN_A		(*(unsigned short int *)0x62002010)		//READ ONLY
//    #define HDLC_RX_CTRL_A		(*(unsigned short int *)0x62002014)
//    #define HDLC_RX_DATA_A		(*(unsigned short int *)0x62002018)		//READ ONLY
//    #define HDLC_RX_STATUS_A	(*(unsigned short int *)0x6200201C)		//READ ONLY
//
//    #define INT_STATUSA			(*(unsigned int *)0x62002020)
//    #define CLR_HDLC_A_INT		(*(unsigned int *)0x62002024)
//
//
//    #define HDLC_RX_DATA_B		(*(unsigned short int *)0x62000448)		//READ ONLY
//    #define HDLC_RX_STATUS_B	(*(unsigned short int *)0x6200044A)		//READ ONLY
//    #define HDLC_RX_CTRL_B		(*(unsigned short int *)0x6200044C)
//    #define HDLC_RX_EN_B		(*(unsigned short int *)0x6200044E)		//READ ONLY
//    #define HDLC_TX_CTRL_B	    (*(unsigned short int *)0x62000450)
//    #define HDLC_TX_STATUS_B	(*(unsigned short int *)0x62000452)		//WRITE ONLY
//    #define HDLC_TX_EN_B		(*(unsigned short int *)0x62000454)		//WRITE ONLY
//    #define HDLC_TX_DATA_B		(*(unsigned short int *)0x62000456)		//WRITE ONLY
//
//    #define INT_STATUSB			(*(unsigned int *)0x6200045c)
//    #define CLR_HDLC_B_INT		(*(unsigned int *)0x6200045e)



//
//	//common reg
//	#define	VID 						(*(unsigned short int *)0x62000000)
//	#define	PID 						(*(unsigned short int *)0x62000002)
//	#define	LED 						(*(unsigned short int *)0x62000004)
//	#define	RST_I2S_Addr 				(*(unsigned short int *)0x62000008)
//	#define	DA_Dout_low_Addr 			(*(unsigned short int *)0x6200000A)
//	#define	DA_Dout_high_Addr 			(*(unsigned short int *)0x6200000C)
//	#define	RST_DA_Addr 				(*(unsigned short int *)0x6200000E)
//	#define	DA_OE_Addr 					(*(unsigned short int *)0x62000010)
//
//
//    //IM_SPI
//
//	#define	spi_rx_low_addr 						(*(unsigned short int *)0x62000026)
//	#define	spi_rx_high_addr 						(*(unsigned short int *)0x62000028)
//	#define	spi_rx_flag_addr 						(*(unsigned short int *)0x6200002A)
//	#define	spi_int_clr_addr 						(*(unsigned short int *)0x6200002C)
//	#define	spi_ctrl_addr 						    (*(unsigned short int *)0x6200002E)
//
//    //uart
//	#define	uart_rst_Addr 						(*(unsigned short int *)0x62000060)
//	#define	uart_Txd_Addr 						(*(unsigned short int *)0x62000062)
//	#define	uart_Rxd_Addr 						(*(unsigned short int *)0x62000064)
//	#define	Uart_status_Addr 						(*(unsigned short int *)0x62000066)
//	#define	uart_clr_flag_Addr 						(*(unsigned short int *)0x62000068)
//	#define	uart_int_flag_Addr 						(*(unsigned short int *)0x6200006A)
//	#define	uart_clr_int_Addr 						(*(unsigned short int *)0x6200006C)
//	#define	Uart_FIFO_Threshold_addr 						(*(unsigned short int *)0x6200006E)
//	#define	uart_int_en_addr 						(*(unsigned short int *)0x62000070)
//	#define	uart_global_ctrl_addr 						(*(unsigned short int *)0x62000072)
//	#define	uart_int_status_addr 						(*(unsigned short int *)0x62000074)
//	#define	uart_LED_addr 						(*(unsigned short int *)0x62000076)
//
//    //VM_SPI
//
//	#define	VM_spi_rx_low_addr 						(*(unsigned short int *)0x62000086)
//	#define	VM_spi_rx_high_addr 						(*(unsigned short int *)0x62000088)
//	#define	VM_spi_rx_flag_addr 						(*(unsigned short int *)0x6200008A)
//	#define	VM_spi_int_clr_addr 						(*(unsigned short int *)0x6200008C)
//	#define	VM_spi_ctrl_addr 						    (*(unsigned short int *)0x6200008E)
//
//
//    //HDLC
//    #define	HDLC_tx_ctrl_addr 						(*(unsigned short int *)0x620000C2)
//	#define	HDLC_tx_data_in_addr 						(*(unsigned short int *)0x620000C4)
//	#define	HDLC_tx_status_addr 						(*(unsigned short int *)0x620000C6)
//
//	#define	HDLC_rx_ctrl_addr 						(*(unsigned short int *)0x620000CA)
//	#define	HDLC_rx_data_out_addr 						(*(unsigned short int *)0x620000CC)
//	#define	HDLC_rx_status_addr 						(*(unsigned short int *)0x620000CE)
//
//	#define	HDLC_int_flag_addr 						(*(unsigned short int *)0x620000D0)
//	#define	HDLC_clr_int_addr 						(*(unsigned short int *)0x620000D2)


#endif
