/*
 * interface_hdlc.c
 *
 *  Created on: 2019年11月23日
 *      Author: syn
 */

#include "interface_hdlc.h"
unsigned int hdlc_count=0;
extern Hdlc_interface* my_hdlc;
Hdlc_interface* new_hdlc_interface(unsigned int channel)
{

    Hdlc_interface* real_core    = (Hdlc_interface*)malloc(sizeof(Hdlc_interface));
    real_core->channel   = channel;
    real_core->init      = Hdlc_Init;
    real_core->send      = Hdlc_Send;
    real_core->recv      = Hdlc_Recv;
    if(hdlc_count == 0){
       real_core->send_fifo = fifo_create(3, 512);
    }else
       real_core->send_fifo = my_hdlc->send_fifo;

    if(hdlc_count == 0){
       real_core->recv_fifo = fifo_create(3, 512);
    }else
       real_core->recv_fifo = my_hdlc->recv_fifo;
        hdlc_count++;
    real_core->init(real_core,channel);

    return real_core;
}

unsigned int Hdlc_Init(Hdlc_interface* interface, unsigned int channel){
	int i;
	HDLC_tx_ctrl_addr  &= ~HDLC_Tx_RST_Disable;   //进入发送复位状态
	HDLC_tx_ctrl_addr  |= HDLC_Tx_Fcsen ;  //使能帧校验

    for(i=0;i<1000;i++);
    HDLC_tx_ctrl_addr  |= HDLC_Tx_RST_Disable;  //结束发送复位状态，复位结束

	HDLC_rx_ctrl_addr &= ~HDLC_Rx_RST_Disable;   //进入接收复位状态
    asm(   "nop");
    HDLC_rx_ctrl_addr |= HDLC_Rx_Fcsen;         //使能帧校验
	asm("   NOP");
	HDLC_rx_ctrl_addr &= ~HDLC_Rx_int_enable;//接收中断關閉
	asm("   NOP");
	HDLC_rx_ctrl_addr |= HDLC_Rx_RST_Disable;   //结束接收复位状态，
	asm("   NOP");


    HDLC_clr_int_addr = 0x01;   //清除中断
	asm("   NOP");
    HDLC_clr_int_addr = 0x00;
    HDLC_rx_ctrl_addr |= HDLC_Rx_int_enable;//使能HDLC中断
    return 0;
}

unsigned int Hdlc_Send(Hdlc_interface* interface, unsigned char* data,unsigned int length){
	int cnt=0;
	unsigned short temp=0;
    unsigned short XG_TXCTRL_temp=0,Hdlc_txstatus_temp=0;
    Hdlc_txstatus_temp = HDLC_tx_status_addr  & 0x0401;
    if((Hdlc_txstatus_temp) == 0x0001)
    {
    	HDLC_tx_ctrl_addr &= ~HDLC_Tx_RST_Disable;  //发送复位
    	HDLC_tx_ctrl_addr &= ~HDLC_TxEnable;  //关闭发送功能
    	HDLC_tx_ctrl_addr |= HDLC_Tx_RST_Disable;  //跳出发送复位状态

    	//put data into tx fifo

    	for(cnt=0;cnt<length;cnt++)
    	{
    		temp= data[cnt];
    		HDLC_tx_data_in_addr = temp;
    		asm("	NOP");
    		asm("	NOP");
    		asm("	NOP");
    	}

    	HDLC_tx_ctrl_addr |= HDLC_TxEnable;  //使能发送，开始发送数据
    	return 1;
    }
return 0;
}



unsigned int Hdlc_Recv(Hdlc_interface* interface, unsigned char* data,unsigned int* length){
    unsigned int* data_length=length;
    unsigned int hdlc_byte_temp;
    unsigned int i=0;
    unsigned short data_len=0;
	hdlc_byte_temp = HDLC_rx_status_addr & 0x01ff;
	*data_length = hdlc_byte_temp>>1;      //接收到的数据个数
    for(i=0;i<*data_length;i++)
    {
        data[i] = HDLC_rx_data_out_addr & 0xFF;
    }
    if (fifo_writeable(interface->recv_fifo))
    {
        fifo_write(interface->recv_fifo, (void *)data,&data_len);
    }
    return 0;
}





