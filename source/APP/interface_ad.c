#include "interface_ad.h"

void * ad_recv_mem;
Ad_interface* new_ad_interface()
{
    Fifo *fifo = 0;
	Ad_interface* real_core	 = (Ad_interface*)malloc(sizeof(Ad_interface));

	real_core->init      = Ad_Init;
	real_core->send		 = Ad_Send;
	real_core->recv   	 = Ad_Recv;

	real_core->recv_fifo = fifo_create(6*3000, 4);
	fifo =(Fifo *)(real_core->recv_fifo);
	ad_recv_mem = (fifo->fifo_ptr);
	real_core->init(real_core);

	return real_core;
}

void Ad_Init(Ad_interface* interface){

}

void Ad_Send(Ad_interface* interface, unsigned char* data,unsigned int length){
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



void Ad_Recv(Ad_interface* interface, unsigned char* data,unsigned int* length){
    unsigned int* data_length=length;
    unsigned int i=0;
    unsigned short data_len=4;
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





