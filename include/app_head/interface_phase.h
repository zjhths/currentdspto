#ifndef _INTERFACE_PHASE_H_
#define _INTERFACE_PHASE_H_

#include <stdio.h>
#include <stdlib.h>
#include "define_imput.h"
#include "fifo.h"

//#define Ad_ctrl0_addr(x)   (*((volatile unsigned short *)(0x62000000 + 130 + x*10)))



typedef struct Phase_interface
{
    unsigned int recv_fifo;
    unsigned int send_fifo;
    void(*init)(struct Phase_interface* interface);
    void(*send)(struct Phase_interface* interface, unsigned char* data,unsigned int length);
    void(*recv)(struct Phase_interface* interface, unsigned char* data,unsigned int* length);     //类似于基类虚函数   函数指针
}Phase_interface;


//函数
void Phase_Init(Phase_interface* interface);
void Phase_Send(Phase_interface* interface, unsigned char* data,unsigned int length);
void Phase_Recv(Phase_interface* interface, unsigned char* data,unsigned int* length);

void Phase_Interface_Process(Phase_interface* interface);

Phase_interface* new_phase_interface();
#endif /* CORE_H_ */