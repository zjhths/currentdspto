/*
 * protocolanalyze.cpp
 *
 *  Created on: 2019年11月24日
 *      Author: Dell
 */

#include <protocol_analyze.h>
#include"fpga.h"
#include "interface_da.h"
#include "interface_hdlc.h"
#define NOR_FLASH_BASE              (0x60000000+5*0x8000)

int returns_data_status=0;
Analyze_Type func_type =idle_func;
PF m_protocol_analyze_list[] = {protocol_idle,protocol_rest,protocol_recv_ad_cmd,protocol_recv_ad_data,protocol_set_mode,protocol_updata_variable_mode,
                                                     protocol_remote_begin, protocol_remote_output,protocol_remote_returns_data,protocol_remote_stop,};
unsigned char protocol_data_source[ANALYZE_DATA_SIZE];
unsigned int signal_list[10]={0};
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
case 0x33:
    return updata_variable_mode_func;
    break;
//远程计算机
case REMOTE_CMD_BEGIN:
   return remote_begin;
    break;
case REMOTE_CMD_CURRENT_OUTPUT:
case REMOTE_CMD_VOLTAGE_OUTPUT:
   return remote_output;
    break;

case REMOTE_CMD_CURRENT_RETURNS:
case REMOTE_CMD_VOLTAGE_RETURNS:
   return remote_returns_data;
    break;
case REMOTE_CMD_STOP:
    return  remote_stop;
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
return 0;
}

int protocol_recv_ad_cmd(protocol_analyze_interface* interface,unsigned char* sources){

   // fifo_clear(interface->ad_input_fifo);
    signal_list[2]--;
    if(signal_list[2] <= 0)
    func_type = idle_func;
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
        if (temp_data > 200)
        {

            send_pc_data.data_locality_addr = HOST_ADDR;
            send_pc_data.data_source_addr = CHANNEL_ADDR;
            send_pc_data.work_mode = 0x34;
            temp_data  =  (*(unsigned short int *)0x62000310);
            send_pc_data.temp[1] = temp_data;
            send_pc_data.temp[0] = temp_data >> 8;
            for(i = 0;i<100;i++){
                fifo_read(interface->ad_input_fifo, &(send_pc_data.data_sorce[i*4]),&data_len);
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
        temp  =  EMIF(FIFO_RST);
                temp |= 1;
                EMIF(FIFO_RST)= temp;
    default:
        break;


    }

   // CONTROL_BYPASS= 0x0;
    //m_ad_modle_set->frequncy
    return 0;
}

int protocol_updata_variable_mode(protocol_analyze_interface* interface,unsigned char* sources){
    func_type = idle_func;
    protocol_updata_variable_struct* m_updata_variable = (protocol_updata_variable_struct*)sources;
    unsigned short data_len = sizeof(protocol_updata_variable_struct);
    NOR_block_erase(NOR_FLASH_DATA_BASE);
    NOR_write(NOR_FLASH_DATA_BASE,(unsigned char*)&(m_updata_variable->up_da_variable),(data_len-3)/2);
    if (fifo_writeable(interface->hdlc_output_fifo))
      {
            NOR_read(NOR_FLASH_DATA_BASE,(unsigned char*)&(m_updata_variable->up_da_variable),(data_len-3)/2);
            fifo_write(interface->hdlc_output_fifo, (void *)m_updata_variable,&data_len);
       }
    return 0;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
int protocol_remote_begin(protocol_analyze_interface* interface,unsigned char* sources){
    func_type = idle_func;

    return 0;
}

int protocol_remote_output(protocol_analyze_interface* interface,unsigned char* sources){
    protocol_remote_struct * m_remote_output;
    unsigned int i=0;
    float m_amplitude=0;
    double m_double=0;
    unsigned int int_frequncy=0;
    unsigned char *p_float =( unsigned char *)&m_amplitude;
    float m_amplitude_tag;
    func_type = idle_func;
    m_remote_output = (protocol_remote_struct *)sources;
    EMIF(CHANNEL_SEL)= 0x400;
    memcpy(p_float,&(m_remote_output->channel_data[CHANNEL_ADDR-0x41][0]),4);
    if(m_remote_output->m_handle.cmd == REMOTE_CMD_CURRENT_OUTPUT)//電流輸出
    {
        DA_VI_SEL = 0;
        m_amplitude_tag = -50;
    }else if(m_remote_output->m_handle.cmd == REMOTE_CMD_VOLTAGE_OUTPUT)//電壓力輸出
    {
        DA_VI_SEL = 1;
        m_amplitude_tag = 1;
    }else
        return 0;

            WAVE_SEL = 1; //fix_wave
            m_double = m_amplitude*m_amplitude_tag/1000;//电压模式下：value = 目标电压（V）；电流模式下value = -50 * 目标电流（A）
            p_float=( unsigned char *)&m_double;
            SET_POINT_HH =*(unsigned short *)&p_float[6];
            SET_POINT_HL =*(unsigned short *)&p_float[4];
            SET_POINT_LH =*(unsigned short *)&p_float[2];
            SET_POINT_LL = *(unsigned short *)&p_float[0];
            DA_CONFIG_SEL=0X1;
            func_type = remote_returns_data;
    return 0;
}

int protocol_remote_returns_data(protocol_analyze_interface* interface,unsigned char* sources){
    double m_double=0;
    protocol_remote_struct  m_remote_returns_data;
    protocol_handle_struct * m_remote_returns_data_head = (protocol_handle_struct *)sources;
    unsigned short temp_data=0,i=0;
    unsigned short data_len=0;
switch(returns_data_status)
{
   case 0:
       fifo_clear(interface->ad_input_fifo);
       returns_data_status = 1;
   break;
    case 1:
    if (fifo_writeable(interface->hdlc_output_fifo))
    {
        temp_data =  fifo_readable(interface->ad_input_fifo);
        if (temp_data == 1)
        {
            func_type = idle_func;
            m_remote_returns_data.m_handle.data_locality_addr = REMOTE_ADDR;
            m_remote_returns_data.m_handle.data_source_addr = CHANNEL_ADDR;
            m_remote_returns_data.m_handle.cmd = m_remote_returns_data_head->cmd;
            fifo_read(interface->ad_input_fifo, &(m_remote_returns_data.channel_data[CHANNEL_ADDR-0x41][0]),&data_len);

            data_len = sizeof(protocol_remote_struct);
            fifo_write(interface->hdlc_output_fifo, (void *)&m_remote_returns_data,&data_len);
        }
    }
    break;
    default:
        break;
}
    return 0;
}
int protocol_remote_stop(protocol_analyze_interface* interface,unsigned char* sources){

    func_type = idle_func;
    //m_remote_stop = (protocol_handle_struct *)sources;
    return 0;
}

