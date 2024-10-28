/*
 * protocol_analyze_remote.c
 *
 *  Created on: 2020年9月21日
 *      Author: ydk
 */
#include "protocol_analyze_remote.h"
#include "fifo.h"
#include"fpga.h"
#include "interface_da.h"
#include "interface_hdlc.h"

extern int returns_data_status;
extern Analyze_Type func_type;

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
            //func_type = remote_returns_data;
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
       return 0;
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
    return 0;
    default:
        returns_data_status = 0;
        return 0;
}

}
int protocol_remote_stop(protocol_analyze_interface* interface,unsigned char* sources){
    double m_double=0;
    unsigned char *p_float;
    func_type = idle_func;

    EMIF(CHANNEL_SEL)= 0x400;
    WAVE_SEL = 1; //fix_wave
    m_double = 0;//电压模式下：value = 目标电压（V）；电流模式下value = -50 * 目标电流（A）
    p_float=( unsigned char *)&m_double;
    SET_POINT_HH =*(unsigned short *)&p_float[6];
    SET_POINT_HL =*(unsigned short *)&p_float[4];
    SET_POINT_LH =*(unsigned short *)&p_float[2];
    SET_POINT_LL = *(unsigned short *)&p_float[0];
    DA_CONFIG_SEL=0X1;
    return 0;
}
