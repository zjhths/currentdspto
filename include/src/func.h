/*
 * func.h
 *
 *  Created on: 2015-11-26
 *      Author: Administrator
 */

#ifndef FUNC_H_
#define FUNC_H_


#define TMR_addr (0x01C20000)    //by  Hannie


#define PI 3.1415926

#define Own_Add 0x41

union data_buffer
{
	volatile unsigned char c_data[4];
	volatile float f_data;
};
union my_uni
{
	 unsigned char uni_char[8];
	 double uni_double;
};

typedef struct
{
	volatile char wave_style;
	volatile union data_buffer fre_data;
	volatile union data_buffer amp_data;
}wave_msg;
//typedef wave_msg *p_wave_msg;


//extern unsigned char target_err;
//extern unsigned char source_err;
extern unsigned char protocol_error;
extern unsigned char cur_measure;
extern unsigned char vol_measure;
//extern unsigned char cur_output_en;
//extern unsigned char vol_output_en;
//extern unsigned char cur_uptrans;
//extern unsigned char vol_uptrans;
//extern union data_buffer cur_data_ext[4];
//extern union data_buffer vol_data_ext[4];
//extern union data_buffer cur_data_output[4];
//extern union data_buffer vol_data_output[4];
extern unsigned char data_prepare;
//extern unsigned char start_output;

//extern unsigned char need_cur_flag;
//extern unsigned char need_vol_flag;
//extern unsigned char ext_vol;
//extern unsigned char ext_cur;
//extern float delay_arr[80];

//extern unsigned char trans_data_out_cur[19];
//extern unsigned char trans_data_out_vol[19];

//extern union my_uni back_data;
//extern union my_uni back_data1;

//extern float adi_out_average,adv_out_average;	//16路AD测量数据的平均值
//extern unsigned int out_cnt_v1;
//extern unsigned int out_cnt_i1;

//extern unsigned char need_vol_array[19];
//extern unsigned char need_cur_array[19];

//extern unsigned int back_cur_flag ;
//extern unsigned int back_vol_flag ;

//extern unsigned int DAV_CONV;
//extern unsigned int DAI_CONV;

//extern float MaxCurrent;
//extern float MaxVoltage;

//extern float VolScale;
//extern float Rx;

//extern int NoLoad;
//extern unsigned char OutVol;
//extern int new_data_v;








#endif /* FUNC_H_ */
