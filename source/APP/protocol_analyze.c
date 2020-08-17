/*
 * protocolanalyze.cpp
 *
 *  Created on: 2019年11月24日
 *      Author: Dell
 */

#include <protocol_analyze.h>
#include"fpga.h"
#include "interface_da.h"
Analyze_Type func_type =idle_func;
PF m_protocol_analyze_list[] = {protocol_idle,protocol_rest,protocol_recv_ad_cmd,protocol_recv_ad_data,protocol_set_mode};
unsigned char protocol_data_source[ANALYZE_DATA_SIZE];
protocol_analyze_interface* new_protocol_analyze_interface()
{
    protocol_analyze_interface* real_core    = (protocol_analyze_interface*)malloc(sizeof(protocol_analyze_interface));
    real_core->analyze         = protocol_analyze;

    return real_core;
}
unsigned char protocol_func_map(unsigned char* cmd)
{
switch(*cmd)
{
case 0x31:
   return set_mode_func;
    break;
case 0x32:
   return set_mode_func;
    break;
default:
    return * cmd;
    break;

}
}
void protocol_analyze(protocol_analyze_interface* interface)
{

    protocol_handle_struct* commanda;
    unsigned char cmd_func=0;
    if (fifo_readable(interface->hdlc_input_fifo) == true)
    {
        fifo_read(interface->hdlc_input_fifo, (void *)&protocol_data_source);
        commanda  = (protocol_handle_struct*)protocol_data_source;
        if(CHANNEL_ADDR != commanda->data_locality_addr)
           return ;
       cmd_func = protocol_func_map(&commanda->cmd);
        func_type = (Analyze_Type)(cmd_func);
    }
    m_protocol_analyze_list[(unsigned int)func_type](interface,protocol_data_source);
}

int protocol_idle(protocol_analyze_interface* interface,unsigned char* sources){
return 0;
}

int protocol_rest(protocol_analyze_interface* interface,unsigned char* sources){
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
    unsigned int i=0;
    if (fifo_writeable(interface->hdlc_output_fifo))
    {
        temp_data =  fifo_writeable(interface->ad_input_fifo);
        if (temp_data != 1)
        {
            func_type = idle_func;
            send_pc_data.data_locality_addr = HOST_ADDR;
            send_pc_data.data_source_addr = CHANNEL_ADDR;
            send_pc_data.work_mode = 0x34;
            temp_data  =  (*(unsigned short int *)0x62000310);
            send_pc_data.temp[1] = temp_data;
            send_pc_data.temp[0] = temp_data >> 8;
            for(i = 0;i<100;i++){
                fifo_read(interface->ad_input_fifo, &(send_pc_data.data_sorce[i*4]));
            }
            //fifo_read_batch(interface->ad_input_fifo, send_pc_data.data_sorce, 100);
            fifo_write(interface->hdlc_output_fifo, (void *)&send_pc_data);
        }
    }
return 0;
}
int protocol_set_mode(protocol_analyze_interface* interface,unsigned char* sources){
    protocol_ad_modle_set_struct *m_ad_modle_set;
    unsigned int i=0;
    float m_frequncy=0,m_amplitude=0;
    double m_double=0;
    unsigned int int_frequncy=0;
    unsigned char *p_float =( unsigned char *)&m_frequncy;
    float m_amplitude_tag;
    CHANNEL_SEL = 0x400;
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
    switch(m_ad_modle_set->wave)
    {
    case 0x01://三角波
          int_frequncy = 64000/m_frequncy*2;
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
        Delay1();
    default:
        break;

    }


    //m_ad_modle_set->frequncy
    return 0;
}
