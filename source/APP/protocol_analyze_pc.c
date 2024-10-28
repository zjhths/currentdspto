/*
 * protocol_analyze_pc.c
 *
 *  Created on: 2020��9��21��
 *      Author: ydk
 */
#include "protocol_analyze_pc.h"
#include "mnic_nor.h"
#include "Init.h"
extern int returns_data_status;
extern Analyze_Type func_type;

extern Da_Variable m_da_variable;
extern Ad_Phase     m_ad_phase;
extern Ad_Variable m_ad_variable;
extern  Fusion_Parameters fusion;
extern  Kalman_Parameters m_pusion_parameters;
extern  Calib_Struct              m_calib_struct;
extern  PID_Struct                m_pid_struct;
extern  System_Struct          m_system_struct;

extern unsigned char channal_zero;
extern unsigned  int ad_updata;
//���±���ģʽ��������д�� NOR Flash��������������ʱ������д�� FIFO��
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
    Flash_data_init();
    return 0;
}
//���� DA ������������д�� FIFO������ʼ�� DA ������
int protocol_updata_da_variable(protocol_analyze_interface* interface,unsigned char* sources)
{
     unsigned short data_len=sizeof(m_da_variable)+3;
    func_type = idle_func;
    memcpy(&m_da_variable,sources+3,data_len-3);
    if (fifo_writeable(interface->hdlc_output_fifo))
      {
            fifo_write(interface->hdlc_output_fifo, (void *)sources,&data_len);
      };
    DAPara_init();
    return 0;
}
//���� AD ��λ��������д�� FIFO������ʼ��ͨ���ӳ١�
int protocol_updata_ad_phase(protocol_analyze_interface* interface,unsigned char* sources){
    unsigned short data_len=sizeof(m_ad_phase)+3;
    func_type = idle_func;
    //channal_zero = 0x3;
    memcpy(&m_ad_phase,sources+3,data_len-3);
    if (fifo_writeable(interface->hdlc_output_fifo))
      {
            fifo_write(interface->hdlc_output_fifo, (void *)sources,&data_len);
      };
    channaldelay_init();
    return 0;
}
//���� AD ������������д�� FIFO������ʼ�� AD ������
int protocol_updata_ad_variable(protocol_analyze_interface* interface,unsigned char* sources){
    unsigned short data_len=sizeof(m_ad_variable)+3;
    func_type = idle_func;
    //channal_zero = 0x2;
    memcpy(&m_ad_variable,sources+3,data_len-3);
    if (fifo_writeable(interface->hdlc_output_fifo))
      {
            fifo_write(interface->hdlc_output_fifo, (void *)sources,&data_len);
      };
    ADPara_init();
    return 0;
}
//�����ںϲ�����������д�� FIFO������ʼ���ںϲ�����
int protocol_updata_fusion_parameters(protocol_analyze_interface* interface,unsigned char* sources)
{
    unsigned short data_len=sizeof(fusion)+3;
    func_type = idle_func;
    memcpy(&fusion,sources+3,sizeof(fusion));
    if (fifo_writeable(interface->hdlc_output_fifo))
      {
            fifo_write(interface->hdlc_output_fifo, (void *)sources,&data_len);
      };
    FUSION_init();
    return 0;
}
//���¿�����������������д�� FIFO������ʼ��������������
int protocol_updata_kalman_parameters(protocol_analyze_interface* interface,unsigned char* sources)
{
    unsigned short data_len=sizeof(m_pusion_parameters)+3;
    func_type = idle_func;
    memcpy(&m_pusion_parameters,sources+3,data_len-3);
    if (fifo_writeable(interface->hdlc_output_fifo))
      {
            fifo_write(interface->hdlc_output_fifo, (void *)sources,&data_len);
      };
    Kalmen_init();
    return 0;
}
//����У׼������������д�� FIFO������ʼ��У׼������
int protocol_updata_calib_struct(protocol_analyze_interface* interface,unsigned char* sources)
{
    unsigned short data_len=sizeof(m_calib_struct)+3;
    func_type = idle_func;
    memcpy(&m_calib_struct,sources+3,sizeof(m_calib_struct));
    if (fifo_writeable(interface->hdlc_output_fifo))
      {
            fifo_write(interface->hdlc_output_fifo, (void *)sources,&data_len);
      };
    Calib_Para_init();
    return 0;
}
//���� PID ������������д�� FIFO������ʼ�� PID ������
int protocol_updata_pid_struct(protocol_analyze_interface* interface,unsigned char* sources)
{
    unsigned short data_len=sizeof(m_pid_struct)+3;
    func_type = idle_func;
    memcpy(&m_pid_struct,sources+3,sizeof(m_pid_struct));
    if (fifo_writeable(interface->hdlc_output_fifo))
      {
            fifo_write(interface->hdlc_output_fifo, (void *)sources,&data_len);
      };
    PID_init();
    return 0;
}
//����ϵͳ������������д�� FIFO������ʼ��ϵͳ������
int protocol_updata_system_struct(protocol_analyze_interface* interface,unsigned char* sources)
{
    unsigned short data_len=sizeof(m_system_struct)+3;
    func_type = idle_func;
    memcpy(&m_system_struct,sources+3,data_len-3);
    if (fifo_writeable(interface->hdlc_output_fifo))
      {
            fifo_write(interface->hdlc_output_fifo, (void *)sources,&data_len);
      };
    sys_int();
    return 0;
}
