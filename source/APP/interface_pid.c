#include "interface_pid.h"

void * pid_recv_mem;
Pid_interface* new_pid_interface()
{
    Fifo *fifo = 0;
	Pid_interface* real_core	 = (Pid_interface*)malloc(sizeof(Pid_interface));

	real_core->init      = Pid_Init;
	real_core->send		 = Pid_Send;
	real_core->recv   	 = Pid_Recv;

	real_core->recv_fifo = fifo_create(6*1500, 8);
	fifo =(Fifo *)(real_core->recv_fifo);
	pid_recv_mem = (fifo->fifo_ptr);
	real_core->init(real_core);

	return real_core;
}

void Pid_Init(Pid_interface* interface){

}

void Pid_Send(Pid_interface* interface, unsigned char* data,unsigned int length){
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



void Pid_Recv(Pid_interface* interface, unsigned char* data,unsigned int* length){
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