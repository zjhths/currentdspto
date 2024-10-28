#include "interface_fusion.h"

void * fusion_recv_mem;
Fusion_interface* new_fusion_interface()
{
    Fifo *fifo = 0;
	Fusion_interface* real_core	 = (Fusion_interface*)malloc(sizeof(Fusion_interface));

	real_core->init      = Fusion_Init;
	real_core->send		 = Fusion_Send;
	real_core->recv   	 = Fusion_Recv;

	real_core->recv_fifo = fifo_create(6*1500, 8);
	fifo =(Fifo *)(real_core->recv_fifo);
	fusion_recv_mem = (fifo->fifo_ptr);
	real_core->init(real_core);

	return real_core;
}

void Fusion_Init(Fusion_interface* interface){

}

void Fusion_Send(Fusion_interface* interface, unsigned char* data,unsigned int length){
    int i=0;
    unsigned short data_len=0;
    for(i=0;i<length;i++)
    {
        if (fifo_writeable(interface->send_fifo))
        {
            fifo_write(interface->send_fifo, (void *)&data[i],&data_len);
        }

    }
}



void Fusion_Recv(Fusion_interface* interface, unsigned char* data,unsigned int* length){
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