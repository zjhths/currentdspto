/*
 * control_variable.h
 *
 *  Created on: 2020��9��18��
 *      Author: ydk
 */

#ifndef INCLUDE_APP_HEAD_CONTROL_VARIABLE_H_
#define INCLUDE_APP_HEAD_CONTROL_VARIABLE_H_
#pragma pack(1)
typedef struct Linear_Variable{
    double da_proportion;
    double da_offset ;
}Linear_Variable;
/*DA����У׼*/
typedef struct Da_Variable
{
    Linear_Variable da_linear;  //DA_FIX_BASE_HH ��ҪУ׼���� //DA_OFFSET_HH
}Da_Variable;

/*AD������λУ׼����*/
typedef struct Ad_Phase
{
    signed int phase_calibration2500[4];//CHANNEL1_DLY
    signed int phase_calibration1281[4];//CHANNEL1_DLY
}Ad_Phase;
/*AD����KPУ׼*/
typedef struct Ad_Variable
{
    Linear_Variable ad_linear2500[4];
    Linear_Variable ad_linear1281[4];
}Ad_Variable;
/*AD�ںϲ���*/
typedef struct Fusion_Parameters
{
    double fusion_param[5][5];
}Fusion_Parameters;
/*Kalman����*/
typedef struct Kalman_Parameters
{
    double kalman_param_q;
    double kalman_param_rm;
}Kalman_Parameters;
/*PIDǰ��������*/
typedef struct Calib_Struct
{
    Linear_Variable calib_struct;
}Calib_Struct;

/*PID����*/
typedef struct PID_Struct
{
    double pid_kp;
    double pid_ki;
    double pid_kd;
}PID_Struct;

/*PID����*/
typedef struct System_Struct
{
    unsigned short ad_updata_mod;
    unsigned short ad_updata_num;
    unsigned short ctrl_bypass;
}System_Struct;
#pragma pack()
#endif /* INCLUDE_APP_HEAD_CONTROL_VARIABLE_H_ */
