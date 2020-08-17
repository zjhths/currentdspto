
#ifndef _INTERFACE_AD_H_
#define _INTERFACE_AD_H_

#include <stdio.h>
#include <stdlib.h>
#include "define_imput.h"
#include "fifo.h"

#define PC_AD 2
#define L_AD 0

//#define Ad_ctrl0_addr(x)   (*((volatile unsigned short *)(0x62000000 + 130 + x*10)))



typedef struct Ad_interface
{
    unsigned int recv_fifo;
    unsigned int send_fifo;
    void(*init)(struct Ad_interface* interface);
    void(*send)(struct Ad_interface* interface, unsigned char* data,unsigned int length);
    void(*recv)(struct Ad_interface* interface, unsigned char* data,unsigned int* length);     //类似于基类虚函数   函数指针
}Ad_interface;


//函数
void Ad_Init(Ad_interface* interface);
void Ad_Send(Ad_interface* interface, unsigned char* data,unsigned int length);
void Ad_Recv(Ad_interface* interface, unsigned char* data,unsigned int* length);

void Ad_Interface_Process(Ad_interface* interface);

Ad_interface* new_ad_interface();
#endif /* CORE_H_ */
