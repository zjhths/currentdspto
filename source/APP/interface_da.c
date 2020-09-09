#include "interface_da.h"
//#include "fpga.h"
unsigned int wave=0;

Da_interface* new_da_interface()
{
	Da_interface* real_core	 = (Da_interface*)malloc(sizeof(Da_interface));
	real_core->init      = Da_Init;
	real_core->send		 = Da_Send;
	real_core->recv   	 = Da_Recv;
	real_core->init(real_core);
	return real_core;
}

void Da_Init(Da_interface* interface){
//	PID_KP_HH =0xbff0;//µçÁ÷
//	PID_KP_HL =0x0000;
//	PID_KP_LH =0x0000;
//	PID_KP_LL =0x0000;
//
//	PID_KI_HH=0xbf6b;
//	PID_KI_HL=0x4e81;
//	PID_KI_LH=0xb4e8;
//	PID_KI_LL=0x1b4f;
//
//
//	PID_KD_HH=0x0000;//0
//	PID_KD_HL=0x0000;
//	PID_KD_LH=0x0000;
//	PID_KD_LL=0x0000;
//
//	 DA_CONFIG_SEL=0X0;//kaihuan
//	 WAVE_SEL=0x1;  //changzhi
//	 DA_VI_SEL=0x0;//
}

void Da_Send(Da_interface* interface, unsigned char* data,unsigned int length){
    int i=0;
    switch(wave)
    {
    case 1:
    	WAVE_SEL=0x1;  //changzhi

    	SET_POINT_HH=0xbff0;//1
    	SET_POINT_HL=0x0000;
    	SET_POINT_LH=0x0000;
    	SET_POINT_LL=0x0000;

    	DA_CONFIG_SEL=0X1;//bihuan
    	Delay1();
    	break;
    case 2:
    	SQUARE_HIGH_DUTY =0xc80;//20hz
    	SQUARE_LOW_DUTY =0xc80;

    //	SQUARE_HIGH_DUTY =0x1900;//10hz
    //	SQUARE_LOW_DUTY =0x1900;

    //
    	SQUARE_HIGH_AMP_HH =0x3ff0;//-1
    	SQUARE_HIGH_AMP_HL =0x0000;
    	SQUARE_HIGH_AMP_LH =0x0000;
    	SQUARE_HIGH_AMP_LL =0x0000;
    	SQUARE_LOW_AMP_HH=0x0000;
    	SQUARE_LOW_AMP_HL=0x0000;
    	SQUARE_LOW_AMP_LH=0x0000;
    	SQUARE_LOW_AMP_LL=0x0000;



    	DA_CONFIG_SEL=0X0;
    	WAVE_SEL=0x2;//fangbo
    //	i2c_init();
    //	GPIOInit();
    //	IntInit();
    	DA_CONFIG_SEL=0X1;
    	Delay1();

    	break;
    case 3:
    	SIN_FRQ_H=0x0033;
    	SIN_FRQ_L=0x3333;

    	SIN_AMP_HH=0x3ff0;
    	SIN_AMP_HL=0x0000;
    	SIN_AMP_LH=0x0000;
    	SIN_AMP_LL=0x0000;


    	DA_CONFIG_SEL=0X0;
    	WAVE_SEL=0x8;//zhengxian
    	DA_CONFIG_SEL=0X1;
    	Delay1();
    	break;
    default:
    	break;
    }






}



void Da_Recv(Da_interface* interface, unsigned char* data,unsigned int* length){
    unsigned int* data_length=length;
    unsigned int i=0;

}





