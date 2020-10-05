

#include "fpga.h"
#include "Init.h"
#include "interface_da.h"
#include "control_variable.h"
#include <protocol_analyze.h>
#include "mnic_nor.h"
unsigned short VID_R,PID_R;
//ch2
Da_Variable m_da_variable={{102692047.7,-461857.4844}};
Ad_Phase     m_ad_phase   ={48,48,52,53,10,1};
Ad_Variable m_ad_variable={{{7.105824000000E-13,-6.287694000000E-05},
                                                   {7.105498000000E-12,-6.287694000000E-05},
                                                   {7.191182000000E-11,-6.486302000000E-05},
                                                   {7.055647500000E-10,-1.961454950000E-02},
                                                   {-2.330048000000E-09,-1.412000000000E-03}},
                                                 {-4.671012000000E-09,-3.408688000000E-05}};
 Fusion_Parameters fusion={{{0,           0,            0,           0,          1          },
                                                {0,            0,            0,           7.8610213E-01,  2.1389787E-01},
                                                {0,            0,            7.5039052E-01,   1.9621855E-01,   5.3390937E-02},
                                                {0,            4.9903597E-01,   3.7591866E-01,  9.8298434E-02,   2.6746939E-02},
                                                { 3.3162878E-01,   3.3354128E-01,   2.5125321E-01,  6.5699844E-02,   1.7876884E-02}}};

//ch3
//Da_Variable m_da_variable={{102562427,-1.22838E-12}};
//Ad_Phase     m_ad_phase   ={48,48,52,53,10,1};
//Ad_Variable m_ad_variable={{{7.105824000000E-13,-2.8972910997755E-05},
//                                                  {7.119290000000E-12,-2.2151471314788E-05},
//                                                  {7.187612000000E-11,-2.3530442771000E-06},
//                                                  {7.031512500000E-10,9.2502719083446E-04},
//                                                  {-2.330976000000E-09,-2.7044284385465E-03}},
//                                                 {-4.623152000000E-09,-2.9636807820749E-05}};
//Fusion_Parameters fusion={{{0,           0,            0,           0,          1          },
//                                               {0,            0,            0,           8.9124175E-01,  1.0875825E-01},
//                                               {0,            0,            8.2849089E-01,  1.5285608E-01,  1.8653031E-02},
//                                               {0,            5.4764365E-01,   3.7477311E-01,  6.9145418E-02,  8.4378169E-03},
//                                               {3.5489999E-01,   3.5328493E-01,   2.4176614E-01,  4.4605710E-02,  5.4432357E-03}}};
//ch4
//Da_Variable m_da_variable={{102498647.2,-113124.7845}};
//Ad_Phase     m_ad_phase   ={48,48,52,53,10,1};
//Ad_Variable m_ad_variable={{{7.181988000000E-13,-5.0115219684522E-05},
//                                                   {7.110370000000E-12,-1.0386029027714E-05},
//                                                   {7.194612000000E-11,3.7261588236577E-04},
//                                                   {7.029383333333E-10,5.0802565634388E-03},
//                                                   {-2.329782000000E-09,-1.1971411043407E-02}},
//                                                 {-4.744116000000E-09,-1.0622955629346E-04}};
// Fusion_Parameters fusion={{{0,           0,            0,           0,          1          },
//                                                {0,            0,            0,           7.8610213E-01,  2.1389787E-01},
//                                                {0,            0,            7.5039052E-01,   1.9621855E-01,   5.3390937E-02},
//                                                {0,            4.9903597E-01,   3.7591866E-01,  9.8298434E-02,   2.6746939E-02},
//                                                { 3.3162878E-01,   3.3354128E-01,   2.5125321E-01,  6.5699844E-02,   1.7876884E-02}}};

 Kalman_Parameters m_pusion_parameters={0,0};
 Calib_Struct              m_calib_struct = {{1,0}};
 PID_Struct                m_pid_struct    = {-0.6,0,0};
 System_Struct          m_system_struct = {0,0,0};
extern unsigned char channal_zero;//1:CH1 2:CH2 4:CH3 8:CH4 10:CH5 20:CH1281
extern unsigned int ad_updata;
 void sys_int(){
     channal_zero = m_system_struct.ad_updata_mod;
     ad_updata   = m_system_struct.ad_updata_num;
     EMIF(CONTROL_BYPASS) = m_system_struct.ctrl_bypass;
 }

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
    NOR_read(NOR_FLASH_DATA_BASE+offset,(unsigned char*)&(m_da_variable),sizeof(Da_Variable)/2);
    offset+=sizeof(Da_Variable);
    NOR_read(NOR_FLASH_DATA_BASE+offset,(unsigned char*)&(m_ad_phase),sizeof(Ad_Phase)/2);
    offset+=sizeof(Ad_Phase);
    NOR_read(NOR_FLASH_DATA_BASE+offset,(unsigned char*)&(m_ad_variable),sizeof(Ad_Variable)/2);
    offset+=sizeof(Ad_Variable);
    NOR_read(NOR_FLASH_DATA_BASE+offset,(unsigned char*)&(fusion),sizeof(Fusion_Parameters)/2);
    offset+=sizeof(Fusion_Parameters);
    //NOR_read(NOR_FLASH_DATA_BASE+offset,(unsigned char*)&(m_pusion_parameters),sizeof(Kalman_Parameters)/2);
    offset+=sizeof(Kalman_Parameters);
    NOR_read(NOR_FLASH_DATA_BASE+offset,(unsigned char*)&(m_calib_struct),sizeof(Calib_Struct)/2);
    offset+=sizeof(Calib_Struct);
    NOR_read(NOR_FLASH_DATA_BASE+offset,(unsigned char*)&(m_pid_struct),sizeof(PID_Struct)/2);
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
{
    int i=0,j=0,k=0;
        unsigned short* data_tamp_ptr=0;
        for(i=0 ;i<5;i++){
            EMIF(FUSION_CH_STATUS)=i+1;
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
    da_b = m_da_variable.da_linear.da_offset;
    data_tamp_ptr=(unsigned short*)&(da_b);
    for(i=0 ;i<4;i++){
          EMIF(DA_OFFSET(i))=*(data_tamp_ptr+3-i);
    }
}
void ADPara_init()
{
    int j=0,k=0;
	unsigned short* data_tamp_ptr=0;

	    for(j=0 ;j<5;j++){
	        data_tamp_ptr =(unsigned short*)&(m_ad_variable.ad_linear2500[j].da_proportion);
	        for(k=0 ;k<4;k++){
	             EMIF(AD2500_PARAM_I(j,k))=*(data_tamp_ptr+3-k);
	        }
            data_tamp_ptr =(unsigned short*)&(m_ad_variable.ad_linear2500[j].da_offset);
            for(k=0 ;k<4;k++){
                 EMIF(AD2500_OFFSET_I(j,k))=*(data_tamp_ptr+3-k);
            }
	    }

    for(j=0 ;j<1;j++){
        data_tamp_ptr =(unsigned short*)&(m_ad_variable.ad_linear1281.da_proportion);
        for(k=0 ;k<4;k++){
             EMIF(AD1281_PARAM_I(k))=*(data_tamp_ptr+3-k);
        }
        data_tamp_ptr =(unsigned short*)&(m_ad_variable.ad_linear1281.da_offset);
        for(k=0 ;k<4;k++){
             EMIF(AD1281_OFFSET_I(k))=*(data_tamp_ptr+3-k);
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

void Calib_Para_init(){
    int k=0;
    unsigned short* data_tamp_ptr=(unsigned short*)&(m_calib_struct.calib_struct.da_proportion);
    for(k=0 ;k<4;k++){
         EMIF(CALIB_PARA(k))=*(data_tamp_ptr+3-k);
    }
    data_tamp_ptr=(unsigned short*)&(m_calib_struct.calib_struct.da_offset);
    for(k=0 ;k<4;k++){
         EMIF(CALIB_OFFSET(k))=*(data_tamp_ptr+3-k);
    }
}
