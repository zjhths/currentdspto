
#ifndef _INTERFACE_AD_H_
#define _INTERFACE_AD_H_

#include <stdio.h>
#include <stdlib.h>
#include "define_imput.h"
#include "fifo.h"

typedef struct Calib_interface
{
    unsigned int recv_fifo;
    unsigned int send_fifo;
    void(*init)(struct Calib_interface* interface);
    void(*send)(struct Calib_interface* interface, unsigned char* data,unsigned int length);
    void(*recv)(struct Calib_interface* interface, unsigned char* data,unsigned int* length);     //类似于基类虚函数   函数指针
}Calib_interface;


//函数
void Calib_Init(Calib_interface* interface);
void Calib_Send(Calib_interface* interface, unsigned char* data,unsigned int length);
void Calib_Recv(Calib_interface* interface, unsigned char* data,unsigned int* length);

void Calib_Interface_Process(Calib_interface* interface);

Calib_interface* new_calib_interface();
#endif /* CORE_H_ */
