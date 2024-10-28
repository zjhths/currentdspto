/*
 * protocol_analyze_remote.h
 *
 *  Created on: 2020Äê9ÔÂ21ÈÕ
 *      Author: ydk
 */

#ifndef INCLUDE_APP_HEAD_PROTOCOL_ANALYZE_REMOTE_H_
#define INCLUDE_APP_HEAD_PROTOCOL_ANALYZE_REMOTE_H_
#include <protocol_analyze.h>


int protocol_remote_begin(protocol_analyze_interface* interface,unsigned char* sources);
int protocol_remote_output(protocol_analyze_interface* interface,unsigned char* sources);
int protocol_remote_returns_data(protocol_analyze_interface* interface,unsigned char* sources);
int protocol_remote_stop(protocol_analyze_interface* interface,unsigned char* sources);

#endif /* INCLUDE_APP_HEAD_PROTOCOL_ANALYZE_REMOTE_H_ */
