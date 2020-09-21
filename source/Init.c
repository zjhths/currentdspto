

#include "fpga.h"
#include "Init.h"
#include "interface_da.h"
#include "control_variable.h"
#include <protocol_analyze.h>
unsigned short VID_R,PID_R;
Da_Variable m_da_variable={{1.0259e+08,0}};
Ad_Phase     m_ad_phase   ={48,48,52,53,10,1};
Ad_Variable m_ad_variable={{{-7.11E-13,0},{-1.42E-11,0},{-7.19E-11,0},{-7.56E-10,0},{4.66E-09,0}},
                                                 {4.68E-09,0}};
 Fusion_Parameters fusion={{{0,           0,            0,           0,          0           },
                                                {0,            0,            0,           0.7620,  0.2380},
                                                {0,            0,            0.4790,  0.3970,  0.2380},
                                                {0,            0.3910,   0.2920,  0.2420,  0.0753},
                                                {0.2780,   0.2830,   0.2110,  0.1740,  0.0544}}};

 Kalman_Parameters m_pusion_parameters={0,0};
 Calib_Struct              m_calib_struct = {{1,0}};
 PID_Struct                m_pid_struct    = {-0.6,0,0};
void fpga_init()
{
//	   test_addr=0x5A;
//        unsigned char te=test_addr;

    EMIF(UART_Rest)=0xffff;   //UART复位
		asm("	NOP");
	EMIF(UART_Rest)=0x00;

	EMIF(UART_InitEnd)=0x0000;


}
void Flash_data_init(){
    unsigned int offset=0;
    NOR_read(NOR_FLASH_DATA_BASE,(unsigned char*)&(m_da_variable)+offset,sizeof(Da_Variable)/2);
    offset+=sizeof(Da_Variable);
    NOR_read(NOR_FLASH_DATA_BASE,(unsigned char*)&(m_ad_phase)+offset,sizeof(Ad_Phase)/2);
    offset+=sizeof(Ad_Phase);
    NOR_read(NOR_FLASH_DATA_BASE,(unsigned char*)&(m_ad_variable)+offset,sizeof(Ad_Variable)/2);
    offset+=sizeof(Ad_Variable);
    NOR_read(NOR_FLASH_DATA_BASE,(unsigned char*)&(fusion)+offset,sizeof(Fusion_Parameters)/2);
    offset+=sizeof(Fusion_Parameters);
    NOR_read(NOR_FLASH_DATA_BASE,(unsigned char*)&(m_pusion_parameters)+offset,sizeof(Kalman_Parameters)/2);
    offset+=sizeof(Kalman_Parameters);
    NOR_read(NOR_FLASH_DATA_BASE,(unsigned char*)&(m_calib_struct)+offset,sizeof(Calib_Struct)/2);
    offset+=sizeof(Calib_Struct);
    NOR_read(NOR_FLASH_DATA_BASE,(unsigned char*)&(m_pid_struct)+offset,sizeof(PID_Struct)/2);
}

void channaldelay_init()
{
	int i;
	for(i=0;i<5;i++)
	EMIF(CHANNEL_DLY(i))=m_ad_phase.phase_calibration2500[i];//48

	EMIF(CHANNEL_DLY(5))=m_ad_phase.phase_calibration1281;//1
	EMIF(FIFO_RST)=0X3;
	for(i=0;i<400;i++)
		asm("	NOP");
}

void FUSION_init()
{int i=0,j=0,k=0;
unsigned short* data_tamp_ptr=0;
for(i=2 ;i<5;i++){
    EMIF(FUSION_CH_STATUS)=i;
    for(j=0 ;j<5;j++){
        data_tamp_ptr =(unsigned short*)&(fusion.fusion_param[i][j]);
        for(k=0 ;k<4;k++){
             EMIF(FUSION_PARAM(j,k))=*(data_tamp_ptr+3-k);
        }
    }
}
}
void DAPara_init()
{   int i=0;
    double da_k = 0;
    double da_b = 0;
    unsigned short* data_tamp_ptr=(unsigned short*)&(m_da_variable.da_linear.da_proportion);
    for(i=0 ;i<4;i++){
          EMIF(DA_FIX_BASE(i))=*(data_tamp_ptr+3-i);
    }
    data_tamp_ptr=(unsigned short*)&(m_da_variable.da_linear.da_offset);
    for(i=0 ;i<4;i++){
          EMIF(DA_OFFSET(i))=*(data_tamp_ptr+3-i);
    }
}
void ADPara_init()
{
    int i=0,j=0,k=0;
	unsigned short* data_tamp_ptr=0;
	for(i=2 ;i<5;i++){
	    EMIF(FUSION_CH_STATUS)=i;
	    for(j=0 ;j<4;j++){
	        data_tamp_ptr =(unsigned short*)&(m_ad_variable.ad_linear2500[j].da_proportion);
	        for(k=0 ;k<4;k++){
	             EMIF(AD2500_PARAM_I(j,k))=*(data_tamp_ptr+3-k);
	        }
            data_tamp_ptr =(unsigned short*)&(m_ad_variable.ad_linear2500[j].da_offset);
            for(k=0 ;k<4;k++){
                 EMIF(AD2500_OFFSET_I(j,k))=*(data_tamp_ptr+3-k);
            }
	    }
	}

    for(j=0 ;j<1;j++){
        data_tamp_ptr =(unsigned short*)&(m_ad_variable.ad_linear1281.da_proportion);
        for(k=0 ;k<4;k++){
             EMIF(AD2500_PARAM_I(j,k))=*(data_tamp_ptr+3-k);
        }
        data_tamp_ptr =(unsigned short*)&(m_ad_variable.ad_linear1281.da_offset);
        for(k=0 ;k<4;k++){
             EMIF(AD2500_OFFSET_I(j,k))=*(data_tamp_ptr+3-k);
        }
    }
}
void AD1281_init()
{
	int i;

	for(i=0;i<400;i++)
		asm("	NOP");

	//1281初始化首先复位
	EMIF(AD_RST_EN) = 0x0;
	for(i=0;i<400;i++)
		asm("	NOP");

	EMIF(AD_RST_EN) = 0x01;
	for(i=0;i<400;i++)
		asm("	NOP");


	//配置寄存器，开写使能
	EMIF(AD_REG_WR) = 0x01;
	for(i=0;i<400;i++)
		asm("	NOP");

	//写寄存器，按照手册规定  每8位给一个cmd_en
	//第1帧     停掉连续读数
	EMIF(AD_COMMAND) = 0x11;
	EMIF(AD_CMD_EN) = 0x01;
	for(i=0;i<400;i++)
		asm("	NOP");
	EMIF(AD_CMD_EN) = 0x0;
	for(i=0;i<500;i++)
		asm("	NOP");
	//第2帧      确定写寄存器首地址
	EMIF(AD_COMMAND) = 0x41;
	EMIF(AD_CMD_EN) = 0x01;
	for(i=0;i<400;i++)
		asm("	NOP");
	EMIF(AD_CMD_EN) = 0x0;
	for(i=0;i<500;i++)
		asm("	NOP");
	//第3帧     确定写寄存器个数为1
	EMIF(AD_COMMAND) = 0x0;
	EMIF(AD_CMD_EN) = 0x01;
	for(i=0;i<400;i++)
		asm("	NOP");
	EMIF(AD_CMD_EN) = 0x0;
	for(i=0;i<500;i++)
		asm("	NOP");
	//第4帧     写哦寄存器的值
	EMIF(AD_COMMAND) = 0x51;//51：32k 61：:128k
	EMIF(AD_CMD_EN) = 0x01;
	for(i=0;i<400;i++)
		asm("	NOP");
	EMIF(AD_CMD_EN) = 0x0;
	for(i=0;i<500;i++)
		asm("	NOP");
	//第5帧      打开连续读
	EMIF(AD_COMMAND) = 0x10;
	EMIF(AD_CMD_EN) = 0x01;
	for(i=0;i<400;i++)
		asm("	NOP");
	EMIF(AD_CMD_EN) = 0x0;
	for(i=0;i<500;i++)
		asm("	NOP");
	//写完关闭写使能
	EMIF(AD_REG_WR) = 0x00;
	for(i=0;i<400;i++)
		asm("	NOP");

	//开都市能
	EMIF(AD_DAT_RD) = 0x01;
	for(i=0;i<400;i++)
		asm("	NOP");


	return;
}


void AD2500_init()
{
	int i;

	EMIF(AD_2500_CFG_DIN) = 0x821;
//	for(i=0;i<400;i++)
//		asm("	NOP");
	EMIF(AD_2500_CFG_EN) = 0x01;
	for(i=0;i<400;i++)
		asm("	NOP");
	EMIF(AD_2500_CFG_EN) = 0x0;
	for(i=0;i<500;i++)
		asm("	NOP");
	return;
}

void PID_init()
{
    double Kp=-0.6;
    unsigned short* data_tamp_ptr=(unsigned short*)&(m_pid_struct.pid_kp);
	////配置PID
		PID_KP_HH=*(data_tamp_ptr+3);// -1 bff0
		PID_KP_HL=*(data_tamp_ptr+2);
		PID_KP_LH=*(data_tamp_ptr+1);
		PID_KP_LL=*(data_tamp_ptr);
		data_tamp_ptr=(unsigned short*)&(m_pid_struct.pid_ki);
		PID_KI_HH=*(data_tamp_ptr+3);//
		PID_KI_HL=*(data_tamp_ptr+2);
		PID_KI_LH=*(data_tamp_ptr+1);
		PID_KI_LL=*(data_tamp_ptr);
		data_tamp_ptr=(unsigned short*)&(m_pid_struct.pid_kd);
		PID_KD_HH=*(data_tamp_ptr+3);
		PID_KD_HL=*(data_tamp_ptr+2);
		PID_KD_LH=*(data_tamp_ptr+1);
		PID_KD_LL=*(data_tamp_ptr+0);
}
