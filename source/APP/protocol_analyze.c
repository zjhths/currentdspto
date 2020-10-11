/*
 * protocolanalyze.cpp
 *
 *  Created on: 2019年11月24日
 *      Author: Dell
 */

#include <protocol_analyze.h>
#include "protocol_analyze_remote.h"
#include "protocol_analyze_pc.h"
#include"fpga.h"
#include "interface_da.h"
#include "interface_hdlc.h"


int returns_data_status=0;
Analyze_Type func_type =idle_func;
PF m_protocol_analyze_list[] = {protocol_idle, protocol_rest, protocol_recv_ad_cmd, protocol_recv_ad_data, protocol_set_mode,
                                                     protocol_updata_variable_mode, protocol_updata_da_variable, protocol_updata_ad_phase, protocol_updata_ad_variable,
                                                     protocol_updata_fusion_parameters, protocol_updata_kalman_parameters, protocol_updata_calib_struct, protocol_updata_pid_struct,
                                                     protocol_updata_system_struct,
                                                     protocol_remote_begin, protocol_remote_output,protocol_remote_returns_data,protocol_remote_stop,};
unsigned char protocol_data_source[ANALYZE_DATA_SIZE];
unsigned int signal_list[10]={0};
unsigned int function_size=0;
//test code
unsigned int pkg_num = 0;
protocol_analyze_interface* new_protocol_analyze_interface()
{
    protocol_analyze_interface* real_core    = (protocol_analyze_interface*)malloc(sizeof(protocol_analyze_interface));
    real_core->analyze         = protocol_analyze;
    function_size = sizeof(m_protocol_analyze_list)/sizeof(PF);
    return real_core;
}
unsigned char protocol_func_map(unsigned char* cmd)
{
switch(*cmd)
{
case CMD_REST:
    return  rest_func;
case CMD_SET_CURRENT:
case CMD_SET_VOLTAGE:
   return set_mode_func;

case PC_CMD_SET_VARIABLE:
    return updata_variable_mode_func;
case PC_CMD_DA_VARIABLE:
    return updata_da_variable_func;
case PC_CMD_AD_PHASE:
    return updata_ad_phase_func;
case PC_CMD_AD_VARIABLE:
    return updata_ad_variable_func;
case PC_CMD_FUSION_PARAMETERS:
    return updata_fusion_parameters_func;
case PC_CMD_KALMAN_PARAMETERS:
    return updata_kalman_parameters_func;
case PC_CMD_CAILIB_STRUCT:
    return updata_calib_struct_func;
case PC_CMD_PID_STRUCT:
    return updata_pid_struct_func;
case  PC_CMD_SYSTEM_STRUCT:
    return updata_system_struct_func;
//远程计算机
case REMOTE_CMD_BEGIN:
   return remote_begin;

case REMOTE_CMD_CURRENT_OUTPUT:
case REMOTE_CMD_VOLTAGE_OUTPUT:
   return remote_output;


case REMOTE_CMD_CURRENT_RETURNS:
case REMOTE_CMD_VOLTAGE_RETURNS:
   return remote_returns_data;

case REMOTE_CMD_STOP:
    return  remote_stop;

default:
    if(* cmd < function_size)
         return * cmd;
    else
        return 0;
}
}
void protocol_analyze(protocol_analyze_interface* interface)
{

    protocol_handle_struct* commanda;
    unsigned char cmd_func=0;
    unsigned short data_len=0;
    if (fifo_readable(interface->hdlc_input_fifo) == true)
    {
        fifo_read(interface->hdlc_input_fifo, (void *)&protocol_data_source,&data_len);
        commanda  = (protocol_handle_struct*)protocol_data_source;
        if((CHANNEL_ADDR != commanda->data_locality_addr) && (CHANNEL_ALL_ADDR != commanda->data_locality_addr))
           return ;
       cmd_func = protocol_func_map(&commanda->cmd);
       signal_list[cmd_func]++;
        func_type = (Analyze_Type)(cmd_func);
        returns_data_status=0;
    }
    m_protocol_analyze_list[(unsigned int)func_type](interface,protocol_data_source);
}

int protocol_idle(protocol_analyze_interface* interface,unsigned char* sources){
return 0;
}

int protocol_rest(protocol_analyze_interface* interface,unsigned char* sources){
    func_type = idle_func;
    fifo_clear(interface->ad_input_fifo);
return 0;
}

int protocol_recv_ad_cmd(protocol_analyze_interface* interface,unsigned char* sources){
    func_type = idle_func;
   fifo_clear(interface->ad_input_fifo);
    return 0;
}

int protocol_recv_ad_data(protocol_analyze_interface* interface,unsigned char* sources){
    protocol_ad_to_pc_struct send_pc_data;
    unsigned short temp_data=0;
    unsigned short data_len=0;
    unsigned int i=0;
    func_type = idle_func;
    if (fifo_writeable(interface->hdlc_output_fifo))
    {
        temp_data =  fifo_readable_item_count(interface->ad_input_fifo);
        if (temp_data > 100)
        {

            send_pc_data.data_locality_addr = HOST_ADDR;
            send_pc_data.data_source_addr = CHANNEL_ADDR;
            send_pc_data.work_mode = 0x34;
            temp_data  =  (*(unsigned short int *)0x62000310);
            //temp_data = pkg_num++;
            send_pc_data.temp[1] = temp_data;
            send_pc_data.temp[0] = temp_data >> 8;
            for(i = 0;i<60;i++){
                fifo_read(interface->ad_input_fifo, &(send_pc_data.data_sorce[i*8]),&data_len);
            }
            //fifo_read_batch(interface->ad_input_fifo, send_pc_data.data_sorce, 100);
            data_len=sizeof(send_pc_data);
            fifo_write(interface->hdlc_output_fifo, (void *)&send_pc_data,&data_len);

            signal_list[3]--;
            //if( signal_list[3] <= 0)

        }
    }
return 0;
}
int protocol_set_mode(protocol_analyze_interface* interface,unsigned char* sources){
    protocol_ad_modle_set_struct *m_ad_modle_set;
    unsigned int i=0;
    unsigned short int temp=0;
    float m_frequncy=0,m_amplitude=0;
    double m_double=0;
    unsigned int int_frequncy=0;
    unsigned char *p_float =( unsigned char *)&m_frequncy;
    float m_amplitude_tag;
    EMIF(CHANNEL_SEL)= 0x400;
    func_type = idle_func;
    m_ad_modle_set = (protocol_ad_modle_set_struct *)sources;
    memcpy(p_float,m_ad_modle_set->frequncy,4);
    p_float =( unsigned char *)&m_amplitude;
    memcpy(p_float,m_ad_modle_set->amplitude,4);
    if(m_ad_modle_set->m_handle.cmd == 0x31)//電流輸出
    {
        DA_VI_SEL = 0;
        m_amplitude_tag = -50;
    }else if(m_ad_modle_set->m_handle.cmd == 0x32)//電壓力輸出
    {
        DA_VI_SEL = 1;
        m_amplitude_tag = 1;
    }else
        ;

    EMIF(CONTROL_BYPASS)= ~0x2;
    switch(m_ad_modle_set->wave)
    {
    case 0x01://三角波
          int_frequncy = 64000/m_frequncy;
          m_double = fabs(m_amplitude*m_amplitude_tag/1000);//电压模式下：value = 目标电压（V）；电流模式下value = -50 * 目标电流（A）
          p_float=( unsigned char *)&int_frequncy;
          TRIANGLE_FRQ=(unsigned short )int_frequncy;

          p_float=( unsigned char *)&m_double;
          TRIANGLE_AMP_HH=*(unsigned short *)&p_float[6];
          TRIANGLE_AMP_HL=*(unsigned short *)&p_float[4];
          TRIANGLE_AMP_LH=*(unsigned short *)&p_float[2];
          TRIANGLE_AMP_LL=*(unsigned short *)&p_float[0];
          m_double=m_double*2/int_frequncy;
          TRIANGLE_ITV_HH=*(unsigned short *)&p_float[6];
          TRIANGLE_ITV_HL=*(unsigned short *)&p_float[4];
          TRIANGLE_ITV_LH=*(unsigned short *)&p_float[2];
          TRIANGLE_ITV_LL=*(unsigned short *)&p_float[0];
          DA_CONFIG_SEL=0X0;
          WAVE_SEL=4;//zhengxian
          DA_CONFIG_SEL=0X1;
          EMIF(CONTROL_BYPASS)=0x2;
        break;
    case 0x02://方波
        int_frequncy =128000/m_frequncy/0.5;
        m_double = fabs(m_amplitude*m_amplitude_tag/1000);//电压模式下：value = 目标电压（V）；电流模式下value = -50 * 目标电流（A）
        p_float=( unsigned char *)&int_frequncy;
        SQUARE_HIGH_DUTY=(unsigned short )int_frequncy;
        SQUARE_LOW_DUTY=(unsigned short )int_frequncy;

        p_float=( unsigned char *)&m_double;
        SQUARE_HIGH_AMP_HH=*(unsigned short *)&p_float[6];
        SQUARE_HIGH_AMP_HL=*(unsigned short *)&p_float[4];
        SQUARE_HIGH_AMP_LH=*(unsigned short *)&p_float[2];
        SQUARE_HIGH_AMP_LL=*(unsigned short *)&p_float[0];
        m_double=-m_double;
        SQUARE_LOW_AMP_HH=*(unsigned short *)&p_float[6];
        SQUARE_LOW_AMP_HL=*(unsigned short *)&p_float[4];
        SQUARE_LOW_AMP_LH=*(unsigned short *)&p_float[2];
        SQUARE_LOW_AMP_LL=*(unsigned short *)&p_float[0];
        DA_CONFIG_SEL=0X0;
        WAVE_SEL=2;//zhengxian
        DA_CONFIG_SEL=0X1;
        EMIF(CONTROL_BYPASS)=0x2;
        break;
    case 0x03://正弦波

        int_frequncy = m_frequncy*pow(2,32)/128000;
        m_double = fabs(m_amplitude*m_amplitude_tag/1000);//电压模式下：value = 目标电压（V）；电流模式下value = -50 * 目标电流（A）
        p_float=( unsigned char *)&int_frequncy;
        SIN_FRQ_H=*(unsigned short *)&p_float[2];
        SIN_FRQ_L=*(unsigned short *)&p_float[0];
        p_float=( unsigned char *)&m_double;
        SIN_AMP_HH=*(unsigned short *)&p_float[6];
        SIN_AMP_HL=*(unsigned short *)&p_float[4];
        SIN_AMP_LH=*(unsigned short *)&p_float[2];
        SIN_AMP_LL=*(unsigned short *)&p_float[0];


        DA_CONFIG_SEL=0X0;
        WAVE_SEL=0x8;//zhengxian
        DA_CONFIG_SEL=0X1;
        EMIF(CONTROL_BYPASS)=0x2;
        break;
    case 0x04://直流
        WAVE_SEL = 1; //fix_wave
        m_double = m_amplitude*m_amplitude_tag/1000;//电压模式下：value = 目标电压（V）；电流模式下value = -50 * 目标电流（A）
        p_float=( unsigned char *)&m_double;
        SET_POINT_HH =*(unsigned short *)&p_float[6];
        SET_POINT_HL =*(unsigned short *)&p_float[4];
        SET_POINT_LH =*(unsigned short *)&p_float[2];
        SET_POINT_LL = *(unsigned short *)&p_float[0];
        DA_CONFIG_SEL=0X1;
        EMIF(CONTROL_BYPASS)=0x2;
    default:
        break;


    }
    temp  =  EMIF(FIFO_RST); //第0位：PID 复位，写1，不用写0
            temp |= 1;
            EMIF(FIFO_RST)= temp;
    EMIF(CONTROL_BYPASS)= 0x0;
    //m_ad_modle_set->frequncy
    return 0;
}





