/*
 * interface_hdlc.h
 *
 *  Created on: 2019年11月23日
 *      Author: Dell
 */

#ifndef INCLUDE_APP_HEAD_INTERFACE_HDLC_H_
#define INCLUDE_APP_HEAD_INTERFACE_HDLC_H_

#define hdlc_0  0

#define WAVE_TRI    0x01
#define WAVE_RECTANG    0x02
#define WAVE_SIN    0x03
#define WAVE_FIXED  0x04

#define current_out 0x0
#define voltage_out 0x1

#define HDLC_Tx_RST_Disable (0x0001)
#define HDLC_TxEnable (0x0002)
#define HDLC_Tx_Fcsen  (0x0004)
#define HDLC_Tx_AbortFrame  (0x0200)

#define HDLC_Rx_RST_Disable (0x0001)
#define HDLC_Rx_Fcsen  (0x0002)
#define HDLC_Rx_int_enable  (0x0004)

   //HDLC
#define HDLC_tx_ctrl_addr                       (*(unsigned short int *)0x62002004)
#define HDLC_tx_data_in_addr                        (*(unsigned short int *)0x62002008)
#define HDLC_tx_status_addr                         (*(unsigned short int *)0x6200200C)

#define HDLC_rx_ctrl_addr                       (*(unsigned short int *)0x62002014)
#define HDLC_rx_data_out_addr                       (*(unsigned short int *)0x62002018)
#define HDLC_rx_status_addr                         (*(unsigned short int *)0x6200201C)

#define HDLC_int_flag_addr                      (*(unsigned short int *)0x62002020)
#define HDLC_clr_int_addr                       (*(unsigned short int *)0x62002024)

#define HDLC_CMD_SIZE                       500


typedef struct Hdlc_interface
{
    unsigned int channel;
    unsigned int recv_fifo;
    unsigned int send_fifo;
    unsigned int (*init)(struct Hdlc_interface* interface, unsigned int channel);
    unsigned int (*send)(struct Hdlc_interface* interface, unsigned char* data,unsigned int length);
    unsigned int (*recv)(struct Hdlc_interface* interface, unsigned char* data,unsigned int* length);     //类似于基类虚函数   函数指针
}Hdlc_interface;

//函数
unsigned int Hdlc_Init(Hdlc_interface* interface, unsigned int channel);
unsigned int Hdlc_Send(Hdlc_interface* interface, unsigned char* data,unsigned int length);
unsigned int Hdlc_Recv(Hdlc_interface* interface, unsigned char* data,unsigned int* length);

Hdlc_interface* new_hdlc_interface(unsigned int channel);
#endif /* INCLUDE_APP_HEAD_INTERFACE_HDLC_H_ */
