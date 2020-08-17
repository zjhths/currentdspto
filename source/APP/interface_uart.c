#include "interface_uart.h"


Uart_interface* new_uart_interface(unsigned int channel,unsigned int speed)
{

	Uart_interface* real_core	 = (Uart_interface*)malloc(sizeof(Uart_interface));
	real_core->channel   = channel;
	real_core->speed     = speed;
	real_core->init      = Uart_Init;
	real_core->send		 = Uart_Send;
	real_core->recv   	 = Uart_Recv;
	real_core->send_fifo = fifo_create(256, 1);
	real_core->recv_fifo = fifo_create(256, 1);
	real_core->init(real_core,channel,speed);
	real_core->process   = Uart_Interface_Process;
    Clr_UART_INT_addr=1;
    Clr_UART_INT_addr=0;
	return real_core;
}

void Uart_Init(Uart_interface* interface, unsigned int channel,unsigned int speed){
    Uart_ctrl0_addr(channel) = 0x0000;    //Uart_ctrl(0):复位;(2)中断使能;(3-6)接收到多少数据时产生中断;(9)超时产生中断使能
    Uart_ctrl0_addr(channel) = 0x000d;

    div_uart_0_addr(channel)=1; //设置波特率,
    Uart_set_0_addr(channel)=0x41; //设置为8分频，奇校验
}

void Uart_Send(Uart_interface* interface, unsigned char* data,unsigned int length){
    int i=0;
//    Uart_ctrl0_addr(interface->channel)= 0x0000;
//    Uart_ctrl0_addr(interface->channel)= 0x0055;
    for(i=0;i<length;i++)
    {
        if (fifo_writeable(interface->send_fifo))
        {
            fifo_write(interface->send_fifo, (void *)&data[i]);
        }
    }
}



void Uart_Recv(Uart_interface* interface, unsigned char* data,unsigned int* length){
    unsigned int* data_length=length;
    unsigned int i=0;
    *data_length =(Uart_Status0_H_addr(interface->channel) >> 4) & 0x000f;
    if(*data_length>10){
        //*data_length=10;
    }
    for(i=0;i<*data_length;i++)
    {
        data[i] = Uart_Rx_Data0_addr(interface->channel);
        if (fifo_writeable(interface->recv_fifo))
        {
            fifo_write(interface->recv_fifo, (void *)&data[i]);
        }
    }

}


void Uart_Interface_Process(Uart_interface* interface){
    unsigned char byte_temp=0,uart_temp=0;;
    if (fifo_readable(interface->send_fifo))
    {
        uart_temp = Uart_Status0_L_addr(interface->channel);
        if((uart_temp & 0x0002) == 0){
            fifo_read(interface->send_fifo, (void *)&byte_temp);
            Uart_Tx_Data0_addr(interface->channel) = byte_temp;
        }

    }
}



