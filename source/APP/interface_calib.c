#include "interface_calib.h"

void * calib_recv_mem;
Calib_interface* new_calib_interface()
{
    Fifo *fifo = 0;
	Calib_interface* real_core	 = (Calib_interface*)malloc(sizeof(Calib_interface));

	real_core->init      = Calib_Init;
	real_core->send		 = Calib_Send;
	real_core->recv   	 = Calib_Recv;

	real_core->recv_fifo = fifo_create(6*1500, 8);
	fifo =(Fifo *)(real_core->recv_fifo);
	calib_recv_mem = (fifo->fifo_ptr);
	real_core->init(real_core);

	return real_core;
}

void Calib_Init(Calib_interface* interface){

}

void Calib_Send(Calib_interface* interface, unsigned char* data,unsigned int length){
    int i=0;
    unsigned short data_len=0;

//    Ad_ctrl0_addr(interface->channel)= 0x0000;
//    Ad_ctrl0_addr(interface->channel)= 0x0055;
    for(i=0;i<length;i++)
    {
        if (fifo_writeable(interface->send_fifo))
        {
            fifo_write(interface->send_fifo, (void *)&data[i],&data_len);
        }

    }
}



void Calib_Recv(Calib_interface* interface, unsigned char* data,unsigned int* length){
    unsigned int* data_length=length;
    unsigned int i=0;
    unsigned short data_len=8;
    unsigned char data_temp[8];
    unsigned short data_len_temp=0;
    for(i=0;i<*data_length;i++)
    {
        if (fifo_writeable(interface->recv_fifo))
        {
            fifo_write(interface->recv_fifo, (void *)&data[i],&data_len);
        }else
        {
        	fifo_read(interface->recv_fifo, (void *)&data_temp,&data_len_temp);
        	fifo_write(interface->recv_fifo, (void *)&data[i],&data_len);
        }
    }

}