/*
 * protocol_analyze_pc.h
 *
 *  Created on: 2020Äê9ÔÂ21ÈÕ
 *      Author: ydk
 */

#ifndef INCLUDE_APP_HEAD_PROTOCOL_ANALYZE_PC_H_
#define INCLUDE_APP_HEAD_PROTOCOL_ANALYZE_PC_H_
#include <protocol_analyze.h>
#pragma pack(1)

#pragma pack()
int protocol_updata_variable_mode(protocol_analyze_interface* interface,unsigned char* sources);
int protocol_updata_da_variable(protocol_analyze_interface* interface,unsigned char* sources);
int protocol_updata_ad_phase(protocol_analyze_interface* interface,unsigned char* sources);
int protocol_updata_ad_variable(protocol_analyze_interface* interface,unsigned char* sources);
int protocol_updata_fusion_parameters(protocol_analyze_interface* interface,unsigned char* sources);
int protocol_updata_kalman_parameters(protocol_analyze_interface* interface,unsigned char* sources);
int protocol_updata_calib_struct(protocol_analyze_interface* interface,unsigned char* sources);
int protocol_updata_pid_struct(protocol_analyze_interface* interface,unsigned char* sources);
int protocol_updata_system_struct(protocol_analyze_interface* interface,unsigned char* sources);

#endif /* INCLUDE_APP_HEAD_PROTOCOL_ANALYZE_PC_H_ */
