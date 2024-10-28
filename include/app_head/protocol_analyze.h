/*
 * protocolanalyze.h
 *
 *  Created on: 2019��11��24��
 *      Author: Dell
 */
#include "comm_factory.h"
#include "fifo.h"
#include "control_variable.h"
#ifndef PROTOCOL_ANALYZE_H_
#define PROTOCOL_ANALYZE_H_

#define HOST_ADDR 0x52
#define REMOTE_ADDR 0x53
#define CHANNEL_ADDR 0x41//0x41~0x44�ĸ�ͨ��;
#define CHANNEL_ALL_ADDR 0x45//0x45ȫͨ����

#define CMD_REST                                           0xFF
#define CMD_RECV_AD                                    0x03
#define CMD_SET_CURRENT                            0x31
#define CMD_SET_VOLTAGE                            0x32


#define PC_CMD_SET_VARIABLE                      0x73
#define PC_CMD_DA_VARIABLE                       0x74
#define PC_CMD_AD_PHASE                            0x75
#define PC_CMD_AD_VARIABLE                       0x76
#define PC_CMD_FUSION_PARAMETERS        0x77
#define PC_CMD_KALMAN_PARAMETERS      0x78
#define PC_CMD_CAILIB_STRUCT                    0x79
#define PC_CMD_PID_STRUCT                         0x7A
#define PC_CMD_SYSTEM_STRUCT                 0x7B

#define REMOTE_CMD_BEGIN                         0x21
#define REMOTE_CMD_CURRENT_OUTPUT    0x23
#define REMOTE_CMD_VOLTAGE_OUTPUT    0x24
#define REMOTE_CMD_CURRENT_RETURNS  0x25
#define REMOTE_CMD_VOLTAGE_RETURNS  0x26
#define REMOTE_CMD_STOP                           0x29

#define ANALYZE_DATA_SIZE 512
#define AD_DATA_SIZE 480

#define NOR_FLASH_DATA_BASE              (0x60000000+128*0x8000)

#define WAVE_FIXED           0x01 //�̶�
#define WAVE_RECTANG    0x02//��
#define WAVE_TRI               0x04//����
#define WAVE_SIN              0x08//����

#pragma pack(1)

typedef enum Analyze_Type
{
    idle_func = 0,
    rest_func,
    recv_ad_cmd_func,
    recv_ad_data_func,
    set_mode_func,

    updata_variable_mode_func,
    updata_da_variable_func,
    updata_ad_phase_func,
    updata_ad_variable_func,
    updata_fusion_parameters_func,
    updata_kalman_parameters_func,
    updata_calib_struct_func,
    updata_pid_struct_func,
    updata_system_struct_func,

    remote_begin,
    remote_output,
    remote_returns_data,
    remote_stop
}Analyze_Type;


typedef struct protocol_handle_struct
{
    unsigned char data_locality_addr;
    unsigned char data_source_addr;
    unsigned char cmd;
}protocol_handle_struct;


typedef struct protocol_rest_struct
{
    protocol_handle_struct m_handle;
}protocol_rest_struct;

//���ػ���ȡͨ����������
typedef struct protocol_ad_to_pc_cmd_struct
{
    protocol_handle_struct m_handle;
    unsigned char channal;
}protocol_ad_to_pc_cmd_struct;

//ͨ����Ӧ���ػ�Ҫ��ָ��Э��
typedef struct protocol_ad_to_pc_struct
{
    unsigned char data_locality_addr;
    unsigned char data_source_addr;
    unsigned char work_mode;
    unsigned char data_sorce[AD_DATA_SIZE];
    unsigned char temp[2];
}protocol_ad_to_pc_struct;

//���ػ����ù���ģʽ
typedef struct protocol_ad_modle_set_struct
{
    protocol_handle_struct m_handle;
    unsigned char wave;
    unsigned char frequncy[4];
    unsigned char amplitude[4];
}protocol_ad_modle_set_struct;
/*===============================*/

typedef struct protocol_updata_variable_struct
{
    protocol_handle_struct m_handle;
    Da_Variable  up_da_variable;
    Ad_Phase      up_ad_phase;
    Ad_Variable  up_ad_variable;
    Fusion_Parameters up_fusion_parameters;
    Kalman_Parameters up_pusion_parameters;
    Calib_Struct  up_calib_struct;
    PID_Struct up_pid_struct;
}protocol_updata_variable_struct;

//++++++++++++++++�ⲿHDLC���++++++++++++++++++++//
typedef struct protocol_remote_struct
{
    protocol_handle_struct m_handle;
    unsigned char channel_data[4][4];
}protocol_remote_struct;


typedef struct protocol_analyze_interface
{
    int hdlc_input_fifo;
    int hdlc_output_fifo;

    int uart_input_fifo;
    int uart_output_fifo;

    int ad_input_fifo;
    int ad_output_fifo;

    int da_input_fifo;
    int da_output_fifo;

    int phase_input_fifo;
    int phase_output_fifo;

    int variable_input_fifo;
    int variable_output_fifo;

    int fusion_input_fifo;
    int fusion_output_fifo;

    int calib_input_fifo;
    int calib_output_fifo;

    int pid_input_fifo;
    int pid_output_fifo;
    
    void (*analyze)(struct protocol_analyze_interface* m_protocol_analyze);
}protocol_analyze_interface;

#pragma pack()
//����
void protocol_analyze(protocol_analyze_interface* interface);

typedef int (*PF)(protocol_analyze_interface* interface,unsigned char* sources);
int protocol_idle(protocol_analyze_interface* interface,unsigned char* sources);
int protocol_rest(protocol_analyze_interface* interface,unsigned char* sources);
int protocol_recv_ad_cmd(protocol_analyze_interface* interface,unsigned char* sources);
int protocol_recv_ad_data(protocol_analyze_interface* interface,unsigned char* sources);
int protocol_set_mode(protocol_analyze_interface* interface,unsigned char* sources);





protocol_analyze_interface* new_protocol_analyze_interface();
#endif /* PROTOCOLANALYZE_H_ */
